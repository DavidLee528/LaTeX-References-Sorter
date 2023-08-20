#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>

std::string read_file(const std::string &path)
{
    std::ifstream tex_file{};
    tex_file.open(path);

    if (!tex_file.is_open())
    {
        throw std::runtime_error("cannot open file {}");
    }

    std::string tex_str{};
    std::string line_str{};

    while (tex_file)
    {
        tex_file >> line_str;
        tex_str += line_str;
    }

    tex_file.close();
    return tex_str;
}

std::vector<std::string> read_items(const std::string &tex_str, const std::string &match)
{
    std::vector<std::string> ret{};

    for (size_t i = 0; i < tex_str.length() - match.length(); ++i)
    {
        if (tex_str.substr(i, match.length()) != match)
            continue;
        size_t j{i + match.length()};
        for (/* */; tex_str[j] != '}'; ++j)
            ;
        std::string item = tex_str.substr(i + match.length(), j - i - match.length());
        if (std::find(ret.begin(), ret.end(), item) != ret.end())
            continue;
        ret.push_back(item);
    }

    return ret;
}

void update_tex_file(const std::string &path, const std::vector<std::string> &sorted_bibitems)
{
    std::ifstream tex_file{};
    tex_file.open(path);

    if (!tex_file.is_open())
    {
        throw std::runtime_error("cannot open file");
    }

    std::string line_str{};
    std::vector<std::string> lines{};
    std::vector<std::string> new_lines{};
    std::vector<std::string> bibitems{};

    while (tex_file)
    {
        tex_file >> line_str;
        if (line_str.substr(0, 9) != "\\bibitem{")
            new_lines.push_back(line_str);
            
    }

    tex_file.close();
}

int main(int argc, const char **argv)
{

    if (argc < 2 || argc > 2)
    {
        throw std::runtime_error("./sort article.tex");
    }

    std::string tex_str = read_file(argv[1]);
    std::vector<std::string> cites = read_items(tex_str, "\\cite{");
    std::vector<std::string> bibitems = read_items(tex_str, "\\bibitem{");

    std::vector<std::string> sorted_bibitems{};
    for (const auto &item : cites)
    {
        auto match_iter = std::find(bibitems.begin(), bibitems.end(), item);
        sorted_bibitems.push_back(*match_iter);
    }

    for (const auto &elem : sorted_bibitems)
        std::cout << elem << '\n';
    std::cout << std::endl;
    
    return 0;
}