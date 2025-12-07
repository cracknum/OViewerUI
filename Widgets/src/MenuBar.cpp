#include "MenuBar.h"
#include <imgui.h>
#include <utility>
#include <vector>
#include <spdlog/spdlog.h>
#include "EventId.h"

struct MenuBar::Impl final
{
  std::vector<Menu> mMenus;
};

MenuItemClicked::MenuItemClicked(const EventId& eventId, std::unique_ptr<EventData> eventData)
  : EventObject(eventId, std::move(eventData))
{
}
MenuItemData::MenuItemData(std::string  menuItemName)
  :mMenuItemName(std::move(menuItemName))
{}
std::string MenuItemData::menuItemName() const
{
  return mMenuItemName;
}
MenuBar::Menu::Item::Item(std::string  name, const std::shared_ptr<IEventObserver>& observer)
  :mName(std::move(name))
{
  addObserver(observer);
}
void MenuBar::Menu::setName(const std::string& name)
{
  this->mName = name;
}
void MenuBar::Menu::addItem(const Item& item)
{
  this->mMenuItems.push_back(item);
}
MenuBar::MenuBar()
{
  mImpl = std::make_unique<Impl>();
}
MenuBar::~MenuBar() = default;
bool MenuBar::Render()
{
  // BeginMainMenuBar()无论成功还是失败都需要调用EndMainMenuBar
  if (ImGui::BeginMainMenuBar())
  {
    // BeginMenu()只有成功后才需要调用EndMenu()
    for (auto& menu : mImpl->mMenus)
    {
      if (ImGui::BeginMenu(menu.mName.c_str()))
      {
        for (auto& item: menu.mMenuItems)
        {
          if (ImGui::MenuItem(item.mName.c_str()))
          {
            item.invokeEvent(MenuItemClicked(EventId::MenuItemClicked, std::make_unique<MenuItemData>(item.mName)));
          }
        }
        ImGui::EndMenu();
      }
    }
  }
  ImGui::EndMainMenuBar();

  return true;
}
void MenuBar::addMenu(const Menu& item)
{
  mImpl->mMenus.push_back(item);
}