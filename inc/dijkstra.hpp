#pragma once

#include <graph_algorithm.hpp>
#include <map>
#include <queue>
#include <game_event_dispatcher.hpp>
#include <graph_helpers.hpp>

class dijkstra
  : public graph_algorithm
{
    event_sink<game_event_dispatcher>& game_event_sink_;

    enum vertex_reachability
    {
      visited,
      reachable,
      unreachable
    };

    struct internal_data
    {
      int path_size;
      vertex_reachability state;
      const model::edge* reachable_through;
    };

    graph_helpers::adjacency_lists adjlists_;
    std::map<const model::vertex*, internal_data> algo_data_;
    const model::vertex* current_vertex_;

  public:

    dijkstra(const model::graph& graph, const model::vertex* start_point, event_sink<game_event_dispatcher>& game_event_sink);
    virtual void step() override;
};