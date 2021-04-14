#pragma once

#include <font.hpp>
#include <generic_shader.hpp>

class font_renderer
{
    generic_shader text_shader_;
    mutable const font* currently_used_font_;

  public:

    font_renderer();
    font_renderer(const font_renderer&) = delete;

    void use(const glm::mat4& ortho, const font& the_font) const;
    void draw_text(const std::wstring& text, float screen_x, float screen_y, const glm::vec3& color) const;
};