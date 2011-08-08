#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <assert.h>
#include <stdio.h>

//***************************************************************************************************************

template <typename TYPE>
class CSingleton
{
public:
	class Guard
	{
	public:
		Guard()
		{
			assert(!s_instance);
			s_instance = new TYPE();
		}

		template<typename ARG>
		Guard(ARG arg)
		{
			assert(!s_instance);
			s_instance = new TYPE(arg);
		}

		~Guard()
		{
			assert(s_instance);
			delete s_instance;
			s_instance = NULL;
		}
	};

	static TYPE * Get()
	{
		assert(s_instance);
		return s_instance;
	}

	explicit CSingleton()
	{}
	virtual ~CSingleton()
	{}

private:
	static TYPE * s_instance;
};

//***************************************************************************************************************

template<typename TYPE>
TYPE * CSingleton<TYPE>::s_instance = 0;

//***************************************************************************************************************

#endif
