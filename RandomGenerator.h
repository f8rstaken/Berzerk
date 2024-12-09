#pragma once

#include <random>
#include <chrono>

class RandomGenerator {

public:
    static int getRandomInt(int min, int max) {
        static std::default_random_engine rng(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }

};
