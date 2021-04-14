#pragma once

#include <widget.hpp>
#include <deque>
#include <game_event_dispatcher.hpp>

class log_window
  : public widget,
    public event_handler<e_log_msg>
{

    std::deque<std::wstring> log_;

  public:

    log_window(const glm::vec2& loc, const glm::vec2& size, event_handler_registrar<e_log_msg>& reg);
    virtual void draw(gui_brush& brush) override;
    virtual bool on_click(float x, float y, bool press_or_release) override;
    virtual void on_focus_changed(const widget* new_front_element) override;
    virtual bool on_key(wchar_t keycode) override;

    virtual void on_event(const e_log_msg& e) override;
};