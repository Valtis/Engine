#include <random>
class Random
{
public:
	
	template <typename T>
	static T GetRandom(T upperLimit, T lowerLimit = 0)
	{
		if (!mIsInitialized)
		{
			InitializeRandomGenerator();
		}

		if (lowerLimit == upperLimit)
		{
			return lowerLimit;
		}
		else if (lowerLimit > upperLimit)
		{
			return 0;
		}

		std::uniform_real_distribution<double> distribution(lowerLimit, upperLimit);
		return distribution(mEngine);
	}

private:
	Random() { }
	~Random() { }

	static void InitializeRandomGenerator();


	static std::mt19937 mEngine;
	static bool mIsInitialized;
};
