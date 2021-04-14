#include <dfs.hpp>
#include <color.hpp>

dfs::dfs(const model::graph& graph, const model::vertex* start_point, event_sink<game_event_dispatcher>& game_event_sink)
  : graph_algorithm(graph),
    game_event_sink_(game_event_sink),
    adjlists_(graph_helpers::generate_adjacency_lists(graph_))
{
  dfs_stack_.push(start_point);
  visited_.insert(start_point);
}

void dfs::step()
{
  //end algorithm when the stack is empty
  if (dfs_stack_.empty())
  {
    game_event_sink_.add_event(std::make_unique<e_algo_finished>());
    return;
  }
  auto current = dfs_stack_.top();
  current->color = color::red;
  dfs_stack_.pop();
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Pushing unvisited neighbours of " + std::to_wstring(current->index)));
  auto& my_neighbours = adjlists_[current];
  for (const auto& pair : my_neighbours)
  {
    const auto& destination = pair.second;
    if (visited_.insert(destination).second)
    {
      dfs_stack_.push(destination);
      destination->color = color::green;
    }
  }
}

