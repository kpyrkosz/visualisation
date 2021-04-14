#include <vertex_buffer.hpp>

vertex_buffer::vertex_buffer(vertex_buffer&& rhs)
  : VAO_(rhs.VAO_),
    VBO_(std::move(rhs.VBO_)),
    num_vertices_(rhs.num_vertices_)
{
  rhs.VAO_ = 0;
}

vertex_buffer::~vertex_buffer()
{
  if (VAO_) glDeleteVertexArrays(1, &VAO_);
  if (VBO_.size()) glDeleteBuffers(VBO_.size(), VBO_.data());
}

void vertex_buffer::draw() const
{
  glBindVertexArray(VAO_);
  glDrawArrays(GL_TRIANGLES, 0, num_vertices_);
}

