#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H
#include "GLExport.h"
#include "RenderContext.hpp"

class IWindow;

class GL_API OpenGLContext final : public RenderContext
{
public:
    using superclass = RenderContext;
    bool init(IWindow *window) override;

    void preRender() override;

    void postRender() override;

    void end() override;
};
#endif // OPENGL_CONTEXT_H