#include <cstdio>
#include <string>

#include "board.hpp"
#include "config.hpp"

namespace roadagain
{

Config::Config() : color_(true), automatic_(false), player_(BLACK)
{
}

Config& Config::instance()
{
    static Config instance_;
    return (instance_);
}

bool Config::init(int argc, char** argv)
{
    for (int i = 1; i < argc; i++){
        std::string argument(argv[i]);

        if (argument == BLACK_STR){
            player_ = BLACK;
        }
        else if (argument == WHITE_STR){
            player_ = WHITE;
        }
        else if (argument == AUTOMATIC_STR){
            automatic_ = true;
        }
        else if (argument == COLOR_STR){
            color_ = true;
        }
        else if (argument == NO_COLOR_STR){
            color_ = false;
        }
        else if (argument == HELP_STR){
            help();
            return (false);
        }
        else {
            std::printf("invalid argument: %s\n", argv[i]);
            return (false);
        }
    }

    return (true);
}

void Config::help()
{
    std::puts("Usage: reversi [options] [color]");
    std::puts("Reversi game for one person's play.");
    std::puts("Options:");
    std::puts("  --automatic Play automatically.");
    std::puts("  --color     Use colors when printing something.");
    std::puts("  --help      Print this help and exit successfully.");
    std::puts("  --nocolor   Don't use colors when printing something.");
    std::puts("");
    std::puts("Color must be 'black' or 'white'.");
    std::puts("Default color is black.");
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

const std::string Config::BLACK_STR("black");
const std::string Config::WHITE_STR("white");
const std::string Config::AUTOMATIC_STR("--automatic");
const std::string Config::COLOR_STR("--color");
const std::string Config::NO_COLOR_STR("--nocolor");
const std::string Config::HELP_STR("--help");

}
