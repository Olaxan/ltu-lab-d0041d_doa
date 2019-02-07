#pragma once

#include <limits>
#include <type_traits>
#include <sstream>
#include <string>
#include <iostream>

namespace efiilj
{

	template<typename S, typename T, typename = void>
	struct is_stream_extractable : std::false_type {};

	template<typename S, typename T>
	struct is_stream_extractable<S, T,
		std::void_t<  decltype(std::declval<S&>() >> std::declval<T>())  > >
		: std::true_type {};

	template<typename S, typename T, typename = void>
	struct is_stream_insertable : std::false_type {};

	template<typename S, typename T>
	struct is_stream_insertable<S, T,
		std::void_t<  decltype(std::declval<S&>() << std::declval<T>())  > >
		: std::true_type {};

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

		std::string exit;

		bool Show();

		T Value() { return _value; };

		bool operator == (bool state) { return _state; }
		bool operator != (bool state) { return !_state; }
		explicit operator bool() const { return _state; }

		~UserInput();
	};
}

#include "uinput_impl.h"

