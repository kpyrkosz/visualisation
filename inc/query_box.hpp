#pragma once

#include <button.hpp>
#include <textfield.hpp>

class query_box
  : public widget
{

    button b_ok_;
    textfield textfield_;

  public:

    query_box(const glm::vec2& loc, std::function<void(const std::wstring&)> on_ok);
    virtual void draw(gui_brush& brush) override;
    virtual bool on_click(float x, float y, bool press_or_release) override;
    virtual void on_focus_changed(const widget* new_front_element) override;
    virtual bool on_key(wchar_t keycode) override;
    virtual void on_unicode(unsigned codepoint);
};