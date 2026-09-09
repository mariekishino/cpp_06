#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <cstddef>

struct Data
{
    std::string name;
    std::size_t age;
    Data*       next;
};

#endif