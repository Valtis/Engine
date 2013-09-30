#include "Utility/Random.h"
#include <ctime>
std::mt19937 Random::mEngine;
bool Random::mIsInitialized = false;

void Random::InitializeRandomGenerator()
{
	mEngine.seed(time(nullptr));
}