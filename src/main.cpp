#include <framework.hpp>
#include <iostream>

int main(int argc, char** argv)
{
  try
  {
    return framework(argc, argv).run();
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what();
  }
}