#include "IDXFTestObject.hpp"


OD::IDXFTestObject::IDXFTestObject ()
{
}


OD::IDXFTestObject::~IDXFTestObject ()
{
}


void OD::IDXFTestObject::SetOdDbDatabase (const OdDbDatabasePtr db)
{
	this->db = db;
}


void OD::IDXFTestObject::CheckOdDbDatabase ()
{
}