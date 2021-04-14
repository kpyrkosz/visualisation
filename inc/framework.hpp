#pragma once

#include <window.hpp>
#include <gl_context.hpp>
#include <application.hpp>
#include <renderer.hpp>
#include <memory>
#include <camera.hpp>
#include <window_event_dispatcher.hpp>
#include <gui_event_dispatcher.hpp>
#include <game_event_dispatcher.hpp>
#include <input_dispositor.hpp>

class framework
{
    gl_context glc_;
    window_event_dispatcher window_dispatcher_;
    gui_event_dispatcher gui_dispatcher_;
    game_event_dispatcher game_dispatcher_;
    window wnd_;
    model::graph graph_;
    std::unique_ptr<application> app_;
    camera cam_;
    renderer renderer_;
    gui gui_;
    input_dispositor input_disp_;

  public:

    framework(int argc, char** argv);
    int run();

};