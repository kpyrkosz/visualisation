#pragma once

#include <graph.hpp>

class application
{
  protected:

    model::graph& graph_;

  public:

    application(model::graph& graph)
      : graph_(graph) {}
    virtual ~application() = default;

    virtual void update(float elapsed_time) = 0;
    virtual void on_key(int key) = 0;
    virtual void on_left_click(float loc_x, float loc_y) = 0;
};
