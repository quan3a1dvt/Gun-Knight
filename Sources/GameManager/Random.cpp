#include "Random.h"

namespace random {

	int random(int min, int max) {
		
		return (rand() % (max - min + 1) + min);
	}
}