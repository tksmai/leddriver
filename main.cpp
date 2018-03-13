#include <iostream>
#include <string> // for function std::getline()
#include <vector>
#include "number.cpp"
#include "strprocess.cpp"

int main(int argc, char *argv[])
{
    number n(5, 6, 7);
    // n.loop_show();
    std::string input_str;
    std::cout << "Please input float:" << std::endl;
    std::getline(std::cin, input_str);
    ::strprocess strproc(&input_str);
    std::vector<std::string> vstr = strproc.to_vector();
    std::cout << vstr[0] << std::endl;
    return 0;
}