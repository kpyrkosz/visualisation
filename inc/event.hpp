#pragma once

template <typename DispatcherT>
struct event
{
  virtual void accept(DispatcherT& d) = 0;
  virtual ~event() = default;
};
