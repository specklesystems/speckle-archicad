#if !defined GS_GS_ISEQUALORNULL_HPP
#define GS_GS_ISEQUALORNULL_HPP

namespace GS {


template <class Type1, class Type2>
inline bool IsEqualOrNull (const Type1* item1, const Type2* item2)
{
	return (item1 == nullptr && item2 == nullptr) || (item1 != nullptr && item2 != nullptr && *item1 == *item2);
}


} // namespace GS

#endif