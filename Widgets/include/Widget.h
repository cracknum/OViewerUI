#ifndef WIDGET_H
#define WIDGET_H
#include "UIObject.h"
class Widget : public UIObject{
public:
  virtual bool Render() = 0;
  ~Widget() override;
};

#endif // WIDGET_H
