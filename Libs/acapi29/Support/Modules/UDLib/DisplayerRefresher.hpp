#ifndef DISPLAYER_REFRESHER
#define DISPLAYER_REFRESHER

namespace UD {

template<typename TypedDisplayer>
class DisplayerRefresher
{
public:
	DisplayerRefresher () :
		displayer (nullptr)
	{
	}

	virtual ~DisplayerRefresher ()
	{
	}

	void AttachDisplayer (TypedDisplayer& newDisplayer)
	{
		if (DBVERIFY (displayer == nullptr)) {
			displayer = &newDisplayer;
		}
	}

	void Notify (const std::function<void (TypedDisplayer& displayerToUpdate)> updateDisplayer)
	{
		if (DBVERIFY (displayer != nullptr)) {
			updateDisplayer (*displayer);
		}
	}

private:
	TypedDisplayer* displayer;
};

}

#endif