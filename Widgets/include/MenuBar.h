#ifndef MENUBAR_H
#define MENUBAR_H
#include "Widget.h"
#include <memory>
#include <string>
#include <vector>
#include "WidgetsExport.h"
class WIDGETS_API MenuBar final : public Widget
{
public:
  class Menu
  {
  public:
    class Item
    {
    public:
      void setName(const std::string& name);

    private:
      friend class MenuBar;
      std::string mName;
    };

  public:
    void setName(const std::string& name);
    void addItem(const Item& item);

  private:
    friend class MenuBar;
    std::string mName;
    std::vector<Item> mMenuItems;
  };

public:
  MenuBar();
  ~MenuBar() override;
  bool Render() override;

  void addMenu(const Menu& item);

private:
  struct Impl;
  std::unique_ptr<Impl> mImpl;
};

#endif // MENUBAR_H
