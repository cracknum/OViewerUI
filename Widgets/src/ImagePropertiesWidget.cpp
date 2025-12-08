#include "ImagePropertiesWidget.h"
#include <imgui.h>

struct ImagePropertiesWidget::Private
{

};

ImagePropertiesWidget::ImagePropertiesWidget(const char* widgetName, int widgetFlags)
  : AbstractPropertiesWidget(widgetName, widgetFlags)
{
}

ImagePropertiesWidget::~ImagePropertiesWidget() {}

bool ImagePropertiesWidget::Render()
{
  if (ImGui::Begin(mWidgetName.c_str(), false, mWidgetFlags))
  {
    /* code */
  }
  ImGui::End();
  return true;
}
