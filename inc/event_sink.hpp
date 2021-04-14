#pragma once

#include <event.hpp>
#include <queue>
#include <memory>

template<typename DispatcherT>
class event_sink
{

  protected:

    std::queue<std::unique_ptr<event<DispatcherT>>> event_q_;

  public:
    event_sink() = default;
    event_sink(const event_sink&) = delete;

    void add_event(std::unique_ptr<event<DispatcherT>> e)
    {
      event_q_.push(std::move(e));
    }
};