#include <vector>
#include <fstream>

#include "board.hpp"
#include "config.hpp"
#include "log.hpp"

namespace roadagain
{

Log::Log(const Point& p, BoardState stone) : p(p), stone(stone)
{
}

void log_records(std::vector<Log>& logs, BoardState winner)
{
    Config& config = Config::instance();

    if (config.log_file_name().empty()){
        return;
    }

    int size = logs.size();
    std::ofstream log_file(config.log_file_name().c_str());
    for (int i = 0; i < size; i++){
        if (logs[i].stone == BLACK){
            log_file << 'B';
        }
        else {
            log_file << 'W';
        }
        log_file << ' ' << static_cast<char>('a' + logs[i].p.x);
        log_file << ' ' << logs[i].p.y;
        log_file << '\n';
    }
    if (winner == BLACK){
        log_file << "Winner is Black";
    }
    else if (winner == WHITE){
        log_file << "Winner is White";
    }
    else {
        log_file << "Draw";
    }
    log_file << '\n';

    log_file.close();
}

} // namespace roadagain
