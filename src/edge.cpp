#include <edge.hpp>
#include <algorithm>
#include <stdexcept>

namespace model
{

edge::edge(const vertex& from, const vertex& to, int weight, const std::string& label)
  : from(from),
    to(to),
    weight(weight),
    label(label),
    is_selected(false),
    color(0.2f, 0.2f, 0.2f)
{
}

}