#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <window_event_dispatcher.hpp>
#include <utility>

class window
{
    GLFWwindow* the_window_;
    event_sink<window_event_dispatcher>& window_event_sink_;
    int width_, height_;

    static void key_callback_(GLFWwindow* wnd, int key, int scancode, int action, int mode);
    static void mouse_click_callback_(GLFWwindow* wnd, int button, int action, int mods);
    static void resize_callback_(GLFWwindow* wnd, int width, int height);
    static void mouse_move_callback_(GLFWwindow* wnd, double xpos, double ypos);
    static void scroll_callback_(GLFWwindow* wnd, double xoffset, double yoffset);
    static void character_callback(GLFWwindow* wnd, unsigned int codepoint);

  public:

    window(int width, int height, event_sink<window_event_dispatcher>& window_event_sink);

    void set_closing();
    bool is_closing() const;
    void swap_buffers();
};