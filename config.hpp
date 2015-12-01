#ifndef INCLUDE_ROADAGAIN_CONFIG
#define INCLUDE_ROADAGAIN_CONFIG

#include <string>

namespace roadagain
{

class Config
{
public:
    static Config& instance();

    bool init(int argc, char** argv);

    bool use_color() const;
    bool automatic() const;
    BoardState player() const;

    static const std::string BLACK_STR;
    static const std::string WHITE_STR;
    static const std::string AUTOMATIC_STR;
    static const std::string USE_COLOR_STR;
    static const std::string TRUE_STR;
    static const std::string FALSE_STR;

private:
    Config();
    Config(const Config& config);
    Config& operator=(const Config& config);

    bool use_color_;
    bool automatic_;
    BoardState player_;
};

}

#endif
