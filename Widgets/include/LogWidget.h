#ifndef LOG_WIDGET
#define LOG_WIDGET
#include "Widget.h"
#include <memory>
#include "WidgetsExport.h"
class WIDGETS_API LogWidget final : public Widget
{
public:
  LogWidget(const char* widgetName, int widgetFlag = 0);
  ~LogWidget();

  bool Render() override;

private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // LOG_WIDGET