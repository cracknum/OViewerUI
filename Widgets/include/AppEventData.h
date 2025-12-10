#ifndef APP_EVENT_DATA_H
#define APP_EVENT_DATA_H
#include "EventData.h"
class AppExitData : public EventData
{
public:
  AppExitData() = default;
  ~AppExitData() = default;
};
#endif // APP_EVENT_DATA_H