#include "LogWidget.h"
#include <imgui.h>

struct LogWidget::Private
{

};

LogWidget::LogWidget(const char* widgetName, int widgetFlag)
  : Widget(widgetName, widgetFlag)
{
}

LogWidget::~LogWidget() {}

bool LogWidget::render()
{
    if (ImGui::Begin(mWidgetName.c_str(), false, mWidgetFlags))
    {
        /* code */
    }
    ImGui::End();    
  return true;
}

void LogWidget::resize(int width, int height) {}
