#include <bfs.hpp>
#include <color.hpp>

bfs::bfs(const model::graph& graph, const model::vertex* start_point, event_sink<game_event_dispatcher>& game_event_sink)
  : graph_algorithm(graph),
    game_event_sink_(game_event_sink),
    adjlists_(graph_helpers::generate_adjacency_lists(graph_))
{
  bfs_queue_.push(start_point);
  visited_.insert(start_point);
  for (auto& edge : graph_.edges())
    edge.color = color::dark_grey;
  game_event_sink_.add_event(std::make_unique<e_set_label_rendering_mode>(false));
}

void bfs::step()
{
  //end algorithm when the queue is empty
  if (bfs_queue_.empty())
  {
    game_event_sink_.add_event(std::make_unique<e_set_label_rendering_mode>(true));
    game_event_sink_.add_event(std::make_unique<e_algo_finished>());
    return;
  }
  auto current = bfs_queue_.front();
  current->color = color::white;
  bfs_queue_.pop();
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Pushing unvisited neighbours of " + std::to_wstring(current->index)));
  auto& my_neighbours = adjlists_[current];
  for (const auto& pair : my_neighbours)
  {
    const auto& destination = pair.second;
    if (visited_.insert(destination).second)
    {
      bfs_queue_.push(destination);
      destination->color = color::green;
      pair.first->color = { 0.2f, 0.9f, 0.8f };
    }
  }
  if (!bfs_queue_.empty())
    bfs_queue_.front()->color = color::red;
}
