#include "Application.hpp"
#include "../include/OpenGLWindow.hpp"
#include <iostream>

struct ApplicationPrivate
{
    std::unique_ptr<OpenGLWindow> mRenderWindow;

    ApplicationPrivate()
    {

    }
};

Application::Application(int argc, char **argv)
{
    mPrivate = std::make_unique<ApplicationPrivate>();
    mPrivate->mRenderWindow = std::make_unique<OpenGLWindow>();
    mPrivate->mRenderWindow->init(1920, 1080, "Window");
}

Application::~Application()
{
}

void Application::loop()
{
    while(mPrivate->mRenderWindow->isRunning())
    {
        mPrivate->mRenderWindow->render();
    }
}
