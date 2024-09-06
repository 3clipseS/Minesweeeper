#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
	static std::mt19937 random;

public:
	static int getRandomInt(int min, int max);
	static float getRandomFloat(float min, float max);

};


#endif

