#ifndef RENDER_CONTEXT_H
#define RENDER_CONTEXT_H

class IWindow;

class GL_API RenderContext
{
public:
  virtual ~RenderContext() = default;
  RenderContext()
    : mWindow(nullptr)
  {
  }

  virtual bool init(IWindow* window)
  {
    mWindow = window;
    return true;
  }

  virtual void preRender() = 0;
  virtual void postRender() = 0;
  virtual void end() = 0;

protected:
  IWindow* mWindow;
};
#endif // RENDER_CONTEXT_H