#pragma once

#include <graph_algorithm.hpp>
#include <game_event_dispatcher.hpp>
#include <graph_helpers.hpp>

class biparite
  : public graph_algorithm
{
    event_sink<game_event_dispatcher>& game_event_sink_;

    graph_helpers::adjacency_lists adjlists_;
    std::set<const model::vertex*> neighbours_to_check_;

  public:

    biparite(const model::graph& graph, event_sink<game_event_dispatcher>& game_event_sink);
    virtual void step() override;
};