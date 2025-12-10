#include "OpenGLViewerWidget.h"
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
    unsigned int texture = mPrivate->mFrameBuffer->texture();
    int width = mPrivate->mFrameBuffer->textureWidth();
    int height = mPrivate->mFrameBuffer->textureHeight();

    if (texture == 0 || width <= 0 || height <= 0)
      return false; // 安全检查

    ImVec2 canvasSize = ImGui::GetContentRegionAvail();
    if (canvasSize.x <= 0 || canvasSize.y <= 0)
      return false;

    // 计算保持宽高比的缩放因子
    float scale = std::min(canvasSize.x / (float)width, canvasSize.y / (float)height);
    ImVec2 imageSize = ImVec2(width * scale, height * scale);

    // 获取当前光标位置
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // 计算居中偏移量
    float offsetX = (canvasSize.x - imageSize.x) / 2;
    float offsetY = (canvasSize.y - imageSize.y) / 2;

    // 设置新的光标位置以居中图像
    ImGui::SetCursorScreenPos(ImVec2(pos.x + offsetX, pos.y + offsetY));

    ImTextureID textureId(texture);
    ImGui::Image(textureId, imageSize, ImVec2(0, 1), ImVec2(1, 0));

    // 恢复原始光标位置（如果需要）
    ImGui::SetCursorScreenPos(pos);
  }
  ImGui::End();
  ImGui::PopStyleVar(3); // 弹出样式设置
  return true;
}

void OpenGLViewerWidget::resize(int width, int height)
{
  mPrivate->mFrameBuffer->updateBufferSize(width, height);
}

std::shared_ptr<FrameBuffer> OpenGLViewerWidget::renderBuffer()
{
  return mPrivate->mFrameBuffer;
}
