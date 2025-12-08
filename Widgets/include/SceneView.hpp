#ifndef PROPERTY_PANEL_H
#define PROPERTY_PANEL_H
#include <memory>
#include "WidgetsExport.h"
#include "OpenGLViewerWidget.h"

struct ImGuiContext;

class WIDGETS_API SceneView
{
public:
    explicit SceneView(ImGuiContext* context);
    ~SceneView();

    void render(SceneView *mScene = nullptr) const;

    SceneView(const SceneView &) = delete;
    SceneView &operator=(const SceneView &) = delete;

    SceneView(SceneView &&) noexcept ;
    SceneView &operator=(SceneView &&) noexcept;
    std::shared_ptr<OpenGLViewerWidget> viewerWidget();

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

#endif