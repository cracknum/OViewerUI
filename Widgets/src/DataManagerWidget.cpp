#include "DataManagerWidget.h"
#include <imgui.h>
#include <string>

struct DataManagerWidget::Private
{
};

DataManagerWidget::DataManagerWidget(const char* widgetName, int widgetFlags /*= 0*/)
  : Widget(widgetName, widgetFlags)
{
}

DataManagerWidget::~DataManagerWidget() {}

bool DataManagerWidget::Render()
{
  if (ImGui::Begin(mWidgetName.c_str(), false, mWidgetFlags))
  {
    if (ImGui::TreeNode("data1"))
    {
        if (ImGui::TreeNode("data1.data1"))
        {
            ImGui::Text("data");
            ImGui::TreePop();
        }
        ImGui::TreePop();
    }
  }
  ImGui::End();

  return true;
}
