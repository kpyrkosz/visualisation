#pragma once

#include <event_sink.hpp>
#include <event_handler_registrar.hpp>

struct e_keypress;
struct e_window_resized;
struct e_mouse_moved;
struct e_mouse_clicked;
struct e_scroll;
struct e_unicode_keypress;

class window_event_dispatcher
  : public event_sink<window_event_dispatcher>,
    public event_handler_registrar<e_keypress>,
    public event_handler_registrar<e_window_resized>,
    public event_handler_registrar<e_mouse_moved>,
    public event_handler_registrar<e_mouse_clicked>,
    public event_handler_registrar<e_scroll>,
    public event_handler_registrar<e_unicode_keypress>
{

  public:

    template <typename EventT>
    void dispatch(const EventT& e)
    {
      for (auto& elem : event_handler_registrar<EventT>::handlers_)
        elem->on_event(e);
    }

    void execute_all()
    {
      while (!event_q_.empty())
      {
        event_q_.front()->accept(*this);
        event_q_.pop();
      }
    }
};

struct e_keypress : event<window_event_dispatcher>
{
  int key;
  int scancode;
  int action;
  int mode;

  e_keypress(int key, int scancode, int action, int mode)
    : key(key),
      scancode(scancode),
      action(action),
      mode(mode)
  {}

  virtual void accept(window_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_window_resized : event<window_event_dispatcher>
{
  int width;
  int height;

  e_window_resized(int width, int height)
    : width(width),
      height(height)
  {}

  virtual void accept(window_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_mouse_moved : event<window_event_dispatcher>
{
  float xpos;
  float ypos;

  e_mouse_moved(float xpos, float ypos)
    : xpos(xpos),
      ypos(ypos)
  {}

  virtual void accept(window_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_mouse_clicked : event<window_event_dispatcher>
{
  float xpos;
  float ypos;
  int button;
  int action;
  int mods;

  e_mouse_clicked(float xpos, float ypos, int button, int action, int mods)
    : xpos(xpos),
      ypos(ypos),
      button(button),
      action(action),
      mods(mods)
  {}

  virtual void accept(window_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_scroll : event<window_event_dispatcher>
{
  float offset;

  e_scroll(float offset)
    : offset(offset)
  {}

  virtual void accept(window_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_unicode_keypress : event<window_event_dispatcher>
{
  unsigned codepoint;

  e_unicode_keypress(unsigned codepoint)
    : codepoint(codepoint)
  {}

  virtual void accept(window_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};
