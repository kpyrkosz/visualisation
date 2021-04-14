#include <button.hpp>

button::button(const glm::vec2& loc, const glm::vec2& size, const std::wstring& name, event_sink<gui_event_dispatcher>& gui_sink)
  : button(loc, size, name, [ & gui_sink, this]()
{
  gui_sink.add_event(std::make_unique<e_button_pressed>(name_));
})
{
}

button::button(const glm::vec2& loc, const glm::vec2& size, const std::wstring& name, std::function<void()> on_click)
  : widget(loc, size),
    name_(name),
    on_click_(std::move(on_click))
{
}

void button::draw(gui_brush& brush)
{
  brush.draw_tile(loc_, size_, name_);
}

bool button::on_click(float x, float y, bool press_or_release)
{
  if(!press_or_release)
    on_click_();
  return true;
}

void button::on_focus_changed(const widget* new_front_element)
{
}

bool button::on_key(wchar_t keycode)
{
  return false;
}
