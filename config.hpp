#ifndef INCLUDE_ROADAGAIN_CONFIG
#define INCLUDE_ROADAGAIN_CONFIG

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

    static const char* BLACK_STR;
    static const char* WHITE_STR;
    static const char* AUTOMATIC_STR;
    static const char* USE_COLOR_STR;
    static const char* TRUE_STR;
    static const char* FALSE_STR;

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
