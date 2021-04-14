#pragma once

#include <vertex.hpp>
#include <edge.hpp>
#include <set>
#include <number_pool.hpp>

namespace model
{

class graph
{
  public:

    using vertex_collection = std::set<vertex, vertex::less>;
    using edge_collection = std::set<edge, edge::less>;

  private:

    vertex_collection vertices_;
    edge_collection edges_;
    number_pool vertices_index_pool_;

  public:

    const vertex& add_vertex(const std::string& label, float x, float y);
    void remove_vertex(const vertex& v);

    void add_edge(const vertex& from, const vertex& to, int weight = 0, const std::string& label = "");
    void remove_edge(const edge& e);

    const vertex_collection& vertices() const;
    const edge_collection& edges() const;

    void clear();
};

}