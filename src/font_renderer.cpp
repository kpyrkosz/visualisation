#include <font_renderer.hpp>
#include <numeric>

font_renderer::font_renderer()
  : text_shader_(R"(rsrc/text.vs)", R"(rsrc/text.fs)")
{
  currently_used_font_ = nullptr;
}

void font_renderer::use(const glm::mat4& ortho, const font& the_font) const
{
  text_shader_.use();
  text_shader_.set_uint_uniform("symbol_atlas", 0);
  text_shader_.set_mat4_uniform("ortho", ortho);
  the_font.get_font_tex().activate(0);
  the_font.bind();
  currently_used_font_ = &the_font;
}

void font_renderer::draw_text(const std::wstring& text, float screen_x, float screen_y, const glm::vec3& color) const
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  text_shader_.set_3f_uniform("color", color.x, color.y, color.z);
  float advance = 0;
  for (const auto& elem : text)
  {
    auto my_index = currently_used_font_->char_id_to_vbo_index(elem);
    if (my_index == 0xFFFFFFFF)
      continue;
    auto adv = currently_used_font_->get_advancement(elem);
    text_shader_.set_2f_uniform("translation", screen_x + advance, screen_y);
    glDrawArrays(GL_TRIANGLE_STRIP, my_index * 4, 4);
    advance += adv;
  }
  glDisable(GL_BLEND);
}
