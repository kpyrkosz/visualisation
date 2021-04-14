#pragma once

#include <graph_algorithm.hpp>
#include <set>
#include <queue>
#include <game_event_dispatcher.hpp>
#include <graph_helpers.hpp>

class bfs
  : public graph_algorithm
{
    event_sink<game_event_dispatcher>& game_event_sink_;

    graph_helpers::adjacency_lists adjlists_;
    std::set<const model::vertex*> visited_;
    std::queue<const model::vertex*> bfs_queue_;

  public:

    bfs(const model::graph& graph, const model::vertex* start_point, event_sink<game_event_dispatcher>& game_event_sink);
    virtual void step() override;
};