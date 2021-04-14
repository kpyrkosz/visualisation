#include <framework.hpp>
#include <visualisation.hpp>

framework::framework(int argc, char** argv)
  : wnd_(1024, 768, window_dispatcher_),
    app_(std::make_unique<visualisation>(graph_, cam_, game_dispatcher_, gui_dispatcher_)),
    cam_(1024, 768, window_dispatcher_),
    renderer_(window_dispatcher_, game_dispatcher_),
    gui_(gui_dispatcher_, game_dispatcher_),
    input_disp_(gui_, *app_, window_dispatcher_)
{
  glfwSetTime(0);
}

int framework::run()
{
  while (!wnd_.is_closing())
  {
    static float last_tick_time = 0.0f;
    glfwPollEvents();
    window_dispatcher_.execute_all();
    gui_dispatcher_.execute_all();
    game_dispatcher_.execute_all();
    float elapsed_time = (float)glfwGetTime() - last_tick_time;
    last_tick_time += elapsed_time;
    app_->update(elapsed_time);
    renderer_.render(graph_, gui_, cam_);
    wnd_.swap_buffers();
  }
  return 0;
}
