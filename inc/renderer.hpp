#pragma once

#include <graph_renderer.hpp>
#include <gui_renderer.hpp>
#include <gui.hpp>

class renderer
{
    graph_renderer gr_;
    gui_renderer gui_r_;

  public:

    renderer(window_event_dispatcher& w_disp, game_event_dispatcher& game_dispatcher);
    void render(const model::graph& gr, const gui& the_gui, const camera& cam);
};