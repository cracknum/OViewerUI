#ifndef UI_CONTEXT_H
#define UI_CONTEXT_H
#include "GLExport.h"
#include "RenderContext.hpp"

struct ImGuiContext;

class GL_API UIContext : public RenderContext
{
public:
    using superclass = RenderContext;
    bool init(IWindow *window) override;
    ImGuiContext *UIContext::GetContext();
    void preRender() override;
    void postRender() override;
    void end() override;
};
#endif // UI_CONTEXT_H