#pragma once

template <typename EventT>
class event_handler_registrar;

template <typename EventT, typename Registrar = event_handler_registrar<EventT>>
class event_handler
{

    Registrar& my_owner_;

  public:

    event_handler(Registrar& reg)
      : my_owner_(reg)
    {
      my_owner_.register_me(*this);
    }
    event_handler(const event_handler& rhs) = delete;
    ~event_handler()
    {
      my_owner_.unregister_me(*this);
    }

    virtual void on_event(const EventT& e) = 0;
};