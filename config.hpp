#ifndef INCLUDE_ROADAGAIN_CONFIG
#define INCLUDE_ROADAGAIN_CONFIG

namespace roadagain
{

class Config
{
public:
    static Config& instance() const;

private:
    Config();
    Config(const Config& config);
    Config& operator=(const Config& config);
    static Config instance;

    bool use_color;
    bool automatic;
    BoardState player;
};

}

#endif
