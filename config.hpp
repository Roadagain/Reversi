#ifndef INCLUDE_ROADAGAIN_CONFIG
#define INCLUDE_ROADAGAIN_CONFIG

#include <string>

#include "board.hpp"
#include "enemy.hpp"

namespace roadagain
{

class Config
{
public:
    static Config& instance();

    bool init(int argc, char** argv);

    void help();

    bool color() const;
    bool automatic() const;
    BoardState player() const;
    Level level() const;
    std::string log_file() const;

    static const std::string BLACK_STR;
    static const std::string WHITE_STR;
    static const std::string AUTOMATIC_STR;
    static const std::string COLOR_STR;
    static const std::string ALWAYS_STR;
    static const std::string AUTO_STR;
    static const std::string NEVER_STR;
    static const std::string LEVEL_STR;
    static const std::string EASY_STR;
    static const std::string HARD_STR;
    static const std::string LOG_STR;
    static const std::string HELP_STR;

private:
    Config();
    Config(const Config& config);
    Config& operator=(const Config& config);

    bool color_;
    bool automatic_;
    BoardState player_;
    Level level_;
    std::string log_file_;
};

}

#endif
