#pragma once

#include <glm/glm.hpp>
#include <string>
#include <tileset.hpp>
#include <color.hpp>

enum class font_type
{
  comic_32,
  arial_15,
  ebrima_24_bold,
};

class gui_brush
{
  public:
    virtual void draw_text(const std::wstring& text, float x, float y, const glm::vec3& color, font_type type) = 0;
    virtual void draw_tile(const glm::vec2& loc, const glm::vec2& size, const std::wstring& tilename) = 0;
    //~not
};