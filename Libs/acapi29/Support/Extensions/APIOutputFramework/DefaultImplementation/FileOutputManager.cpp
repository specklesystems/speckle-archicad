
#include "FileOutputManager.hpp"

GSAPI::FileOutputManager::~FileOutputManager (void)
{
	outFile.Flush ();
	outFile.Close ();
}
