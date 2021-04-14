#include <graph_helpers.hpp>

namespace graph_helpers
{

std::vector<const model::vertex*> get_selected_vertices(const model::graph& graph)
{
  std::vector<const model::vertex*> res;
  for (const auto& elem : graph.vertices())
    if (elem.is_selected)
      res.push_back(&elem);
  return res;
}

std::vector<const model::edge*> get_selected_edges(const model::graph& graph)
{
  std::vector<const model::edge*> res;
  for (const auto& elem : graph.edges())
    if (elem.is_selected)
      res.push_back(&elem);
  return res;
}

void unselect_all(const model::graph& graph)
{
  for (const auto& elem : graph.edges())
    elem.is_selected = false;
  for (const auto& elem : graph.vertices())
    elem.is_selected = false;
}

void recolor_all_edges(const model::graph& graph, const glm::vec3& color)
{
  for (const auto& elem : graph.edges())
    elem.color = color;
}

void recolor_all_vertices(const model::graph& graph, const glm::vec3& color)
{
  for (const auto& elem : graph.vertices())
    elem.color = color;
}

void select(const model::graph& graph, const camera& cam, float screen_x, float screen_y, float distance)
{
  const glm::vec2 point = cam.screen_to_world(screen_x, screen_y);
  for (const auto& vert : graph.vertices())
    if (glm::distance(vert.loc, point) < distance)
    {
      vert.is_selected = !vert.is_selected;
      return;
    }

  const model::edge* closest = nullptr;
  float max_distance = distance + 1.0f;

  for (const auto& edge : graph.edges())
  {
    const auto& line_begin = edge.from;
    const auto& line_end = edge.to;

    auto length = glm::length(line_end.loc - line_begin.loc);
    float dot = glm::dot(point - line_begin.loc, line_end.loc - line_begin.loc) / (length * length);
    if (dot < 0.0f || dot > 1.0f)
      continue;
    glm::vec2 projection = line_begin.loc + dot * (line_end.loc - line_begin.loc);
    auto distance = glm::length(projection - point);
    if (distance < max_distance)
    {
      max_distance = distance;
      closest = &edge;
    }
  }
  if (closest)
    closest->is_selected = !closest->is_selected;
}

adjacency_lists generate_adjacency_lists(const model::graph& graph)
{
  adjacency_lists result;
  for (const auto& edge : graph.edges())
  {
    result[&edge.from].push_front({ &edge, &edge.to });
    result[&edge.to].push_front({ &edge, &edge.from });
  }
  return result;
}

}