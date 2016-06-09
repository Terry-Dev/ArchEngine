#pragma once

namespace arch
{

namespace win32
{

template<class T>
class com_ptr final
{
public:
	com_ptr();
	explicit com_ptr(T* ptr);
	com_ptr(const com_ptr& ptr);
	~com_ptr();

	T* get() const;
	T*& ptr();
	T*& released_ptr();
	void reset();
	T* operator ->();
	T* operator ->() const;
	T& operator *();
	const T& operator *() const;
	com_ptr& operator =(T* ptr);
	com_ptr& operator =(const com_ptr& ptr);
	bool operator ==(const T* ptr) const;
	bool operator !=(const T* ptr) const;

private:
	T* m_ptr;
};

template<class T> inline com_ptr<T>::com_ptr()
: m_ptr(nullptr)
{
}

template<class T> inline com_ptr<T>::com_ptr(T* ptr)
: m_ptr(ptr)
{
	if (m_ptr != nullptr)
	{
		m_ptr->AddRef();
	}
}

template<class T> inline com_ptr<T>::com_ptr(const com_ptr& ptr)
: m_ptr(ptr.m_ptr)
{
	if (m_ptr != nullptr)
	{
		m_ptr->AddRef();
	}
}

template<class T> inline com_ptr<T>::~com_ptr()
{
	reset();
}

template<class T> inline T* com_ptr<T>::get() const
{
	if (m_ptr != nullptr)
	{
		m_ptr->AddRef();
	}
	return m_ptr;
}

template<class T> inline T*& com_ptr<T>::ptr()
{
	return m_ptr;
}

template<class T> inline T*& com_ptr<T>::released_ptr()
{
	reset();
	return m_ptr;
}

template<class T> inline void com_ptr<T>::reset()
{
	if (m_ptr != nullptr)
	{
		m_ptr->Release();
		m_ptr = nullptr;
	}
}

template<class T> inline T* com_ptr<T>::operator ->()
{
	return m_ptr;
}

template<class T> inline T* com_ptr<T>::operator ->() const
{
	return m_ptr;
}

template<class T> inline T& com_ptr<T>::operator *()
{
	return *m_ptr;
}

template<class T> inline const T& com_ptr<T>::operator *() const
{
	return *m_ptr;
}

template<class T> inline com_ptr<T>& com_ptr<T>::operator =(T* ptr)
{
	if (ptr != nullptr)
	{
		ptr->AddRef();
	}

	if (m_ptr != nullptr)
	{
		m_ptr->Release();
	}

	m_ptr = ptr;

	return *this;
}

template<class T> inline com_ptr<T>& com_ptr<T>::operator =(const com_ptr& ptr)
{
	if (ptr != nullptr)
	{
		ptr->AddRef();
	}

	if (m_ptr != nullptr)
	{
		m_ptr->Release();
	}

	m_ptr = ptr.m_ptr;

	return *this;
}

template<class T> inline bool com_ptr<T>::operator ==(const T* ptr) const
{
	return m_ptr == ptr;
}

template<class T> inline bool com_ptr<T>::operator !=(const T* ptr) const
{
	return m_ptr != ptr;
}

}

}