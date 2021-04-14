#include <gui_renderer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

gui_renderer::gui_renderer(event_handler_registrar<e_window_resized>& reg)
  : event_handler<e_window_resized>(reg),
    tile_drawer_(R"(rsrc/tileset.vs)", R"(rsrc/tileset.fs)"),
    text_comic_(font_loader(R"(rsrc/font.fnt)")),
    text_arial_(font_loader(R"(rsrc/arial_15.fnt)")),
    ebrima_24_bold_(font_loader(R"(rsrc/ebrima_24_bold.fnt)")),
    button_tileset_(R"(rsrc/buttons_better.png)", 4),
    tilename_to_index_
{
  {
    {
      L"play", 0
    },
    {
      L"pause", 1
    },
    {
      L"step", 2
    },
    {
      L"exit", 3
    },
    {
      L"left", 4
    },
    {
      L"right", 5
    },
    {
      L"export", 6
    },
    {
      L"import", 7
    },
    {
      L"refresh", 8
    },
    {
      L"solid_background", 14
    },
    {
      L"background", 15
    },

  }
}
{
  ortho_proj_ = glm::ortho<float>(0, 1024, 768, 0);
}

void gui_renderer::draw_text(const std::wstring& text, float x, float y, const glm::vec3& color, font_type type)
{
  font* selected_font;
  switch (type)
  {
    case font_type::arial_15:
      selected_font = &text_arial_;
      break;
    case font_type::comic_32:
      selected_font = &text_comic_;
      break;
    case font_type::ebrima_24_bold:
      selected_font = &ebrima_24_bold_;
      break;
    default: // unknown font
      return;
  }
  font_renderer_.use(ortho_proj_, *selected_font);
  //auto length_of_text = selected_font->get_text_size(text);
  font_renderer_.draw_text(text, x, y, color);
}

void gui_renderer::draw_tile(const glm::vec2& loc, const glm::vec2& size, const std::wstring& tilename)
{
  glm::mat3 transform(1);
  transform = glm::translate(transform, loc);
  transform = glm::scale(transform, size);
  tile_drawer_.use();
  tile_drawer_.set_mat3_uniform("transform", transform);
  tile_drawer_.set_1f_uniform("tile_index", tilename_to_index_.at(tilename));
  tile_drawer_.set_1f_uniform("tileset_row_count", button_tileset_.get_row_count());
  tile_drawer_.set_uint_uniform("sampler", 7);
  tile_drawer_.set_mat4_uniform("ortho", ortho_proj_);
  button_tileset_.get_tile_tex().activate(7);
  square_template_.bind_to_pipeline();
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisable(GL_BLEND);
}

void gui_renderer::on_event(const e_window_resized& e)
{
  ortho_proj_ = glm::ortho<float>(0, e.width, e.height, 0);
}
