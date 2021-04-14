#pragma once

#include <widget.hpp>
#include <string>

class textfield
  : public widget
{
    std::wstring text_;
    bool receives_input_;

  public:

    textfield(const glm::vec2& loc, const glm::vec2& size, bool receives_input);
    const std::wstring& get_text() const;
    void set_text(const std::wstring& text);
    virtual void draw(gui_brush& brush) override;
    virtual bool on_click(float x, float y, bool press_or_release) override;
    virtual void on_focus_changed(const widget* new_front_element) override;
    virtual bool on_key(wchar_t keycode) override;
    virtual void on_unicode(unsigned codepoint) override;
};