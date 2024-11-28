#ifndef	GS_COMMONUI_DIALOGSTATEBASE_HPP
#define	GS_COMMONUI_DIALOGSTATEBASE_HPP

#include "UDDefinitions.hpp"

#include "UniString.hpp"

namespace UD {

class UD_DLL_EXPORT DialogStateBase {
public:

	class UD_DLL_EXPORT StorageAccessor 
	{
	public:
		StorageAccessor ();
		virtual ~StorageAccessor ();

		template <typename T>
		GS::ErrCode LoadFromEntry (const GS::UniString& keyName, T* data)
		{
			if constexpr (std::disjunction_v<std::is_void<T>,
											 std::is_same<std::remove_cv_t<T>, wchar_t>,
											 std::is_same<std::remove_cv_t<T>, char>,
											 std::is_same<std::remove_cv_t<T>, unsigned char>,
											 std::is_same<std::remove_cv_t<T>, std::byte>>)
			{
				static_assert (GS::AlwaysFalse<T>, "Missing buffer size argument");
			} else {
				static_assert (std::is_trivially_copyable_v<T>);
				return LoadFromEntry (keyName, (void*)data, static_cast<ULong> (sizeof (T)));
			}
		}

		virtual void		StoreToEntry (const GS::UniString& keyName, const void* data, ULong size) = 0;
		virtual GS::ErrCode	LoadFromEntry (const GS::UniString& keyName, void* data, ULong size) = 0;
		virtual ULong		GetEntrySize (const GS::UniString& keyName) = 0;
	};

private:
	StorageAccessor*	mStorageAccessor;

public:
	DialogStateBase (StorageAccessor* accessor = nullptr);
	virtual	~DialogStateBase ();

	GS::ErrCode					Load (const GS::UniString& keyName);
	GS::ErrCode					Store (const GS::UniString& keyName) const;

	virtual void				Reset () = 0;

protected:
	virtual GS::ErrCode			Read (GS::IChannel& channel) = 0;
	virtual GS::ErrCode			Write (GS::OChannel& channel) const = 0;
};

} // namespace UD


#endif