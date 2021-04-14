#pragma once

#include <GL/glew.h>
#include <vector>

class vertex_buffer
{

    GLuint VAO_;
    std::vector<GLuint> VBO_;
    std::size_t num_vertices_;

    template <typename FirstLayoutType>
    void do_init(unsigned index, const std::vector<FirstLayoutType>& flt);

    template <typename FirstLayoutType, typename ... RestLayout>
    void do_init(unsigned index, const std::vector<FirstLayoutType>& flt, RestLayout&& ... rl);

  public:

    template <typename ... Layout>
    vertex_buffer(Layout ... types);

    vertex_buffer(const vertex_buffer&) = delete;
    vertex_buffer(vertex_buffer&& rhs);
    vertex_buffer& operator=(const vertex_buffer&) = delete;
    vertex_buffer& operator=(vertex_buffer&&) = delete;
    ~vertex_buffer();

    void draw() const;
};

template<typename FirstLayoutType>
inline void vertex_buffer::do_init(unsigned index, const std::vector<FirstLayoutType>& flt)
{
  num_vertices_ = flt.size();
  glBindBuffer(GL_ARRAY_BUFFER, VBO_[index]);
  glBufferData(GL_ARRAY_BUFFER, flt.size() * sizeof(FirstLayoutType), &flt[0], GL_STATIC_DRAW);
  glVertexAttribPointer(index, sizeof(FirstLayoutType) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(FirstLayoutType), (GLvoid*)0);
  glEnableVertexAttribArray(index);
}

template<typename FirstLayoutType, typename ...RestLayout>
inline void vertex_buffer::do_init(unsigned index, const std::vector<FirstLayoutType>& flt, RestLayout&& ...rl)
{
  glBindBuffer(GL_ARRAY_BUFFER, VBO_[index]);
  glBufferData(GL_ARRAY_BUFFER, flt.size() * sizeof(FirstLayoutType), &flt[0], GL_STATIC_DRAW);
  glVertexAttribPointer(index, sizeof(FirstLayoutType) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(FirstLayoutType), (GLvoid*)0);
  glEnableVertexAttribArray(index);
  do_init(++index, rl...);
}

template<typename ...Layout>
inline vertex_buffer::vertex_buffer(Layout ...types)
  : VBO_(sizeof...(Layout))
{
  glGenVertexArrays(1, &VAO_);
  glGenBuffers(VBO_.size(), VBO_.data());
  glBindVertexArray(VAO_);

  do_init(0, types...);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}
