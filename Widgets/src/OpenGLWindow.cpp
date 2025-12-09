#include "OpenGLWindow.hpp"
#include "OpenGLContext.hpp"
#include "SceneView.hpp"
#include "UIContext.hpp"
#include <iostream>
#include <spdlog/spdlog.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <GLFW/glfw3.h>

struct WindowPrivate final
{
  bool mIsRunning;
  void* mWindow;
  std::unique_ptr<UIContext> mUIContext;
  std::unique_ptr<OpenGLContext> mOpenGLContext;
  std::shared_ptr<SceneView> mSceneView;
  WindowPrivate()
    : mIsRunning(false)
    , mWindow(nullptr)
  {
  }
};

OpenGLWindow::OpenGLWindow()
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

  return mPrivate->mIsRunning;
}

void OpenGLWindow::render()
{
  mPrivate->mOpenGLContext->preRender();
  mPrivate->mUIContext->preRender();
  mPrivate->mSceneView->render();

  mPrivate->mUIContext->postRender();
  mPrivate->mOpenGLContext->postRender();

  handleInput();
}

void OpenGLWindow::handleInput()
{
  double x, y;
  glfwGetCursorPos(static_cast<GLFWwindow*>(mPrivate->mWindow), &x, &y);
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

  render();
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

std::shared_ptr<SceneView> OpenGLWindow::sceneView()
{
  return mPrivate->mSceneView;
}
