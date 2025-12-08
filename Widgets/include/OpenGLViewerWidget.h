#ifndef OPENGL_VIEWER_WIDGET_UI
#define OPENGL_VIEWER_WIDGET_UI
#include "Widget.h"
#include "WidgetsExport.h"
#include <memory>

class Renderer;

class WIDGETS_API OpenGLViewerWidget final : public Widget
{
public:
  OpenGLViewerWidget(const char* widgetNamae, int widgetFlags = 0);
  ~OpenGLViewerWidget();

  bool Render() override;

  void addRenderer(const std::shared_ptr<Renderer>& renderer);
  void removeRenderer(const Renderer* renderer);
private:
  struct Private;
  std::unique_ptr<Private> mPrivate;
};
#endif // OPENGL_VIEWER_WIDGET_UI