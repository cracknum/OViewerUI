#include "../include/OpenGLWindow.hpp"
#include "OpenGLContext.hpp"
#include "SceneView.hpp"
#include "UIContext.hpp"
// clang-format off
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

struct WindowPrivate final {
  bool mIsRunning;
  GLFWwindow *mWindow;
  std::unique_ptr<UIContext> mUIContext;
  std::unique_ptr<OpenGLContext> mOpenGLContext;
  std::unique_ptr<SceneView> mPropertyPanel;
  WindowPrivate() : mIsRunning(false), mWindow(nullptr) {}
};

OpenGLWindow::OpenGLWindow() {
  mPrivate = std::make_unique<WindowPrivate>();
  mPrivate->mIsRunning = true;
  mPrivate->mWindow = nullptr;
  mPrivate->mUIContext = std::make_unique<UIContext>();
  mPrivate->mOpenGLContext = std::make_unique<OpenGLContext>();
}

OpenGLWindow::~OpenGLWindow() {
  mPrivate->mUIContext->end();
  mPrivate->mOpenGLContext->end();
}

bool OpenGLWindow::init(int width, int height, const std::string &title) {
  mWidth = width;
  mHeight = height;
  mTitle = title;

  mPrivate->mOpenGLContext->init(this);
  mPrivate->mUIContext->init(this);
  mPrivate->mPropertyPanel =
      std::make_unique<SceneView>(mPrivate->mUIContext->GetContext());

  return mPrivate->mIsRunning;
}

void OpenGLWindow::render() {
  mPrivate->mOpenGLContext->preRender();
  mPrivate->mUIContext->preRender();
  mPrivate->mPropertyPanel->render();

  mPrivate->mUIContext->postRender();
  mPrivate->mOpenGLContext->postRender();

  handleInput();
}

void OpenGLWindow::handleInput() {
  double x, y;
  glfwGetCursorPos(mPrivate->mWindow, &x, &y);
}

bool OpenGLWindow::isRunning() const { return mPrivate->mIsRunning; }

void *OpenGLWindow::getNativeWindow() { return mPrivate->mWindow; }

void OpenGLWindow::setNativeWindow(void *window) {
  mPrivate->mWindow = static_cast<GLFWwindow *>(window);
}

void OpenGLWindow::onResize(int width, int height) {
  mWidth = width;
  mHeight = height;

  render();
}

void OpenGLWindow::close() { mPrivate->mIsRunning = false; }
