#ifndef INTERFACE_EVENT_LISTENER_H
#define INTERFACE_EVENT_LISTENER_H

class EventObject;
class IEventListener
{
public:
  virtual bool handle(const EventObject& event) = 0;
  virtual ~IEventListener() = default;
};

#endif // INTERFACE_EVENT_LISTENER_H
