#include "stdafx.h"
#include "menu.h"
#include "uinput.h"

#include <iostream>

namespace efiilj
{

	Menu::Menu(std::string title, std::string prompt) : title(title), prompt(prompt) { }

	bool Menu::Show() const
	{
		///Show menu, loop until the user exits from the top-level menu.

		std::cout << "\n";

		while (true)
		{
			if (title != "")
			{
				std::cout << title << "\n\n";
			}

			ListItems();
			
			UserInput<int> input = UserInput<int>("", prompt, 1 - allowExit, _items.size());

			if (input.Show())
			{
				std::cout << "\n";
				if (input.Value() == 0 || _items[input.Value() - 1].Invoke()) //Invoke menu item, depending on type (submenu/function pointer).
					return true;
			}
			else return false;

			std::cout << "\n";
		}
	}

	void Menu::AddItem(std::string name, bool(*func)())
	{
		_items.push_back(MenuItem(this, name, func));
	}

	void Menu::AddItem(std::string name, Menu* subMenu)
	{
		subMenu->_isSubmenu = true;
		_items.push_back(MenuItem(this, name, subMenu));
	}

	void Menu::ListItems() const
	{
		int i = 1;
		for (auto it = _items.begin(); it != _items.end(); it++)
		{
			std::cout << i << ". " << it->name << "\n";
			i++;
		}
		if (allowExit)
		{
			if (_isSubmenu)
				std::cout << "0. Back\n";
			else
				std::cout << "0. Quit\n";
		}
	}

	Menu::~Menu() { }
}

