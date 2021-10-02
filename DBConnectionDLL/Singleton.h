#pragma once


template<class T>
class CSingleton
{
private:
	static T* m_instance;
	
public:
	
	static T* Instance()
	{
		if (m_instance == nullptr)
		{
			if (m_instance == nullptr)
			{
				m_instance = new T;
			}
		}
		return m_instance;
	}

protected:
	
	CSingleton()
	{
	}

	virtual ~CSingleton()
	{
	}
};

template <class T>
T* CSingleton<T>::m_instance = nullptr;