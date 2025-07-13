#include <random>

#include "key.h"

std::string makeKey()
{
    /* we make a random number generator (RNG):
    1) I create a "random device" obj that will (when it's called) return a value based on machine internals.

    2) I create a "random number engine" obj (in this case, it's a "Mersenne Twister") seeded with a value obtained by calling my random device obj.

    3) I create a uniform distribution obj, which uses my random number engine to return a randomly chosen value in a provided range.
    */

    std::random_device rd; // random device obj 
    std::mt19937 gen(rd()); // random number engine object

    std::uniform_int_distribution<> dist(1, 10); // uniform distribution obj

    // I use my RNG to generate and assign a random value to be the length of my key:
    int length = dist(gen);

    std::string key = fillString(length, gen);

    return key;
}

std::string fillString(int length, std::mt19937& gen)
{
    std::string key;

    std::uniform_int_distribution<> dist(0, 255);

    for (int i = 0; i <= length; i++)
    {
        key += static_cast<char>(dist(gen));
    }

    return key;
}