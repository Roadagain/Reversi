#ifndef INCLUDE_ROADAGAIN_CONFIG
#define INCLUDE_ROADAGAIN_CONFIG

namespace roadagain
{

class Config
{
public:
    static Config& instance();

private:
    Config();
    Config(const Config& config);
    Config& operator=(const Config& config);
    static Config instance_;

    bool use_color_;
    bool automatic_;
    BoardState player_;
};

}

#endif
