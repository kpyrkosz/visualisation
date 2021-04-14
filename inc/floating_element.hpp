#pragma once

#include <widget.hpp>
#include <string>
#include <gui_event_dispatcher.hpp>

template<typename DecoratedWidget>
class floating_element
  : public DecoratedWidget
{
    event_sink<gui_event_dispatcher>& gui_sink_;

  public:

    template<typename ... DecoratedInitArgs>
    floating_element(event_sink<gui_event_dispatcher>& gui_sink, DecoratedInitArgs&& ... args);
    //do not override all vrituals - use the wrapped object's implementation
    //virtual void draw(gui_brush& brush) override;
    //virtual void on_click(float x, float y, bool press_or_release) override;
    virtual void on_focus_changed(const widget* new_front_element) override;
    //virtual void on_key(wchar_t keycode) override;
};

template<typename DecoratedWidget>
template<typename ...DecoratedInitArgs>
inline floating_element<DecoratedWidget>::floating_element(event_sink<gui_event_dispatcher>& gui_sink, DecoratedInitArgs&& ...args)
  : DecoratedWidget(std::forward < DecoratedInitArgs && > (args)...),
    gui_sink_(gui_sink)
{
}

template<typename DecoratedWidget>
inline void floating_element<DecoratedWidget>::on_focus_changed(const widget* new_front_element)
{
  if (new_front_element != this)
    gui_sink_.add_event(std::make_unique<e_widget_request_suicide>(this));
}

