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
    return (Config::instance_);
}

bool Config::init(int argc, char** argv)
{
    for (int i = 1; i < argc; i++){
        std::string argument(argv[i]);

        if (argument == "black"){
            player_ = BLACK;
        }
        else if (argument == "white"){
            player_ = WHITE;
        }
        else if (argument.substr(0, 11) == "--automatic"){
            if (argument == "--automatic" || argument.substr(11) == "=true"){
                automatic_ = true;
            }
            else if (argument.substr(11) == "=false"){
                automatic_ = false;
            }
            else {
                std::printf("invalid argument: %s\n", argv[i]);
                std::printf("automatic option must be 'true' or 'false'");
                return (false);
            }
        }
        else if (argument.substr(0, 11) == "--use-color"){
            if (argument == "--use-color" || argument.substr(11) == "=true"){
                use_color_ = true;
            }
            else if (argument.substr(11) == "=false"){
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

}
