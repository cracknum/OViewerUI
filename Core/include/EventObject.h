#ifndef INTERFACE_EVENT_OBJECT_H
#define INTERFACE_EVENT_OBJECT_H
#include <memory>
class UIObject;
class EventObject
{
public:
  EventObject()
    : m_Caller(nullptr)
  {
  }
  explicit EventObject(const std::shared_ptr<UIObject>& caller)
    : m_Caller(caller)
  {
  }
  std::shared_ptr<UIObject> caller()
  {
    return m_Caller;
  }

protected:
  std::shared_ptr<UIObject> m_Caller;
};
#endif // INTERFACE_EVENT_OBJECT_H
