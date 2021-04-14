#include <biparite.hpp>
#include <color.hpp>

biparite::biparite(const model::graph& graph, event_sink<game_event_dispatcher>& game_event_sink)
  : graph_algorithm(graph),
    game_event_sink_(game_event_sink),
    adjlists_(graph_helpers::generate_adjacency_lists(graph))
{
}

void biparite::step()
{
  //all vertices have been colored succesfully, end algorithm
  if (adjlists_.empty())
  {
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Graph is biparite!"));
    game_event_sink_.add_event(std::make_unique<e_algo_finished>());
    return;
  }
  //if neighbours_to_check_ is empty it means we either just started the algorithm
  //or we succesfully checked part of the graph not connected to some vertices
  //in this case, just take any next vertex and color it red
  if (neighbours_to_check_.empty())
  {
    const model::vertex* new_vert = adjlists_.begin()->first;
    new_vert->color = color::red;
    neighbours_to_check_.insert(new_vert);
  }
  //if any adjacent vertex is the same color as we, graph is not biparite
  //if it is not colored, color it with color different than self
  const model::vertex* current_vertex = *neighbours_to_check_.begin();
  const glm::vec3 my_color = current_vertex->color;
  const glm::vec3 other_color = (my_color == color::red ? color::blue : color::red);

  for (const auto& pair : adjlists_.at(current_vertex))
  {
    const model::vertex* destination_vertex = pair.second;
    if(destination_vertex->color == my_color)
    {
      game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Graph is not biparite!"));
      game_event_sink_.add_event(std::make_unique<e_algo_finished>());
      return;
    }
    if (destination_vertex->color == color::white)
    {
      destination_vertex->color = other_color;
      neighbours_to_check_.insert(destination_vertex);
      continue;
    }
  }
  //remove this vertex from collections as it has been succesfully handled
  adjlists_.erase(current_vertex);
  neighbours_to_check_.erase(current_vertex);
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Succesfully recolored neighbours of " + std::to_wstring(current_vertex->index)));
}
