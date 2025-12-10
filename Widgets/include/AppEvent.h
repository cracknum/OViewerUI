#ifndef APP_EVENT_H
#define APP_EVENT_H
#include "EventData.h"
#include "EventId.h"
#include "EventObject.h"
#include <memory>

class AppEvent : public EventObject
{
public:
  AppEvent(const EventId& eventId, std::unique_ptr<EventData> eventData)
    : EventObject(eventId, std::move(eventData))
  {
  }
  ~AppEvent() = default;
};
#endif // APP_EVENT_H