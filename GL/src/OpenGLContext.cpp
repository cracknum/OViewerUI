#include "OpenGLContext.hpp"
#include "IWindow.hpp"
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <iostream>

static void on_window_size_callback(GLFWwindow *window, int width, int height)
{
    auto pWindow = static_cast<IWindow *>(glfwGetWindowUserPointer(window));
    pWindow->onResize(width, height);
}

static void on_window_close_callback(GLFWwindow *window)
{
    IWindow *pWindow = static_cast<IWindow *>(glfwGetWindowUserPointer(window));
    pWindow->close();
}

bool OpenGLContext::init(IWindow *window)
{
    superclass::init(window);
    /* Initialize the library */
    if (!glfwInit())
    {
        fprintf(stderr, "Error: GLFW Window couldn't be initialized\n");
        return false;
    }

    // Create the window and store this window as window pointer
    // so that we can use it in callback functions
    auto glWindow = glfwCreateWindow(window->mWidth, window->mHeight, window->mTitle.c_str(), nullptr, nullptr);
    window->setNativeWindow(glWindow);

    if (!glWindow)
    {
        fprintf(stderr, "Error: GLFW Window couldn't be created\n");
        return false;
    }

    glfwSetWindowUserPointer(glWindow, window);
    glfwSetWindowSizeCallback(glWindow, on_window_size_callback);
    glfwSetWindowCloseCallback(glWindow, on_window_close_callback);
    glfwMakeContextCurrent(glWindow);

    
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %u\n", glad_glGetError());
        return false;
    }

    glEnable(GL_DEPTH_TEST);

    return true;
}

void OpenGLContext::preRender()
{
    glViewport(0, 0, mWindow->mWidth, mWindow->mHeight);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLContext::postRender()
{
    glfwPollEvents();
    glfwSwapBuffers((GLFWwindow*) mWindow->getNativeWindow());
}

void OpenGLContext::end()
{
    glfwDestroyWindow((GLFWwindow*)mWindow->getNativeWindow());
    glfwTerminate();
}
