#include "Application.hpp"
#include "Log.h"
int main(int argc, char** argv)
{
  Application app(argc, argv);
  Log::initLog(spdlog::level::debug);

  app.loop();
  return 0;
}