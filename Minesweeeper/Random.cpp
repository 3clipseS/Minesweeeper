#include "Random.h"

using namespace std;


std::mt19937 Random::random(time(0));

int Random::getRandomInt(int min, int max) {

	uniform_int_distribution<int> dist(min, max);

	return dist(random);
}

float Random::getRandomFloat(float min, float max) {

	uniform_real_distribution<float> dist(min, max);

	return dist(random);
}