#include "stdafx.h"
#include "menu.h"

//Implement hashing functions
namespace std
{
	template <>
	struct hash<efiilj::Menu::MenuItem>
	{
		size_t operator()(const efiilj::Menu::MenuItem& i) const
		{
			//Return hash of all (important) fields.
			return hash<string>()(i.name);
		}
	};
}

namespace efiilj
{
	Menu::MenuItem::MenuItem() : parent(nullptr), name(""), hasSubmenu(false) { }
	Menu::MenuItem::MenuItem(const Menu* parent, std::string name, bool(*func)()) : parent(parent), name(name), func(func), hasSubmenu(false) { }
	Menu::MenuItem::MenuItem(const Menu* parent, std::string name, Menu* subMenu) : parent(parent), name(name), subMenu(subMenu), hasSubmenu(true) { }

	bool Menu::MenuItem::Invoke() const
	{
		///Execute menu option - show submenu if one, otherwise run provided function.
		if (hasSubmenu)
		{
			this->subMenu->Show();
			return false;
		}
		else
			return this->func();
	}
}