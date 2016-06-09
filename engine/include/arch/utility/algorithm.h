//=================================================================================//
//                                                                                 //
//  ArchEngine                                                                     //
//                                                                                 //
//  Copyright (C) 2011-2016 Terry                                                  //
//                                                                                 //
//  This file is a portion of the ArchEngine. It is distributed under the MIT      //
//  License, available in the root of this distribution and at the following URL.  //
//  http://opensource.org/licenses/mit-license.php                                 //
//                                                                                 //
//=================================================================================//

#pragma once

#include <algorithm>
#include <vector>

namespace arch
{

template<class container_type, class predicate_type> inline void erase_if(container_type& _container, predicate_type _predicate)
{
	_container.erase(std::remove_if(_container.begin(), _container.end(), _predicate), _container.end());
}

template<class container_type, class predicate_type> inline void transform(container_type& _container, predicate_type _predicate)
{
	std::transform(_container.begin(), _container.end(), _container.begin(), _predicate);
}

template<class value_type> inline std::vector<value_type> range(value_type _end)
{
	std::vector<value_type> container;
	for (value_type value = static_cast<value_type>(0); value <= _end; value++)
	{
		container.emplace_back(value);
	}
	return container;
}

template<class value_type> inline std::vector<value_type> range(value_type _begin, value_type _end)
{
	std::vector<value_type> container;
	for (value_type value = _begin; value <= _end; value++)
	{
		container.emplace_back(value);
	}
	return container;
}

template<class value_type> inline std::vector<value_type> range(value_type _begin, value_type _end, value_type _steps)
{
	std::vector<value_type> container;
	for (value_type value = _begin; value <= _end; value += _steps)
	{
		container.emplace_back(value);
	}
	return container;
}

template<class container_type, class predicate_type> inline void combination(container_type& _container, typename container_type::size_type _n, predicate_type _predicate)
{
	using size_type = typename container_type::size_type;

	container_type tmp(_n);
	std::function<void(size_type, size_type)> make_conbination = [&](size_type _insert_index, size_type _start_index)
	{
		if (_insert_index == _n)
		{
			_predicate(tmp);
			return;
		}

		for (size_type index = _start_index; index != _container.size() - _n + _insert_index + 1; index++)
		{
			tmp[_insert_index] = _container[index];
			make_conbination(_insert_index + 1, index + 1);
		}
	};
	make_conbination(0, 0);
}

}