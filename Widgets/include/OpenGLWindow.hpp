#ifndef WINDOW_H
#define WINDOW_H
#include "WidgetsExport.h"
#include "IWindow.hpp"
#include <memory>
#include <string>

struct WindowPrivate;

class WIDGETS_API OpenGLWindow final: public IWindow
{
public:
    OpenGLWindow();
    ~OpenGLWindow() override;

    bool init(int width, int height, const std::string& title);
    void render();
    void handleInput();
    [[nodiscard]] bool isRunning() const;
    void *getNativeWindow() override;
    void setNativeWindow(void *window) override;
    void onResize(int width, int height) override;
    void close() override;

private:
    std::unique_ptr<WindowPrivate> mPrivate;
};
#endif // WINDOW_H