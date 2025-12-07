#include "../Widgets/include/Application.hpp"
int main(int argc, char** argv)
{
    Application app(argc, argv);
    app.loop();
    return 0;
}