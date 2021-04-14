#include <window.hpp>
#include <stdexcept>
#include <cmath>

void window::key_callback_(GLFWwindow* wnd, int key, int scancode, int action, int mode)
{
  window* this_instance = (window*)glfwGetWindowUserPointer(wnd);
  if (this_instance == nullptr)
    return;
  this_instance->window_event_sink_.add_event(std::make_unique<e_keypress>(key, scancode, action, mode));
}

void window::mouse_click_callback_(GLFWwindow* wnd, int button, int action, int mods)
{
  window* this_instance = (window*)glfwGetWindowUserPointer(wnd);
  if (this_instance == nullptr)
    return;
  double xpos, ypos;
  glfwGetCursorPos(wnd, &xpos, &ypos);
  this_instance->window_event_sink_.add_event(std::make_unique<e_mouse_clicked>(floor(static_cast<float>(xpos)), floor(static_cast<float>(ypos)), button, action, mods));
}

void window::resize_callback_(GLFWwindow* wnd, int width, int height)
{
  window* this_instance = (window*)glfwGetWindowUserPointer(wnd);
  if (this_instance == nullptr)
    return;
  this_instance->width_ = width;
  this_instance->height_ = height;
  glViewport(0, 0, width, height);
  this_instance->window_event_sink_.add_event(std::make_unique<e_window_resized>(width, height));
}

void window::mouse_move_callback_(GLFWwindow* wnd, double xpos, double ypos)
{
  window* this_instance = (window*)glfwGetWindowUserPointer(wnd);
  if (this_instance == nullptr)
    return;
  this_instance->window_event_sink_.add_event(std::make_unique<e_mouse_moved>(static_cast<float>(xpos), static_cast<float>(ypos)));
}

void window::scroll_callback_(GLFWwindow* wnd, double xoffset, double yoffset)
{
  window* this_instance = (window*)glfwGetWindowUserPointer(wnd);
  if (this_instance == nullptr)
    return;
  if(yoffset != 0.0)
    this_instance->window_event_sink_.add_event(std::make_unique<e_scroll>(static_cast<float>(yoffset)));
}

void window::character_callback(GLFWwindow* wnd, unsigned int codepoint)
{
  window* this_instance = (window*)glfwGetWindowUserPointer(wnd);
  if (this_instance == nullptr)
    return;
  this_instance->window_event_sink_.add_event(std::make_unique<e_unicode_keypress>(codepoint));
}

window::window(int width, int height, event_sink<window_event_dispatcher>& window_event_sink)
  : window_event_sink_(window_event_sink),
    width_(width),
    height_(height)
{
  the_window_ = glfwCreateWindow(width, height, "Wizualizacja algorytmow grafowych", nullptr, nullptr);
  glfwMakeContextCurrent(the_window_);

  glfwSetInputMode(the_window_, GLFW_STICKY_KEYS, GL_TRUE);

  glewExperimental = true;
  if (glewInit() != GLEW_OK)
    throw std::runtime_error("GLEW init failed");

  glfwSetWindowUserPointer(the_window_, this);
  glfwSetKeyCallback(the_window_, key_callback_);
  glfwSetMouseButtonCallback(the_window_, mouse_click_callback_);
  glfwSetWindowSizeCallback(the_window_, resize_callback_);
  glfwSetCursorPosCallback(the_window_, mouse_move_callback_);
  glfwSetScrollCallback(the_window_, scroll_callback_);
  glfwSetCharCallback(the_window_, character_callback);
}

void window::swap_buffers()
{
  glfwSwapBuffers(the_window_);
}

void window::set_closing()
{
  glfwSetWindowShouldClose(the_window_, 1);
}

bool window::is_closing() const
{
  return glfwWindowShouldClose(the_window_) != 0;
}
