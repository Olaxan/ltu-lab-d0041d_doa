#pragma once

#include <limits>
#include <type_traits>
#include <sstream>
#include <string>
#include <iostream>

namespace efiilj
{

	template<class, class = std::void_t<>>
	struct is_streamable : std::false_type {};

	template<class T>
	struct is_streamable<T,
		std::void_t<decltype(std::declval<std::istream&>() >> std::declval<T&>())>
	> : std::true_type { };

	template <typename T>
	class UserInput
	{
	private:
		std::string _error;
		std::string _prompt;
		std::string _query;
		bool _state;
		T _value, _min, _max;

		bool Validate(std::string input);

		template<typename U = T>
		typename std::enable_if<std::is_arithmetic<U>::value, bool>::type
			TestLimits() { return (_value >= _min && _value <= _max); }

		template<typename U = T>
		typename std::enable_if<!std::is_arithmetic<U>::value, bool>::type
			TestLimits() { return true; }

	public:
		UserInput(std::string query, std::string prompt);

		template <typename = std::enable_if_t<std::is_arithmetic<T>::value>>
		UserInput(std::string query, std::string prompt, T min, T max);

		template <typename = std::enable_if_t<std::is_arithmetic<T>::value>>
		inline void Limits(T min, T max)
		{
			_min = min;
			_max = max;
		}

		bool Show(); // Non-comparable

		T Value() { return _value; };

		bool operator == (bool state);
		bool operator != (bool state);

		~UserInput();
	};
}

#include "uinput_impl.h"

