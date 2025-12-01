#ifndef GEOM_PPE_INDEXTYPE_HPP
#define GEOM_PPE_INDEXTYPE_HPP
#pragma once

template <int IndexTypeID>
class IndexType
{
public:
	IndexType<IndexTypeID> () : value (static_cast<size_t> (-1)) {}
	explicit IndexType<IndexTypeID> (size_t initVal) : value (initVal) {}
	IndexType<IndexTypeID>& operator = (const size_t rhs) = delete; //no assign like this!

	bool IsValid () const { return value != static_cast<size_t> (-1); }

	IndexType<IndexTypeID>& operator ++ ()
	{
		++value;
		return *this;
	}

	IndexType<IndexTypeID> operator ++ (int)
	{
		return IndexType<IndexTypeID> (value++);
	}

	bool operator < (const size_t rhs) const { return value < rhs; }

	bool operator < (const IndexType<IndexTypeID>& rhs) const { return value < rhs.value; }
	bool operator <= (const IndexType<IndexTypeID>& rhs) const { return value <= rhs.value; }
	bool operator == (const IndexType<IndexTypeID>& rhs) const { return value == rhs.value; }
	bool operator >= (const IndexType<IndexTypeID>& rhs) const { return value >= rhs.value; }
	bool operator > (const IndexType<IndexTypeID>& rhs) const { return value > rhs.value; }

	size_t Get () const { return value; }

	static int GetIndexTypeID () { return IndexTypeID; }

private:
	size_t value;
};

#endif
