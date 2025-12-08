#ifndef OPENGL_VIEWER_WIDGET_UI
#define OPENGL_VIEWER_WIDGET_UI
#include "Widget.h"
#include "WidgetsExport.h"
#include <memory>

class WIDGETS_API OpenGLViewerWidget final : public Widget
{
public:
  OpenGLViewerWidget(const char* widgetNamae, int widgetFlags = 0);
  ~OpenGLViewerWidget();

  bool Render() override;

private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // OPENGL_VIEWER_WIDGET_UI