#pragma once

#include <string>
#include <glm/glm.hpp>

namespace model
{

struct vertex
{
  const unsigned index;
  mutable std::string label;
  mutable bool is_selected;
  mutable glm::vec3 color;
  mutable glm::vec2 loc;

  vertex(unsigned index, const std::string& label, float x, float y);
  bool operator==(const vertex& rhs) const;

  struct less
  {
    bool operator()(const vertex& a, const vertex& b) const
    {
      return a.index < b.index;
    }

    bool operator()(const vertex* a, const vertex* b) const
    {
      return a->index < b->index;
    }
  };
};

}