#ifndef WIDGET_H
#define WIDGET_H
#include "UIObject.h"
#include "WidgetsExport.h"
class WIDGETS_API Widget : public UIObject{
public:
  virtual bool Render() = 0;
  ~Widget() override = default;
};

#endif // WIDGET_H
