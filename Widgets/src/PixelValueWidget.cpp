#include "PixelValueWidget.h"
#include <imgui.h>

struct PixelValueWidget::Private
{

};

PixelValueWidget::PixelValueWidget(const char* widgetName, int widgetFlags)
  : Widget(widgetName, widgetFlags)
{
}

PixelValueWidget::~PixelValueWidget() {}

bool PixelValueWidget::render()
{
  if (ImGui::Begin(mWidgetName.c_str(), false, mWidgetFlags))
  {
    ImGui::LabelText("Image Name", "");
    ImGui::LabelText("Pixel Value", "");
  }

  ImGui::End();

  return false;
}

void PixelValueWidget::resize(int width, int height) {}
