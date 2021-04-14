#include <number_pool.hpp>

namespace model
{

number_pool::number_pool()
  : max_served_val_(0)
{
}

unsigned number_pool::get()
{
  if (pool_.empty())
    return max_served_val_++;
  auto val = pool_.front();
  pool_.pop();
  return val;
}

void number_pool::reset()
{
  max_served_val_ = 0;
  pool_ = std::queue<unsigned>();
}

void number_pool::put_back(unsigned val)
{
  pool_.push(val);
}

}