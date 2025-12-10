#include "OpenGLViewerWidget.h"
#include "FrameBuffer.h"
#include <imgui.h>
#include <spdlog/spdlog.h>


struct OpenGLViewerWidget::Private
{
  std::shared_ptr<FrameBuffer> mFrameBuffer;

  Private() { mFrameBuffer = std::make_shared<FrameBuffer>(1, 1); }
};
OpenGLViewerWidget::OpenGLViewerWidget(const char* widgetNamae, int widgetFlags)
  : Widget(widgetNamae, widgetFlags)
{
  mPrivate = std::make_unique<Private>();
}

OpenGLViewerWidget::~OpenGLViewerWidget() = default;

bool OpenGLViewerWidget::render()
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

void OpenGLViewerWidget::resize(int width, int height)
{
  mPrivate->mFrameBuffer->updateBufferSize(width, height);
}
