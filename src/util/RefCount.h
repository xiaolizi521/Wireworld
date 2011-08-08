#ifndef __REFCOUNT_H__
#define __REFCOUNT_H__

#include <boost/noncopyable.hpp>

//***************************************************************************************************************

class CRefCount : boost::noncopyable
{
	friend void intrusive_ptr_add_ref(const CRefCount * ptr);
	friend void intrusive_ptr_release(const CRefCount * ptr);

public:
	explicit CRefCount() 
	: m_refs(0)
	{
	}

	virtual ~CRefCount()
	{
	}

private:

	size_t IncRef() const
	{
		return ++ m_refs;
	}

	size_t DecRef() const
	{
		return -- m_refs;
	}

	mutable size_t m_refs;
};

//***************************************************************************************************************

inline void intrusive_ptr_add_ref(const CRefCount * ptr)
{
	ptr->IncRef();
}

inline void intrusive_ptr_release(const CRefCount * ptr)
{
	if ( ptr->DecRef() == 0 ) {	delete ptr; }
}

//***************************************************************************************************************

#endif