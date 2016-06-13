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

#include <memory>

namespace arch
{

template<class T>
class singleton
{
public:
	static void create()
	{
		if (m_instance != nullptr)
		{
			return;
		}

		m_instance = std::make_unique<T>();
	}

	static void destroy()
	{
		m_instance.reset();
	}

	static T* get_instance()
	{
		return m_instance.get();
	}

protected:
	virtual ~singleton() {};

private:
	static std::unique_ptr<T> m_instance;
};

template<class T> std::unique_ptr<T> singleton<T>::m_instance;

}