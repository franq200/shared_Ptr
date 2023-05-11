#pragma once

template <typename T>
class SharedPtr
{
public:
	SharedPtr(T* ptr);
	SharedPtr(const SharedPtr& ptr);
	~SharedPtr();
	int UseCount();
	void Reset(T* newPtr);
	T* Get();

	SharedPtr<T> operator=(const SharedPtr<T>& ptr);
	bool operator_bool() const;
	bool operator==(const SharedPtr<T>& ptr) const;
	T* operator->() const;
	T& operator*() const;
private:
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

template<typename T>
inline int SharedPtr<T>::UseCount()
{
	return *m_counter;
}

template<typename T>
inline void SharedPtr<T>::Reset(T* newPtr)
{
	delete m_ptr;
	m_ptr = newPtr;
}

template<typename T>
inline T* SharedPtr<T>::Get()
{
	return m_ptr;
}

template<typename T>
inline SharedPtr<T> SharedPtr<T>::operator=(const SharedPtr<T>& ptr)
{
	delete m_counter;
	delete m_ptr;
	m_counter = ptr.m_counter;
	m_ptr = ptr.m_ptr;
	return *this;
}

template<typename T>
inline bool SharedPtr<T>::operator_bool() const
{
	return m_ptr;
}

template<typename T>
inline bool SharedPtr<T>::operator==(const SharedPtr<T>& ptr) const
{
	return (m_ptr == ptr.m_ptr);
}

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
