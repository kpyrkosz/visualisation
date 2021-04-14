#include <log_window.hpp>

log_window::log_window(const glm::vec2& loc, const glm::vec2& size, event_handler_registrar<e_log_msg>& reg)
  : widget(loc, size),
    event_handler<e_log_msg>(reg)
{
  log_.push_back(L"Log window!");
}

void log_window::draw(gui_brush& brush)
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  brush.draw_tile(loc_, size_, L"background");
  glDisable(GL_BLEND);
  float y = loc_.y + 3.0f;
  for (const auto& elem : log_)
  {
    brush.draw_text(elem, loc_.x + 3.0f, y, color::white, font_type::arial_15);
    y += 12.0f;
  }
}

bool log_window::on_click(float x, float y, bool press_or_release)
{
  return true;
}

void log_window::on_event(const e_log_msg& e)
{
  log_.push_back(e.msg);
  while (log_.size() > 32)
    log_.pop_front();
}

void log_window::on_focus_changed(const widget* new_front_element)
{
}

bool log_window::on_key(wchar_t keycode)
{
  return false;
}
