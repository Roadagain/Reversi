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
    scorpio::OptionParser parser(argc, argv);

    parser.add_option(AUTOMATIC_STR);
    parser.add_option(COLOR_STR, true);
    parser.add_option(LEVEL_STR, true);
    parser.add_option(LOG_STR, true);
    parser.add_option(HELP_STR);
    parser.add_option(BLACK_STR);
    parser.add_option(WHITE_STR);

    std::vector<scorpio::Option> options = parser.parse();
    int size = options.size();
    for (int i = 0; i < size; i++){
        if (!options[i].available){
            continue;
        }
        if (options[i].name == HELP_STR){
            help();
        }
        else if (options[i].name == AUTOMATIC_STR){
            automatic_ = true;
        }
        else if (options[i].name == COLOR_STR){
            if (options[i].value == ALWAYS_STR || options[i].value == AUTO_STR){
                color_ = true;
            }
            else if (options[i].value == NEVER_STR){
                color_ = false;
            }
            else {
                std::puts("color option can be only 1 of 3 values: always, auto, never");
                return (false);
            }
        }
        else if (options[i].name == LEVEL_STR){
            if (options[i].value == EASY_STR){
                level_ = EASY;
            }
            else if (options[i].value == MEDIUM_STR){
                level_ = MEDIUM;
            }
            else if (options[i].value == HARD_STR){
                level_ = HARD;
            }
            else {
                std::puts("level option cna be only 1 of 2 values: easy, hard");
                return (false);
            }
        }
        else if (options[i].name == LOG_STR){
            if (options[i].value.empty()){
                std::puts("log option needs filename");
                return (false);
            }
            else {
                log_file_name_ = options[i].value;
            }
        }
        else if (options[i].name == BLACK_STR){
            player_ = BLACK;
        }
        else if (options[i].name == WHITE_STR){
            player_ = WHITE;
        }
        else {
            std::printf("Unknown option: %s\n", options[i].name.c_str());
            return (false);
        }
    }

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
const std::string Config::AUTOMATIC_STR("--automatic");
const std::string Config::AUTOMATIC_DESCRIPTION("Play automatically.");
const std::string Config::COLOR_STR("--color");
const std::string Config::COLOR_DESCRIPTION("Colorize the output.");
const std::string Config::ALWAYS_STR("always");
const std::string Config::AUTO_STR("auto");
const std::string Config::NEVER_STR("never");
const std::string Config::LEVEL_STR("--level");
const std::string Config::LEVEL_DESCRIPTION("Choose enemy's level.");
const std::string Config::EASY_STR("easy");
const std::string Config::MEDIUM_STR("medium");
const std::string Config::HARD_STR("hard");
const std::string Config::LOG_STR("--log");
const std::string Config::LOG_DESCRIPTION("Log the game records to FILENAME.");

}
