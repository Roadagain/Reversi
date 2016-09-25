#ifndef INCLUDE_ROADAGAIN_CONFIG
#define INCLUDE_ROADAGAIN_CONFIG

#include <string>

#include <argp.h>

#include "board.hpp"
#include "enemy.hpp"

namespace roadagain
{

class Config
{
public:
    static Config& instance();

    bool init(int argc, char** argv);

    bool color() const;
    bool automatic() const;
    Cell player() const;
    Level level() const;
    std::string log_file_name() const;

    static const std::string BLACK_STR;
    static const std::string WHITE_STR;
    static const std::string AUTOMATIC_STR;
    static const std::string AUTOMATIC_DESCRIPTION;
    static const char AUTOMATIC_CHAR;
    static const std::string COLOR_STR;
    static const std::string COLOR_DESCRIPTION;
    static const char COLOR_CHAR;
    static const std::string ALWAYS_STR;
    static const std::string AUTO_STR;
    static const std::string NEVER_STR;
    static const std::string LEVEL_STR;
    static const std::string LEVEL_DESCRIPTION;
    static const char LEVEL_CHAR;
    static const std::string EASY_STR;
    static const std::string MEDIUM_STR;
    static const std::string HARD_STR;
    static const std::string LOG_STR;
    static const std::string LOG_DESCRIPTION;
    static const char LOG_CHAR;
    static const std::string ARGS_DOC;

private:
    Config();
    Config(const Config& config);
    Config& operator=(const Config& config);

    bool color_;
    bool automatic_;
    Cell player_;
    Level level_;
    std::string log_file_name_;
};

struct arguments
{
    bool automatic;
    bool color;
    Level level;
    Cell player;
    std::string log_file_name;
};

error_t parse_opt(int key, char* arg, struct argp_state* state);

} // namespace roadagain

#endif
