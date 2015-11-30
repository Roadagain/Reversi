#include <ctime>

#include "board.hpp"
#include "random.hpp"

namespace roadagain
{

unsigned int random()
{
    static unsigned long long x = 123456789ULL;
    static unsigned long long y = 362436069ULL;
    static unsigned long long z = time(NULL) % 521288629ULL;
    static unsigned long long w = 88675123ULL;

    unsigned long long t = (x ^ (x << 11));
    x = y;
    y = z;
    z = w;
    w = w ^ (w >> 19) ^ (t ^ (t >> 8));

    return (w % 64);
}

}
