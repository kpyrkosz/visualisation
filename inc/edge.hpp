#pragma once

#include <vertex.hpp>

namespace model
{

struct edge
{
  const vertex& from;
  const vertex& to;
  mutable int weight;
  mutable std::string label;
  mutable bool is_selected;
  mutable glm::vec3 color;

  edge(const vertex& from, const vertex& to, int weight = 0, const std::string& label = "");

  struct less
  {
    bool operator()(const edge& a, const edge& b) const
    {
      if (a.from.index < b.from.index)
        return true;
      if (a.from.index == b.from.index)
        return a.to.index < b.to.index;
      return false;
    }
  };

  struct by_decreasing_weight
  {
    bool operator()(const edge& a, const edge& b) const
    {
      return a.weight > b.weight;
    }

    bool operator()(const edge* a, const edge* b) const
    {
      return a->weight > b->weight;
    }
  };

};

}