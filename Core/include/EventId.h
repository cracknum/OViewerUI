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
  //-------------- widget event-----------------
  WidgetResize,
  //-------------- widget event-----------------
  //-------------- app event--------------------
  Exit,
  //-------------- app event--------------------
  CustomEvent
};

// clang-format off
inline std::vector<std::string> EventIdStr = { 
  "FileOpened", "FileClosed", "MenuItemClicked",
  "RenderUpdate", 
  "MousePressed", "MouseMove", "MouseRelease", "MouseDrag", "MouseForward", "MouseBackward",
  "WidgetResize",
  "Exit"
};

// clang-format on

#endif // EVENT_ID_H
