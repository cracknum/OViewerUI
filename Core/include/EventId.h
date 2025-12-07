#ifndef EVENT_ID_H
#define EVENT_ID_H
#include <string>
enum class EventId
{
  FileOpened,
  FileClosed,
  MenuItemClicked,
  RenderUpdate,
  CustomEvent
};

inline std::vector<std::string> EventIdStr = { "FileOpened", "FileClosed", "MenuItemClicked",
  "RenderUpdate" };

#endif // EVENT_ID_H
