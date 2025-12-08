#include "OpenGLViewerWidget.h"
#include <imgui.h>
#include <glad/glad.h>

struct OpenGLViewerWidget::Private
{

};
OpenGLViewerWidget::OpenGLViewerWidget(const char* widgetNamae, int widgetFlags)
  : Widget(widgetNamae, widgetFlags)
{
}

OpenGLViewerWidget::~OpenGLViewerWidget() {}

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
