#include "Utility/UniqueID.h"
#include <utility>

unsigned int UniqueID::mLastID = 0;

UniqueID::UniqueID()
{
	mID = mLastID++;

}

// Caller must be sure that id is unique - the class does not track this
UniqueID::UniqueID(unsigned int id)
{
	mID = id;
	if (id >= mLastID)
	{
		mLastID = id + 1;
	}
}


UniqueID::~UniqueID()
{
}