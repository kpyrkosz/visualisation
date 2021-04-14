#pragma once

#include <widget.hpp>
#include <event_sink.hpp>
#include <gui_event_dispatcher.hpp>
#include <functional>

class button
  : public widget
{

    const std::wstring name_;
    std::function<void()> on_click_;

  public:

    button(const glm::vec2& loc, const glm::vec2& size, const std::wstring& name, event_sink<gui_event_dispatcher>& gui_sink);
    button(const glm::vec2& loc, const glm::vec2& size, const std::wstring& name, std::function<void()> on_click);
    virtual void draw(gui_brush& brush) override;
    virtual bool on_click(float x, float y, bool press_or_release) override;
    virtual void on_focus_changed(const widget* new_front_element) override;
    virtual bool on_key(wchar_t keycode) override;
};