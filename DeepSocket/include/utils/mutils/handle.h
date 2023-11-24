#ifndef MUTILS_HANDLE_H
#define MUTILS_HANDLE_H

namespace mutils
{

//this utility creates a copy of an object that its lifetime is managed externally.
//use only in language boundaries, and copied objects.
//in general, using pointer as handle is preferred.
//most useful when exporting a copy of a shared pointer.
template<typename T>
class Handle
{
public:
	Handle() = delete;
	Handle(const Handle& rhs) = delete;
	Handle& operator=(const Handle& rhs) = delete;
	Handle(T& _subject) :
		subject(_subject)
	{}

private:
	T subject;
};

}

#endif // !MUTILS_HANDLE_H
