#include <vector>
#include <fstream>

#include "board.hpp"
#include "config.hpp"
#include "log.hpp"

namespace roadagain
{

Log::Log(int y, int x, BoardState stone) : y(y), x(x), stone(stone)
{
}

void log_records(std::vector<Log> logs, BoardState winner)
{
    int size = logs.size();
    std::ofstream log_file(Config::instance().log_file().c_str());
    for (int i = 0; i < size; i++){
        if (logs[i].stone == BLACK){
            log_file << 'B';
        }
        else {
            log_file << 'W';
        }
        log_file << ' ' << ('a' + logs[i].x);
        log_file << ' ' << logs[i].y;
        log_file << '\n';
    }
    if (winner == BLACK){
        log_file << "Winner is Blackn";
    }
    else if (winner == WHITE){
        log_file << "Winner is Whiten";
    }
    else {
        log_file << "Drawn";
    }
    log_file << '\n';

    log_file.close();
}

}
