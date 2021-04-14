#include <vertex.hpp>

namespace model
{

vertex::vertex(unsigned index, const std::string& label, float x, float y)
  : index(index),
    label(label),
    is_selected(false),
    color(1.0f, 1.0f, 1.0f),
    loc(x, y)
{
}

bool vertex::operator==(const vertex& rhs) const
{
  return index == rhs.index;
}

}