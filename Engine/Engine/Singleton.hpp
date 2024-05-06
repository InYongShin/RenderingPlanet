#ifndef SINGLETON_HPP
#define SINGLETON_HPP


template <typename T>
class Singleton
{
private:
	static T* instance;

protected:
	Singleton() {}
	virtual ~Singleton() {}

public:
	static T* getInstance()
	{
		if (instance == nullptr)
		{
			instance = new T();
		}

		return instance;
	}

	static void destroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
};

template <typename T> T* Singleton<T>::instance = nullptr;


#endif /* SINGLETON_HPP */
