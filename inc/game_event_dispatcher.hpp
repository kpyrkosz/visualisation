#pragma once

#include <event_sink.hpp>
#include <event_handler_registrar.hpp>

struct e_algo_finished;
struct e_log_msg;
struct e_set_label_rendering_mode;

class game_event_dispatcher
  : public event_sink<game_event_dispatcher>,
    public event_handler_registrar<e_algo_finished>,
    public event_handler_registrar<e_log_msg>,
    public event_handler_registrar<e_set_label_rendering_mode>
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

struct e_algo_finished : event<game_event_dispatcher>
{
  virtual void accept(game_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_log_msg : event<game_event_dispatcher>
{
  std::wstring msg;

  e_log_msg(std::wstring msg)
    : msg(msg)
  {}

  virtual void accept(game_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};

struct e_set_label_rendering_mode : event<game_event_dispatcher>
{
  bool enable_or_disable;

  e_set_label_rendering_mode(bool enable_or_disable)
    : enable_or_disable(enable_or_disable)
  {}

  virtual void accept(game_event_dispatcher& d) override
  {
    d.dispatch(*this);
  }
};
