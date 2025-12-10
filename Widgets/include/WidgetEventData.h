#ifndef WIDGET_EVENT_DATA_H
#define WIDGET_EVENT_DATA_H
#include "EventData.h"
#include <imgui.h>
class WidgetResizeData : public EventData
{
public:
  WidgetResizeData(const ImVec2& widgetSize)
    : mWidgetSize(widgetSize)
  {
  }

  ImVec2 widgetSize() const { return mWidgetSize; }

private:
  ImVec2 mWidgetSize;
};

#endif // WIDGET_EVENT_DATA_H