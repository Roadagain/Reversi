#include <ctime>

#include "board.hpp"
#include "random.hpp"

namespace roadagain
{

unsigned int random()
{
    static unsigned int MOD = Board::ROW * Board::COL;
    static unsigned int A = 18;
    static unsigned int B = 4;

    unsigned int x = std::time(NULL);
    for (int i = 0; i < 72; i++){
        x = (A * x + B) % MOD;
    }

    return (x);
}

}
