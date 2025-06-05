#include "lzw.h"
#include <iostream>

std::vector<int> encoding(std::string s1)
{
    std::cout << "Encoding..." << std::endl;
    if (s1.empty())
    {
        std::cout << "Nothing to encode" << std::endl;
        return {};
    }
    std::unordered_map<std::string, int> dict;
    for (int i = 0; i < 256; ++i) {dict[std::string(1, static_cast<char>(i))] = i;}
    std::string current;
    std::vector<int> res;
    int code = 256;
    for (auto& ch : s1)
    {
        if (code > 4095) {break;}
        std::string next = current + ch;
        if (dict.find(next) != dict.end()) {current = next;}
        else
        {
            res.push_back(dict[current]);
            dict[next] = code++;
            current = std::string(1, ch);
        }
    }
    if (!current.empty()) {res.push_back(dict[current]);}
    return res;
}
void decoding(std::vector<int> op)
{
    std::cout << "Decoding..." << std::endl;
    if (op.empty())
    {
        std::cout << "Nothing to decode" << std::endl;
        return;
    }
    std::unordered_map<int, std::string> dict;
    for (int i = 0; i < 256; ++i) {dict[i] = std::string(1, static_cast<char>(i));}
    int code = 256;
    std::string prev, current;
    for (auto& c : op)
    {   
        if (code > 4095) {break;}
        if (dict.find(c) != dict.end()) {current = dict[c];}
        else {current = prev + prev[0];}
        std::cout << current;
        if (!prev.empty()) {dict[code++] = prev + current[0];}
        prev = current;
    }
}
