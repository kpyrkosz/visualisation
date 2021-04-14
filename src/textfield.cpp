#include <textfield.hpp>
#include <GLFW/glfw3.h>

textfield::textfield(const glm::vec2& loc, const glm::vec2& size, bool receives_input)
  : widget(loc, size),
    receives_input_(receives_input)
{
}

const std::wstring& textfield::get_text() const
{
  return text_;
}

void textfield::set_text(const std::wstring& text)
{
  text_ = text;
}

void textfield::draw(gui_brush& brush)
{
  brush.draw_tile(loc_, size_, L"background");
  brush.draw_text(text_, loc_.x, loc_.y + 10, color::red, font_type::arial_15);
}

bool textfield::on_click(float x, float y, bool press_or_release)
{
  return true;
}

void textfield::on_focus_changed(const widget* new_front_element)
{
}

bool textfield::on_key(wchar_t keycode)
{
  if (!receives_input_)
    return false;
  if (keycode == GLFW_KEY_BACKSPACE && !text_.empty())
    text_.pop_back();
  return true;
}

void textfield::on_unicode(unsigned codepoint)
{
  if (!receives_input_)
    return;
  text_ += codepoint;
}
