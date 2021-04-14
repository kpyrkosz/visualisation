#include <dijkstra.hpp>
#include <algorithm>
#include <color.hpp>

dijkstra::dijkstra(const model::graph& graph, const model::vertex* start_point, event_sink<game_event_dispatcher>& game_event_sink)
  : graph_algorithm(graph),
    game_event_sink_(game_event_sink),
    adjlists_(graph_helpers::generate_adjacency_lists(graph_)),
    current_vertex_(start_point)
{
  //init every vertex as nonvisited with "high enough" distance
  for (const auto& v : graph_.vertices())
    algo_data_[&v] = internal_data{ 999999, unreachable };
  //mark starting vertex as visited with distance 0
  algo_data_[current_vertex_] = internal_data{ 0, visited };
  for (auto& edge : graph_.edges())
    edge.color = color::dark_grey;
}

void dijkstra::step()
{
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Shortest path to " + std::to_wstring(current_vertex_->index)
                             + L" is " + std::to_wstring(algo_data_[current_vertex_].path_size)));
  algo_data_[current_vertex_].state = visited;
  current_vertex_->color = {0.8f, 0.2f, 0.4f};
  //get adjacent vertices of current vertex
  auto& my_neighbours = adjlists_[current_vertex_];
  //filter out ones the algorithm already found shortest path to
  auto to_remove = std::remove_if(my_neighbours.begin(), my_neighbours.end(), [this](const std::pair<const model::edge*, const model::vertex*>& elem)
  {
    return algo_data_.at(elem.second).state == visited;
  });
  if (to_remove != my_neighbours.end())
    my_neighbours.erase(to_remove, my_neighbours.end());
  auto my_distance = algo_data_[current_vertex_].path_size;
  //relax path lengths of reachable adjacent vertices
  for (auto& pair : my_neighbours)
  {
    algo_data_[pair.second].state = reachable;
    if (algo_data_[pair.second].path_size > my_distance + pair.first->weight)
    {
      /*game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Found shorter path from " + std::to_wstring(current_vertex_->index)
                                 + L" to " + std::to_wstring(pair.second->index)));*/
      algo_data_[pair.second].path_size = my_distance + pair.first->weight;
      algo_data_[pair.second].reachable_through = pair.first;
    }
  }
  //find next adjacent vertex with shortest current path
  current_vertex_ = nullptr;
  for (const auto& pair : algo_data_)
  {
    if (pair.second.state != reachable)
      continue;
    if (current_vertex_ == nullptr || pair.second.path_size < algo_data_[current_vertex_].path_size)
      current_vertex_ = pair.first;
  }
  //end algorithm when all vertices have been visited or some are not connected
  if (!current_vertex_)
  {
    game_event_sink_.add_event(std::make_unique<e_algo_finished>());
    return;
  }
  algo_data_[current_vertex_].reachable_through->color = { 0.2f, 0.9f, 0.8f };
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Next vertex is " + std::to_wstring(current_vertex_->index)));
  current_vertex_->color = { 0.1f, 0.9f, 0.4f };
}
