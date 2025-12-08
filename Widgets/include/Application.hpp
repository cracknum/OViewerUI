#ifndef OPENGL_IMGUI_APPLICATION
#define OPENGL_IMGUI_APPLICATION
#include "WidgetsExport.h"
#include <memory>
#include <string>

struct ApplicationPrivate;

class WIDGETS_API Application
{
public:
    Application(int argc, char **argv);
    ~Application();

    void setWindowIcon(const std::string& iconPath);

    bool exec();

    static std::string getExecutableDir();

private:
    std::unique_ptr<ApplicationPrivate> mPrivate;
};

#endif // OPENGL_IMGUI_APPLICATION