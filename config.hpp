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
