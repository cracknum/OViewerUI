#include "MenuBar.h"
#include <imgui.h>
#include <vector>
#include <spdlog/spdlog.h>

struct MenuBar::Impl final
{
  std::vector<Menu> mMenus;
};

void MenuBar::Menu::Item::setName(const std::string& name)
{
  this->mName = name;
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
    for (const auto& menu : mImpl->mMenus)
    {
      if (ImGui::BeginMenu(menu.mName.c_str()))
      {
        for (const auto& item: menu.mMenuItems)
        {
          if (ImGui::MenuItem(item.mName.c_str()))
          {
            SPDLOG_DEBUG("item clicked: {}.{}", menu.mName, item.mName);
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