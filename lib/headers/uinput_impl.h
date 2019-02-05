#pragma once

#include "stdafx.h"
#include "uinput.h"

#include <typeinfo>

namespace efiilj
{

	template<typename T>
	bool UserInput<T>::Validate(std::string input)
	{
		std::stringstream ss;
		ss << input;
		ss >> _value;

		_state = !ss.fail();
		return _state;

	}

	template<typename T>
	UserInput<T>::UserInput(std::string query, std::string prompt) : _query(query), _prompt(prompt)
	{
		static_assert(is_streamable<T>, "Type is not streamable");

		_state = false;
	}

	template<typename T>
	template<typename>
	inline UserInput<T>::UserInput(std::string query, std::string prompt, T min, T max)
	{
		Limits(min, max);
	}

	template<typename T>
	inline bool UserInput<T>::Show()
	{
		std::string input;

		std::cout << _query << "\nCtrl + Z to abort.\n";

		while (true)
		{
			std::cout << _prompt;
			std::getline(std::cin, input);

			if (input.length() == 0)
				continue;

			if (input[0] == std::char_traits<char>::eof())
				return false;

			if (Validate(input) && TestLimits())
				return true;
		}
	}

	template<typename T>
	bool UserInput<T>::operator == (bool state)
	{
		return _state;
	}

	template<typename T>
	bool UserInput<T>::operator!=(bool state)
	{
		return !_state;
	}

	template<typename T>
	UserInput<T>::~UserInput()
	{
	}

}

