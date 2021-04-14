#pragma once

#include <event_handler.hpp>
#include <unordered_set>

template <typename EventT>
class event_handler_registrar
{

  protected:

    std::unordered_set<event_handler<EventT>*> handlers_;

  public:

    void register_me(event_handler<EventT>& h)
    {
      handlers_.insert(&h);
    }

    void unregister_me(event_handler<EventT>& h)
    {
      handlers_.erase(&h);
    }
};