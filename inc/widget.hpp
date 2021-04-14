#pragma once

#include <gui_brush.hpp>

class widget
{
  protected:

    const glm::vec2 loc_;
    const glm::vec2 size_;

  public:

    widget(const glm::vec2& loc, const glm::vec2& size)
      : loc_(loc),
        size_(size)
    {}

    inline const glm::vec2& loc() const
    {
      return loc_;
    }

    inline const glm::vec2& size() const
    {
      return size_;
    }

    virtual void draw(gui_brush& brush) = 0;
    virtual bool on_click(float x, float y, bool press_or_release) = 0; // this is very bad now i realize - not every widget is clickable
    virtual void on_focus_changed(const widget* new_front_element) = 0;
    virtual bool on_key(wchar_t keycode) = 0;
    virtual void on_unicode(unsigned) {}
    virtual ~widget() = default;
};