#pragma once

#include <font_loader.hpp>
#include <texture.hpp>
#include <GL/glew.h>
#include <map>

class font
{
    texture font_tex_;
    GLuint VAO_, VBO_;
    std::map<unsigned, unsigned> char_id_to_vbo_index_;
    std::vector<float> offset_data_;

  public:

    font(const font_loader& font);
    ~font();

    const texture& get_font_tex() const;
    unsigned char_id_to_vbo_index(unsigned char_id) const;
    float get_advancement(unsigned char_id) const;
    void bind() const;
    int get_text_size(const std::string& text) const;
};
