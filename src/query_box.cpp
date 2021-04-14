#include <query_box.hpp>

query_box::query_box(const glm::vec2& loc, std::function<void(const std::wstring&)> on_ok)
  : widget(loc, glm::vec2(150.0f, 150.0f)),
    b_ok_(glm::vec2(loc.x + 50.0f, loc.y + 80.0f), glm::vec2(50.0f, 50.0f), L"right", [this, on_ok]()
{
  on_ok(textfield_.get_text());
}),
textfield_(glm::vec2(loc.x + 20.0f, loc.y + 20.0f), glm::vec2(110.0f, 40.0f), true)
{
}

void query_box::draw(gui_brush& brush)
{
  brush.draw_tile(loc_, size_, L"solid_background");
  textfield_.draw(brush);
  b_ok_.draw(brush);
}

bool query_box::on_click(float x, float y, bool press_or_release)
{
  if (b_ok_.loc().x < x &&
      b_ok_.loc().x + b_ok_.size().x > x &&
      b_ok_.loc().y < y &&
      b_ok_.loc().y + b_ok_.size().y > y)
    return b_ok_.on_click(x, y, press_or_release);
  return true;
}

void query_box::on_focus_changed(const widget* new_front_element)
{
}

bool query_box::on_key(wchar_t keycode)
{
  return textfield_.on_key(keycode);
}

void query_box::on_unicode(unsigned codepoint)
{
  textfield_.on_unicode(codepoint);
}
