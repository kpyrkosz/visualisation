#include <input_dispositor.hpp>
#include <GLFW/glfw3.h>

input_dispositor::input_dispositor(gui& g, application& app, window_event_dispatcher& window_disp)
  : event_handler<e_keypress>(window_disp),
    event_handler<e_mouse_clicked>(window_disp),
    event_handler<e_unicode_keypress>(window_disp),
    gui_(g),
    app_(app)
{

}

void input_dispositor::on_event(const e_keypress& e)
{
  if (gui_.on_key(e))
    return;
  app_.on_key(e.key);
}

void input_dispositor::on_event(const e_mouse_clicked& e)
{
  if (gui_.on_click(e))
    return;
  if (e.action == GLFW_PRESS && e.button == GLFW_MOUSE_BUTTON_LEFT)
    app_.on_left_click(e.xpos, e.ypos);
}

void input_dispositor::on_event(const e_unicode_keypress& e)
{
  gui_.on_unicode(e);
}
