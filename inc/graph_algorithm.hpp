#pragma once

#include <graph.hpp>

class graph_algorithm
{
  protected:

    const model::graph& graph_;

  public:

    graph_algorithm(const model::graph& graph);
    virtual ~graph_algorithm() = default;
    virtual void step() = 0;
};