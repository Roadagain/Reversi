#include "board.hpp"
#include "config.hpp"

namespace roadagain
{

Config::Config() : use_color_(true), automatic_(false), player_(BLACK)
{
}

Config::Config(const Config& config)
{
}

Config& Config::instance()
{
    return (Config::instance_);
}

Config::Config& operator=(const Config& config)
{
}

}

#endif
