#pragma once

#include <queue>

namespace model
{

class number_pool
{
    std::queue<unsigned> pool_;
    unsigned max_served_val_;

  public:

    number_pool();
    unsigned get();
    void reset();
    void put_back(unsigned val);
};

}