#include <wire_square_template.hpp>

wire_square_template::wire_square_template()
{
  /*
  x
  y
  z (const 1.0)
  u
  v
  */
  GLfloat vertices[] =
  {
    0, 1, 1, 0, 1,
    0, 0, 1, 0, 0,
    1, 1, 1, 1, 1,
    1, 0, 1, 1, 0,
  };

  GLushort elements[] =
  {
    0, 1, 2, 1, 3, 2
  };

  glGenVertexArrays(1, &VAO_);
  glGenBuffers(1, &VBO_);
  glGenBuffers(1, &EBO_);
  glBindVertexArray(VAO_);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

  //pos
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
  glEnableVertexAttribArray(0);

  //uv
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

wire_square_template::~wire_square_template()
{
  glDeleteVertexArrays(1, &VAO_);
  glDeleteBuffers(1, &VBO_);
  glDeleteBuffers(1, &EBO_);
}

void wire_square_template::bind_to_pipeline() const
{
  glBindVertexArray(VAO_);
}
