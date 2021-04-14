#include <graph.hpp>
#include <stdexcept>

namespace model
{

const vertex& graph::add_vertex(const std::string& label, float x, float y)
{
  auto id = vertices_index_pool_.get();
  auto result = vertices_.insert(vertex(id, label, x, y));
  return *result.first;
}

void graph::remove_vertex(const vertex& v)
{
  vertices_index_pool_.put_back(v.index);
  for (auto it = edges_.begin(); it != edges_.end();)
  {
    if(it->from == v || it->to == v)
      it = edges_.erase(it);
    else ++it;
  }
  vertices_.erase(v);
}

void graph::add_edge(const vertex& from, const vertex& to, int weight, const std::string& label)
{
  if (from.index > to.index)
    return add_edge(to, from, weight, label);
  if (from.index == to.index)
    throw std::invalid_argument("Edge must connect separate vertices");
  edge to_add(from, to);
  if (edges_.count(to_add))
    return;
  edges_.emplace(edge(from, to, weight, label));
}

void graph::remove_edge(const edge& e)
{
  edges_.erase(e);
}

const graph::vertex_collection& graph::vertices() const
{
  return vertices_;
}

const graph::edge_collection& graph::edges() const
{
  return edges_;
}

void graph::clear()
{
  vertices_index_pool_.reset();
  vertices_.clear();
  edges_.clear();
}

}