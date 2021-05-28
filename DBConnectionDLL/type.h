#pragma once
#include <type_traits>
#include <string>

namespace NetworkCommon
{
	namespace Type
	{
		template<typename T>
		struct check_type
			: std::false_type
		{
		};


		template<>
		struct check_type<int>
			: std::true_type
		{ // determine whether T is type that we want
		};

		template<>
		struct check_type<float>
			: std::true_type
		{ // determine whether T is type that we want
		};


		template<>
		struct check_type<std::string>
			: std::true_type
		{ // determine whether T is type that we want
		};
	}
}