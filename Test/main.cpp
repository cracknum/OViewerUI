#include "Application.hpp"
#include "Log.h"
#include "OpenGLWindow.hpp"
#include "SceneView.hpp"
#include <spdlog/spdlog.h>
int main(int argc, char** argv)
{
  Application app(argc, argv);
  Log::initLog(spdlog::level::debug);
  auto renderWindow = app.renderWindow();
  renderWindow->maximum();
  auto glRenderWindow = std::static_pointer_cast<OpenGLWindow>(renderWindow);
  if (!glRenderWindow)
  {
    SPDLOG_DEBUG("opengl window is nullptr");
    return EXIT_FAILURE;
  }

  auto sceneView = glRenderWindow->sceneView();
  if (!sceneView)
  {
    SPDLOG_DEBUG("scene view is nullptr");
    return EXIT_FAILURE;
  }

  auto viewWidget = sceneView->viewerWidget();
  if (!viewWidget)
  {
    SPDLOG_DEBUG("view widget is nullptr");
    return EXIT_FAILURE;
  }

  return app.exec();
}