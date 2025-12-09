#include "OpenGLViewerWidget.h"
#include <imgui.h>

struct OpenGLViewerWidget::Private
{
  std::vector<std::shared_ptr<Renderer>> mRenderers;
};
OpenGLViewerWidget::OpenGLViewerWidget(const char* widgetNamae, int widgetFlags)
  : Widget(widgetNamae, widgetFlags)
{
  mPrivate = std::make_unique<Private>();
}

OpenGLViewerWidget::~OpenGLViewerWidget() = default;

bool OpenGLViewerWidget::Render()
{
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);            // 无边框
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f)); // 无边界
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);              // 无圆角

  if (ImGui::Begin(mWidgetName.c_str(), nullptr, mWidgetFlags))
  {

  }
  ImGui::End();
  ImGui::PopStyleVar(3); // 弹出样式设置
  return false;
}

void OpenGLViewerWidget::addRenderer(const std::shared_ptr<Renderer>& renderer)
{
  mPrivate->mRenderers.push_back(renderer);
}

void OpenGLViewerWidget::removeRenderer(const Renderer* renderer)
{
  auto it = std::find_if(mPrivate->mRenderers.begin(), mPrivate->mRenderers.end(),
    [renderer](const std::shared_ptr<Renderer>& readyRenderer)
    { return renderer == readyRenderer.get(); });
  
  if (it == mPrivate->mRenderers.end())
  {
    return;
  }

  mPrivate->mRenderers.erase(it);
}
