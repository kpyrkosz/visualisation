#pragma once

#include <list>
#include <widget.hpp>
#include <memory>
#include <gui_event_dispatcher.hpp>
#include <window_event_dispatcher.hpp>
#include <game_event_dispatcher.hpp>

class gui
  : public event_handler<e_widget_request_suicide>
{
    event_sink<gui_event_dispatcher>& gui_sink_;
    std::list<std::shared_ptr<widget>> widgets_; // widget on front is the active one

  public:

    gui(gui_event_dispatcher& gui_dispatcher, game_event_dispatcher& g_events);
    void render(gui_brush& brush) const;
    bool on_click(const e_mouse_clicked& e);
    bool on_key(const e_keypress& e) const;
    void on_unicode(const e_unicode_keypress& e) const;
    virtual void on_event(const e_widget_request_suicide& e) override;
};