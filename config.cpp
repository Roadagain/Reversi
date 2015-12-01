#include <cstdio>
#include <string>

#include "board.hpp"
#include "config.hpp"

namespace roadagain
{

Config::Config() : use_color_(true), automatic_(false), player_(BLACK)
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
        else if (argument.find(AUTOMATIC_STR) == 0){
            if (argument == AUTOMATIC_STR || argument.substr(11) == TRUE_STR){
                automatic_ = true;
            }
            else if (argument.substr(11) == FALSE_STR){
                automatic_ = false;
            }
            else {
                std::printf("invalid argument: %s\n", argv[i]);
                std::printf("automatic option must be 'true' or 'false'");
                return (false);
            }
        }
        else if (argument.find(USE_COLOR_STR) == 0){
            if (argument == USE_COLOR_STR || argument.substr(11) == TRUE_STR){
                use_color_ = true;
            }
            else if (argument.substr(11) == FALSE_STR){
                use_color_ = false;
            }
            else {
                std::printf("invalid argument: %s\n", argv[i]);
                std::printf("using color option must be 'true' or 'false'");
                return (false);
            }
        }
        else {
            std::printf("invalid argument: %s\n", argv[i]);
            return (false);
        }
    }

    return (true);
}

bool Config::use_color() const
{
    return (use_color_);
}

bool Config::automatic() const
{
    return (automatic_);
}

BoardState Config::player() const
{
    return (player_);
}

const std::string Config::BLACK_STR("black");
const std::string Config::WHITE_STR("white");
const std::string Config::AUTOMATIC_STR("--automatic");
const std::string Config::USE_COLOR_STR("--use-color");
const std::string Config::TRUE_STR("=true");
const std::string Config::FALSE_STR("=false");

}
