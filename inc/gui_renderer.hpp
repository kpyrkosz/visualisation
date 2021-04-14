#pragma once

#include <font_renderer.hpp>
#include <gui_brush.hpp>
#include <tileset.hpp>
#include <generic_shader.hpp>
#include <wire_square_template.hpp>
#include <window.hpp>
#include <font.hpp>
#include <map>
#include <window_event_dispatcher.hpp>

class gui_renderer
  : public gui_brush,
    public event_handler<e_window_resized>
{
    wire_square_template square_template_;
    generic_shader tile_drawer_;
    font_renderer font_renderer_;
    font text_comic_;
    font text_arial_;
    font ebrima_24_bold_;
    tileset button_tileset_;
    const std::map<std::wstring, unsigned> tilename_to_index_;
    glm::mat4 ortho_proj_;

  public:

    gui_renderer(event_handler_registrar<e_window_resized>& reg);
    virtual void draw_text(const std::wstring& text, float x, float y, const glm::vec3& color, font_type type) override;
    virtual void draw_tile(const glm::vec2& loc, const glm::vec2& size, const std::wstring& tilename) override;
    virtual void on_event(const e_window_resized& e) override;
};
