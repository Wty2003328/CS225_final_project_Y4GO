#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <fstream>
std::vector<std::vector<string>> readfile(const std::string & filename);
std::string TrimRight(const std::string & str);
std::string TrimLeft(const std::string & str);
void Trim(const std::string & str);
std::vector<std::vector<string>> temp;
struct airport {
    std::string name_;
    int latitude_;
    int longtitude_;
};
void devide(string line, vector<string> temp);
map<std::string, airport> airport;