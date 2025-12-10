#ifndef EVENT_ID_H
#define EVENT_ID_H
#include <string>
enum class EventId
{
  FileOpened,
  FileClosed,
  MenuItemClicked,
  RenderUpdate,
  //-------------- mouse event------------------
  MousePressed,
  MouseMove,
  MouseRelease,
  MouseDrag,
  WheelForward,
  WheelBackward,
  //-------------- mouse event------------------
  CustomEvent
};

inline std::vector<std::string> EventIdStr = { "FileOpened", "FileClosed", "MenuItemClicked",
  "RenderUpdate", "MousePressed", "MouseMove", "MouseRelease", "MouseDrag", "MouseForward", "MouseBackward"};

#endif // EVENT_ID_H
