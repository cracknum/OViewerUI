#ifndef IMAGE_NAVIGATOR_WIDGET
#define IMAGE_NAVIGATOR_WIDGET
#include "Widget.h"
#include <memory>
#include "WidgetsExport.h"

class WIDGETS_API ImageNavigatorWidget : public Widget
{
public:
  ImageNavigatorWidget(const char* widgetName, int widgetFlags = 0);
  ~ImageNavigatorWidget();

  bool Render() override;

private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // IMAGE_NAVIGATOR_WIDGET
