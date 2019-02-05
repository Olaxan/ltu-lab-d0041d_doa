#pragma once

#ifdef UTILSLIB_EXPORTS
#define UTILSLIB_API __declspec(dllexport)
#else
#define UTILSLIB_API __declspec(dllimport)
#endif

#include "utilslib.h"

#include <string>
#include <vector>

namespace efiilj
{
	
	class UTILSLIB_API Menu
	{
	private:

		class UTILSLIB_API MenuItem
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

			//friend class Menu;
		};

		std::vector<MenuItem> _items;
		bool _isSubmenu = false;

		//friend class MenuItem;

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

