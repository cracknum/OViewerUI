#ifndef PROPERTY_PANEL_H
#define PROPERTY_PANEL_H
#include <memory>
#include <string>
#include "WidgetsExport.h"
#include <functional>

class SceneView;

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
    SceneView &operator=(SceneView &&) noexcept ;

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

#endif