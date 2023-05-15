#pragma once

template <typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr);
	SharedPtr(const SharedPtr& ptr);
	~SharedPtr();
	int UseCount() const;
	void Reset(T* newPtr);	//
	T* Get() const;

	SharedPtr<T>& operator=(const SharedPtr<T>& ptr);	//
	//bool operator==(const SharedPtr<T>& left, const SharedPtr<Y>& right) const;
	operator bool() const;	//
	//bool operator==(const SharedPtr<T>& ptr) const;
	T* operator->() const;	//
	T& operator*() const;	//
private:
	void TryToDelete();
	T* m_ptr;
	int* m_counter = nullptr;
};

template<typename T>
inline SharedPtr<T>::SharedPtr(T* ptr) :
	m_ptr(ptr)
{
	m_counter = new int(1);
}

template<typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr& ptr) :
	m_ptr(ptr.m_ptr), m_counter(ptr.m_counter)
{
	(*m_counter)++;
}

template<typename T>
inline SharedPtr<T>::~SharedPtr()
{
	TryToDelete();
}

template<typename T>
inline int SharedPtr<T>::UseCount() const
{
	return *m_counter;
}

template<typename T>
inline void SharedPtr<T>::Reset(T* newPtr)
{
	TryToDelete();
	m_ptr = newPtr;
	m_counter = new int(1);
}

template<typename T>
inline T* SharedPtr<T>::Get() const
{
	return m_ptr;
}

template<typename T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& ptr)
{
	TryToDelete();
	m_counter = ptr.m_counter;
	m_ptr = ptr.m_ptr;
	(* m_counter)++;
	return *this;
}

template<typename T, typename Y>
inline bool operator==(const SharedPtr<T>& left, const SharedPtr<Y>& right)
{
	return left.Get() == right.Get();
}

template<typename T>
inline SharedPtr<T>::operator bool() const
{
	return m_ptr;
}

/*
template<typename T>
inline bool SharedPtr<T>::operator==(const SharedPtr<T>& ptr) const
{
	return (m_ptr == ptr.m_ptr);
}
*/

template<typename T>
inline T* SharedPtr<T>::operator->() const
{
	return m_ptr;
}

template<typename T>
inline T& SharedPtr<T>::operator*() const
{
	return *m_ptr;
}

template<typename T>
inline void SharedPtr<T>::TryToDelete()
{
	if (*m_counter > 1)
	{
		(*m_counter)--;
	}
	else
	{
		delete m_ptr;
		delete m_counter;
	}
}
