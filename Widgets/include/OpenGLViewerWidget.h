#ifndef OPENGL_VIEWER_WIDGET_UI
#define OPENGL_VIEWER_WIDGET_UI
#include "Widget.h"
#include "WidgetsExport.h"
#include <memory>

class WIDGETS_API OpenGLViewerWidget final : public Widget
{
public:
  explicit OpenGLViewerWidget(const char* widgetNamae, int widgetFlags = 0);
  ~OpenGLViewerWidget() override;

  bool render() override;
  void resize(int width, int height) override;

private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // OPENGL_VIEWER_WIDGET_UI