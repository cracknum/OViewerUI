#include "OpenGLWindow.hpp"
#include "OpenGLContext.hpp"
#include "SceneView.hpp"
#include "UIContext.hpp"
#include <iostream>
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include "AppEvent.h"
#include "AppEventData.h"
#include "MenuBar.h"
#include "MouseEvent.h"
#include "WidgetEvent.h"
#include "WidgetEventData.h"
#include <GLFW/glfw3.h>
#include <functional>
#include <imgui.h>
#include <stb_image.h>

class MenuItemClickedObserver final : public IEventObserver
{
public:
  bool handle(const EventObject& event) override
  {
    auto data = dynamic_cast<const MenuItemData*>(event.eventData());
    SPDLOG_DEBUG("item clicked, event type: {}, address: {}",
      EventIdStr[static_cast<int>(event.eventId())], data->menuItemName());
    return true;
  }
};

class ExitObserver : public IEventObserver
{
public:
  bool handle(const EventObject& event) override
  {
    auto menuEvent = dynamic_cast<const MenuItemClicked*>(&event);
    if (menuEvent && menuEvent->eventId() == EventId::Exit && mCallback)
    {
      mCallback();
      SPDLOG_DEBUG("APP exit");
    }
      SPDLOG_DEBUG("APP exit: {}", EventIdStr[static_cast<int>(event.eventId())]);

    return true;
  }

  void setExitCallBack(std::function<void()> callback) { mCallback = std::move(callback); }

private:
  std::function<void()> mCallback;
};

struct WindowPrivate final
{
  bool mIsRunning;
  void* mWindow;
  std::unique_ptr<UIContext> mUIContext;
  std::unique_ptr<OpenGLContext> mOpenGLContext;
  std::shared_ptr<SceneView> mSceneView;
  std::unique_ptr<MenuBar> mMenuBar;

  WindowPrivate()
    : mIsRunning(false)
    , mWindow(nullptr)
  {
    mMenuBar = std::make_unique<MenuBar>();
  }
};

OpenGLWindow::OpenGLWindow()
  : Widget("")
{
  mPrivate = std::make_unique<WindowPrivate>();
  mPrivate->mIsRunning = true;
  mPrivate->mWindow = nullptr;
  mPrivate->mUIContext = std::make_unique<UIContext>();
  mPrivate->mOpenGLContext = std::make_unique<OpenGLContext>();
}

OpenGLWindow::~OpenGLWindow()
{
  mPrivate->mUIContext->end();
  mPrivate->mOpenGLContext->end();
}

bool OpenGLWindow::init(int width, int height, const std::string& title)
{
  mWidth = width;
  mHeight = height;
  mTitle = title;

  mPrivate->mOpenGLContext->init(this);
  mPrivate->mUIContext->init(this);
  mPrivate->mSceneView = std::make_shared<SceneView>(mPrivate->mUIContext->GetContext());
  this->addObserver(mPrivate->mSceneView);

  MenuBar::Menu menu;
  menu.setName("File");
  MenuBar::Menu::Item item1("open", std::make_shared<MenuItemClickedObserver>());
  MenuBar::Menu::Item item2("close", std::make_shared<MenuItemClickedObserver>());
  menu.addItem(item1);
  menu.addItem(item2);

  MenuBar::Menu exitMenu;
  exitMenu.setName("App");

  auto exitObserver = std::make_shared<ExitObserver>();
  exitObserver->setExitCallBack([this]() { exit(); });
  MenuBar::Menu::Item exitItem("exit", exitObserver);

  exitMenu.addItem(exitItem);

  mPrivate->mMenuBar->addMenu(menu);
  mPrivate->mMenuBar->addMenu(exitMenu);

  return mPrivate->mIsRunning;
}

bool OpenGLWindow::Render()
{
  ImGui::SetCurrentContext(mPrivate->mUIContext->GetContext());
  mPrivate->mOpenGLContext->preRender();
  mPrivate->mUIContext->preRender();
  mPrivate->mMenuBar->Render();
  mPrivate->mSceneView->render();

  mPrivate->mUIContext->postRender();
  mPrivate->mOpenGLContext->postRender();

  handleInput();

  return true;
}

void OpenGLWindow::handleInput()
{
  mousePressCheck();

  mouseDragCheck();
  mouseMoveCheck();
  mouseReleaseCheck();
}

bool OpenGLWindow::isRunning() const
{
  return mPrivate->mIsRunning;
}

void* OpenGLWindow::getNativeWindow()
{
  return mPrivate->mWindow;
}

void OpenGLWindow::setNativeWindow(void* window)
{
  mPrivate->mWindow = window;
}

void OpenGLWindow::onResize(int width, int height)
{
  mWidth = width;
  mHeight = height;
  auto eventData = std::make_unique<WidgetResizeData>(ImVec2(width, height));
  this->invokeEvent(WidgetEvent(EventId::WidgetResize, std::move(eventData)));
  Render();
}

void OpenGLWindow::close()
{
  mPrivate->mIsRunning = false;
}

void OpenGLWindow::setWindowIcon(const std::string& iconPath)
{
  if (!mPrivate->mWindow)
  {
    SPDLOG_ERROR("window is not initialized");
    return;
  }

  int width = 0;
  int height = 0;
  int channels = 0;
  GLFWimage icon;
  icon.pixels = stbi_load(iconPath.c_str(), &width, &height, &channels, 4);
  icon.width = width;
  icon.height = height;
  if (!icon.pixels)
  {
    SPDLOG_ERROR("could not open file: {}, failed reason: {}", iconPath, stbi_failure_reason());
    return;
  }

  glfwSetWindowIcon(static_cast<GLFWwindow*>(mPrivate->mWindow), 1, &icon);
  stbi_image_free(icon.pixels);
}

void OpenGLWindow::resize(int width, int height)
{
  mWidth = width;
  mHeight = height;
  mPrivate->mOpenGLContext->resize(width, height);
}

void OpenGLWindow::fullScreen()
{
  mPrivate->mOpenGLContext->fullScreen();
}

void OpenGLWindow::maximum()
{
  mPrivate->mOpenGLContext->maximum();
}

std::shared_ptr<SceneView> OpenGLWindow::sceneView()
{
  return mPrivate->mSceneView;
}

void OpenGLWindow::exit()
{
  mPrivate->mIsRunning = false;
  SPDLOG_DEBUG("RUNNING STATE: {}", mPrivate->mIsRunning);
}

void OpenGLWindow::mousePressCheck()
{
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
  {
    auto& io = ImGui::GetIO();

    auto buttonPos = io.MouseClickedPos[ImGuiMouseButton_Left];
    auto eventData = std::make_unique<MousePressedData>(buttonPos, ImGuiMouseButton_Left);
    this->invokeEvent(MouseEvent(EventId::MousePressed, std::move(eventData)));

    SPDLOG_DEBUG("mouse left button clicked");
  }
}

void OpenGLWindow::mouseMoveCheck()
{
  auto& io = ImGui::GetIO();
  if (!ImGui::IsAnyMouseDown() && (fabsf(io.MouseDelta.x) > 1e-6 || fabsf(io.MouseDelta.y) > 1e-6))
  {
    ImVec2 mousePos = io.MousePos;
    ImVec2 preMousePos = io.MousePosPrev;

    auto eventData = std::make_unique<MouseMoveData>(mousePos, preMousePos);
    this->invokeEvent(MouseEvent(EventId::MouseMove, std::move(eventData)));
    SPDLOG_DEBUG("mouse move");
  }
}

void OpenGLWindow::mouseDragCheck()
{
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
  {
    auto& io = ImGui::GetIO();
    ImVec2 accumulateDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
    auto eventData = std::make_unique<MouseDragData>(accumulateDelta, ImGuiMouseButton_Left);
    this->invokeEvent(MouseEvent(EventId::MouseDrag, std::move(eventData)));

    SPDLOG_DEBUG("mouse draging");
  }
}

void OpenGLWindow::mouseReleaseCheck()
{
  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
  {
    this->invokeEvent(MouseEvent(EventId::MouseRelease, std::make_unique<MouseReleaseData>()));
    SPDLOG_DEBUG("mouse left button released");
  }
}
