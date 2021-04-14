#pragma once

#include <GL/glew.h>

class wire_square_template
{

    GLuint VBO_, VAO_, EBO_;

  public:

    wire_square_template();
    wire_square_template(const wire_square_template& rhs) = delete;
    ~wire_square_template();

    void bind_to_pipeline() const;
};