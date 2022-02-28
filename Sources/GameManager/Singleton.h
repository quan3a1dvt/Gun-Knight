#pragma once

template <class T>
class CSingleton
{
public:
	static T* GetInstance()
	{
		if (s_instance == nullptr)
			s_instance = new T();
		return s_instance;
	}

	static bool HasInstance()
	{
		return s_instance != 0;
	}
	static void FreeInstance()
	{
		if (s_instance)
		{
			delete s_instance;
		}
	}
protected:
	CSingleton()
	{
	}
	virtual ~CSingleton()
	{
		delete s_instance;
	}
private:
	static T* s_instance;
};

template <class T> T* CSingleton<T>::s_instance = nullptr;

