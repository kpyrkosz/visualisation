#pragma once

#include <graph_algorithm.hpp>
#include <map>
#include <queue>
#include <game_event_dispatcher.hpp>

class kruskal
  : public graph_algorithm
{
    event_sink<game_event_dispatcher>& game_event_sink_;

    std::map<const model::vertex*, const model::vertex*> subset_representants_;
    std::priority_queue<const model::edge*, std::vector<const model::edge*>, model::edge::by_decreasing_weight> edges_in_order_;

  public:

    kruskal(const model::graph& graph, event_sink<game_event_dispatcher>& game_event_sink);
    virtual void step() override;
};