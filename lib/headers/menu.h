#pragma once

#include <string>
#include <vector>

namespace efiilj
{
	
	class Menu
	{
	private:

		class MenuItem
		{
		private:
			Menu* subMenu;
			const Menu* parent;
			bool(*func)();
			bool hasSubmenu;

		public:
			MenuItem();
			MenuItem(const Menu* parent, std::string name, bool(*func)());
			MenuItem(const Menu* parent, std::string name, Menu* subMenu);

			std::string name;

			bool Invoke() const;

		};

		std::vector<MenuItem> _items;
		bool _isSubmenu = false;

	public:
		Menu(std::string title = "", std::string prompt = "> ");

		std::string title;
		std::string prompt;
		
		bool allowExit = true;

		void AddItem(std::string name, bool(*func)());
		void AddItem(std::string name, Menu* subMenu);
		void RemoveItem(std::string item);
		void ListItems() const;
		
		bool Show() const;

		~Menu();

		//This is probably very bad
		friend std::hash<MenuItem>;
	};

}

