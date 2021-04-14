#pragma once

#include <graph.hpp>
#include <camera.hpp>
#include <vector>
#include <map>
#include <list>

namespace graph_helpers
{

using adjacency_lists = std::map<const model::vertex*, std::list<std::pair<const model::edge*, const model::vertex*>>, model::vertex::less>;

std::vector<const model::vertex*> get_selected_vertices(const model::graph& graph);
std::vector<const model::edge*> get_selected_edges(const model::graph& graph);
void unselect_all(const model::graph& graph);
void recolor_all_edges(const model::graph& graph, const glm::vec3& color);
void recolor_all_vertices(const model::graph& graph, const glm::vec3& color);
void select(const model::graph& graph, const camera& cam, float screen_x, float screen_y, float distance);
adjacency_lists generate_adjacency_lists(const model::graph& graph);
}