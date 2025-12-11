#include "OpenGLViewerWidget.h"
#include "MouseEvent.h"
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

    if (ImGui::IsWindowHovered())
    {
      handleInput();
    }
  }
  ImGui::End();
  ImGui::PopStyleVar(3); // 弹出样式设置
  return true;
}

void OpenGLViewerWidget::resize(int width, int height)
{
  if (mPrivate->mFrameBuffer->textureWidth() - width != 0 || mPrivate->mFrameBuffer->textureHeight() - height != 0)
  {
    mPrivate->mFrameBuffer->updateBufferSize(width, height);
    SPDLOG_DEBUG("resize framebuffer");
  }
}

std::shared_ptr<FrameBuffer> OpenGLViewerWidget::renderBuffer()
{
  return mPrivate->mFrameBuffer;
}

void OpenGLViewerWidget::mousePressCheck()
{
  if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
  {
    auto& io = ImGui::GetIO();

    auto buttonPos = io.MouseClickedPos[ImGuiMouseButton_Left];
    auto eventData = std::make_unique<MousePressedData>(buttonPos, ImGuiMouseButton_Left);
    this->invokeEvent(MouseEvent(EventId::MousePressed, std::move(eventData)));

    SPDLOG_DEBUG("mouse left button clicked");
  }
}

void OpenGLViewerWidget::mouseMoveCheck()
{
  auto& io = ImGui::GetIO();
  if (!ImGui::IsAnyMouseDown() && (fabsf(io.MouseDelta.x) > 1e-6 || fabsf(io.MouseDelta.y) > 1e-6))
  {
    ImVec2 mousePos = io.MousePos;
    ImVec2 preMousePos = io.MousePosPrev;

    auto eventData = std::make_unique<MouseMoveData>(mousePos, preMousePos);
    this->invokeEvent(MouseEvent(EventId::MouseMove, std::move(eventData)));
    SPDLOG_DEBUG("mouse move");
  }
}

void OpenGLViewerWidget::mouseDragCheck()
{
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Left))
  {
    auto& io = ImGui::GetIO();
    ImVec2 accumulateDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Left);
    auto eventData = std::make_unique<MouseDragData>(accumulateDelta, ImGuiMouseButton_Left);
    this->invokeEvent(MouseEvent(EventId::MouseDrag, std::move(eventData)));

    SPDLOG_DEBUG("mouse draging");
  }
}

void OpenGLViewerWidget::mouseReleaseCheck()
{
  if (ImGui::IsMouseReleased(ImGuiMouseButton_Left))
  {
    this->invokeEvent(MouseEvent(EventId::MouseRelease, std::make_unique<MouseReleaseData>()));
    SPDLOG_DEBUG("mouse left button released");
  }
}

void OpenGLViewerWidget::handleInput()
{
  mousePressCheck();
  mouseDragCheck();
  mouseMoveCheck();
  mouseReleaseCheck();
}
