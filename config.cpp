#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "board.hpp"
#include "config.hpp"

namespace roadagain
{

Config::Config() : color_(true), automatic_(false), player_(BLACK), level_(EASY)
{
}

Config& Config::instance()
{
    static Config instance_;
    return (instance_);
}

bool Config::init(int argc, char** argv)
{
    argp_option options[] = {
        { AUTOMATIC_STR.c_str(), AUTOMATIC_STR[0], nullptr, 0, AUTOMATIC_DESCRIPTION.c_str() },
        { COLOR_STR.c_str(), COLOR_STR[0], "WHEN", 0, COLOR_DESCRIPTION.c_str() },
        { LEVEL_STR.c_str(), LEVEL_STR[0], "LEVEL", 0, LEVEL_DESCRIPTION.c_str() },
        { LOG_STR.c_str(), LOG_STR[0], "FILE", 0, LOG_DESCRIPTION.c_str() },
        { nullptr }
    };
    argp args = { options, parse_opt, ARGS_DOC.c_str(), nullptr };
    arguments a = { false, false, EASY, BLACK, "" };
    argp_parse(&args, argc, argv, 0, nullptr, &a);

    return (true);
}

bool Config::color() const
{
    return (color_);
}

bool Config::automatic() const
{
    return (automatic_);
}

BoardState Config::player() const
{
    if (automatic_){
        return (EMPTY);
    }
    else {
        return (player_);
    }
}

Level Config::level() const
{
    return (level_);
}

std::string Config::log_file_name() const
{
    return (log_file_name_);
}

const std::string Config::BLACK_STR("black");
const std::string Config::WHITE_STR("white");
const std::string Config::AUTOMATIC_STR("automatic");
const std::string Config::AUTOMATIC_DESCRIPTION("Play automatically.");
const char Config::AUTOMATIC_CHAR = 'a';
const std::string Config::COLOR_STR("color");
const std::string Config::COLOR_DESCRIPTION("Colorize the output.");
const char Config::COLOR_CHAR = 'c';
const std::string Config::ALWAYS_STR("always");
const std::string Config::AUTO_STR("auto");
const std::string Config::NEVER_STR("never");
const std::string Config::LEVEL_STR("level");
const std::string Config::LEVEL_DESCRIPTION("Choose enemy's level.");
const char Config::LEVEL_CHAR = 'l';
const std::string Config::EASY_STR("easy");
const std::string Config::MEDIUM_STR("medium");
const std::string Config::HARD_STR("hard");
const std::string Config::LOG_STR("Log");
const std::string Config::LOG_DESCRIPTION("Log the game records to FILENAME.");
const char Config::LOG_CHAR = 'L';
const std::string Config::ARGS_DOC("[ARG1]");

error_t parse_opt(int key, char* arg, struct argp_state* state)
{
    arguments* a = static_cast<arguments*>(state->input);
    switch (key){
        case Config::AUTOMATIC_CHAR:
            a->automatic = true;
            break;
        case Config::COLOR_CHAR:
            if (arg == Config::NEVER_STR){
                a->color = false;
            }
            else {
                a->color = true;
            }
            break;
        case Config::LEVEL_CHAR:
            if (arg == Config::EASY_STR){
                a->level = EASY;
            }
            else if (arg == Config::MEDIUM_STR){
                a->level = MEDIUM;
            }
            else {
                a->level = HARD;
            }
            break;
        case Config::LOG_CHAR:
            a->log_file_name = arg;
            break;
        case ARGP_KEY_ARG:
            if (arg == Config::WHITE_STR){
                a->player = WHITE;
            }
            else {
                a->player = BLACK;
            }
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

}
