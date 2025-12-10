#include "Application.hpp"
#include "FrameBuffer.h"
#include "IEventObserver.h"
#include "Log.h"
#include "OpenGLWindow.hpp"
#include "SceneView.hpp"
#include "ShaderProgram.h"
#include "ShaderProgramManager.h"
#include "Vertices.h"
#include <VertexIndexBuffer.h>
#include <spdlog/spdlog.h>
#include <unordered_map>
#include "OpenGLViewerWidget.h"
#include "RenderEvent.h"

class RenderObserver : public IEventObserver
{
public:
  RenderObserver(std::shared_ptr<OpenGLViewerWidget> viewerWidget)
    : mViewerWidget(viewerWidget)
  {
    mShaderProgramManager = std::make_shared<ShaderProgramManager>();
  }
  bool handle(const EventObject& event) override
  {
    auto renderEvent = dynamic_cast<const RenderEvent*>(&event);
    if (!renderEvent || renderEvent->eventId() != EventId::RenderUpdateStart)
    {
      return false;
    }
    SPDLOG_DEBUG("event: {}", EventIdStr[static_cast<int>(renderEvent->eventId())]);
    
    std::unordered_map<GLenum, std::string> shaderSources;
    shaderSources[GL_VERTEX_SHADER] = R"(D:\Workspace\github\OViewerUI\Test\test.vert)";
    shaderSources[GL_FRAGMENT_SHADER] = R"(D:\Workspace\github\OViewerUI\Test\test.frag)";
    auto shaderProgram = mShaderProgramManager->getShaderProgram(shaderSources);
    SPDLOG_DEBUG("step 1");
    if (!mVetexIndexBuffer)
    {
      Vertices vertices;
      // clang-format off
    vertices.m_Data = new GLfloat[8]{
      -1.0f, -1.0f,
       1.0f, -1.0f,
       1.0f,  1.0f,
      -1.0f,  1.0f
    };
    vertices.m_Indices = new GLuint[6]{
      0, 1, 3,
      1, 2, 3
    };
      // clang-format on
      vertices.m_DataSize = 8;
      vertices.m_IndicesSize = 6;
      vertices.m_PointAttribute.first = true;
      vertices.m_PointAttribute.second = 2;
      mVetexIndexBuffer->createBuffer(vertices);
    }
SPDLOG_DEBUG("step 2");
    auto frameBuffer = mViewerWidget->renderBuffer();
SPDLOG_DEBUG("step 3");
    shaderProgram->use();
    SPDLOG_DEBUG("step 4");
    frameBuffer->bind();
    SPDLOG_DEBUG("step 5");
    mVetexIndexBuffer->draw(GL_TRIANGLES);
    SPDLOG_DEBUG("step 6");
    frameBuffer->unbind();
    SPDLOG_DEBUG("step 7");
    shaderProgram->unuse();
    SPDLOG_DEBUG("step 8");

    SPDLOG_DEBUG("draw finished");

    return true;
  }

private:
  std::shared_ptr<OpenGLViewerWidget> mViewerWidget;
  std::shared_ptr<ShaderProgramManager> mShaderProgramManager;
  std::shared_ptr<VertexIndexBuffer> mVetexIndexBuffer;
};

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
  auto renderObserver = std::make_shared<RenderObserver>(viewWidget);
  glRenderWindow->addObserver(renderObserver);

  return app.exec();
}