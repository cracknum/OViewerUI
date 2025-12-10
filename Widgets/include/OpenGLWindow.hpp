#ifndef WINDOW_H
#define WINDOW_H
#include "WidgetsExport.h"
#include <IWindow.hpp>
#include <memory>
#include <string>
#include "SceneView.hpp"
#include "UIObject.h"

struct WindowPrivate;

class WIDGETS_API OpenGLWindow final: public IWindow, public Widget
{
public:
    OpenGLWindow();
    ~OpenGLWindow() override;

    bool init(int width, int height, const std::string& title);
    bool Render() override;
    void handleInput();
    [[nodiscard]] bool isRunning() const;
    void *getNativeWindow() override;
    void setNativeWindow(void *window) override;
    void onResize(int width, int height) override;
    void resize(int width, int height) override;
    void fullScreen() override;
    void maximum() override;
    void close() override;
    void setWindowIcon(const std::string& iconPath) override;
    std::shared_ptr<SceneView> sceneView();
    void exit() override;

    void mousePressCheck();
    void mouseMoveCheck();
    void mouseDragCheck();
    void mouseReleaseCheck();

private:
    std::unique_ptr<WindowPrivate> mPrivate;
};
#endif // WINDOW_H