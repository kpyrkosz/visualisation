#include <renderer.hpp>
#include <color.hpp>

renderer::renderer(window_event_dispatcher& w_disp, game_event_dispatcher& game_dispatcher)
  : gr_(game_dispatcher),
    gui_r_(w_disp)
{
}

void renderer::render(const model::graph& gr, const gui& the_gui, const camera& cam)
{
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDisable(GL_BLEND);
  gr_.render(gr, cam, gui_r_);
  the_gui.render(gui_r_);
}
