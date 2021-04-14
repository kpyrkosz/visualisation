#pragma once

#include <event_sink.hpp>
#include <event_handler_registrar.hpp>

struct e_button_pressed;
struct e_play_request;
struct e_import_request;
struct e_export_request;
struct e_widget_request_suicide;

class gui_event_dispatcher
  : public event_sink<gui_event_dispatcher>,
    public event_handler_registrar<e_button_pressed>,
    public event_handler_registrar<e_play_request>,
    public event_handler_registrar<e_import_request>,
    public event_handler_registrar<e_export_request>,
    public event_handler_registrar<e_widget_request_suicide>
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

struct e_button_pressed : event<gui_event_dispatcher>
{
  const std::wstring button_name;

  e_button_pressed(const std::wstring& button_name)
    : button_name(button_name)
  {}

  virtual void accept(gui_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_play_request : event<gui_event_dispatcher>
{
  const std::wstring name;

  e_play_request(const std::wstring& name)
    : name(name)
  {}

  virtual void accept(gui_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_widget_request_suicide : event<gui_event_dispatcher>
{
  class widget* me;

  e_widget_request_suicide(class widget* me)
    : me(me)
  {}

  virtual void accept(gui_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_import_request : event<gui_event_dispatcher>
{
  const std::wstring name;

  e_import_request(const std::wstring& name)
    : name(name)
  {}

  virtual void accept(gui_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_export_request : event<gui_event_dispatcher>
{
  const std::wstring name;

  e_export_request(const std::wstring& name)
    : name(name)
  {}

  virtual void accept(gui_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};
