#include "board.hpp"
#include "config.hpp"

namespace roadagain
{

Config::Config(bool use_color, bool automatic, BoardState player)
    : use_color_(use_color), automatic_(automatic), player_(player)
{
}

Config::Config(const Config& config)
{
}

Config& Config::instance() const
{
    return (Config.instance);
}

Config::Config& operator=(const Config& config)
{
}

}

#endif
