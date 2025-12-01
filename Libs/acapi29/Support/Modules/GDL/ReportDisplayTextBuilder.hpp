#ifndef	GDL_REPORTDISPLAYTEXTBUILDER_HPP
#define GDL_REPORTDISPLAYTEXTBUILDER_HPP

#include "GDLExport.h"
#include "UniString.hpp"

namespace GDL
{

class GDL_DLL_EXPORT ReportDisplayTextBuilder
{
public:
	ReportDisplayTextBuilder ();
	virtual ~ReportDisplayTextBuilder ();


	void AddTitle (const GS::UniString& title);
	void AddLine (const GS::UniString& str);
	void AddPrefixForNextLine (const GS::UniString& str);
	void AddEmptyLine ();

	void AddIndent ();
	void RemoveIndent ();

protected:
	virtual void DisplayRow (const GS::UniString& rowStr) = 0;

private:
	Int32			indentation = 0;
	GS::UniString	linePrefix;
};

}

#endif