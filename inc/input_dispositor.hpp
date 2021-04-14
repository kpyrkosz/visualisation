#pragma once

#include <gui.hpp>
#include <application.hpp>
#include <window_event_dispatcher.hpp>

class input_dispositor
  : public event_handler<e_keypress>,
    public event_handler<e_mouse_clicked>,
    public event_handler<e_unicode_keypress>
{
    gui& gui_;
    application& app_;

  public:

    input_dispositor(gui& g, application& app, window_event_dispatcher& window_disp);

    virtual void on_event(const e_keypress& e) override;
    virtual void on_event(const e_mouse_clicked& e) override;
    virtual void on_event(const e_unicode_keypress& e) override;
};