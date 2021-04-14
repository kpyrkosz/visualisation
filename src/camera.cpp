#include <camera.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

void camera::recalc_transform()
{
  transform_ = glm::ortho<float>(x_look_at_ - current_zoom_ * display_width_,
                                 x_look_at_ + current_zoom_ * display_width_,
                                 y_look_at_ - current_zoom_ * display_height_,
                                 y_look_at_ + current_zoom_ * display_height_);
  inverse_transform_ = glm::inverse(transform_);
}

camera::camera(float initial_width, float initial_height, window_event_dispatcher& wnd_dispatcher)
  : event_handler<e_window_resized>(wnd_dispatcher),
    event_handler<e_scroll>(wnd_dispatcher),
    event_handler<e_keypress>(wnd_dispatcher),
    x_look_at_(0.0f),
    y_look_at_(0.0f),
    current_zoom_(2.0f),
    display_width_(initial_width),
    display_height_(initial_height)
{
  recalc_transform();
}

glm::vec2 camera::screen_to_world(float screen_x, float screen_y) const
{
  glm::vec2 res(screen_x, screen_y);
  res.x /= display_width_;
  res.y /= display_height_;
  res *= 2.0f;
  res -= 1.0f;
  res.y *= -1.0f;
  return inverse_transform_ * glm::vec4(res, 0.0f, 1.0f);
}

glm::vec2 camera::world_to_screen(float world_x, float world_y) const
{
  glm::vec2 res = transform_ * glm::vec4(world_x, world_y, 0.0f, 1.0f);
  res.y *= -1.0f;
  res += 1.0f;
  res *= 0.5f;
  res.x *= display_width_;
  res.y *= display_height_;
  return res;
}

void camera::zoom(float offset)
{
  current_zoom_ = glm::clamp(current_zoom_ - offset, nearest_zoom, farthest_zoom);
  recalc_transform();
}

void camera::move(float x_offset, float y_offset)
{
}

const glm::mat4& camera::get_transform() const
{
  return transform_;
}

void camera::on_event(const e_window_resized& e)
{
  display_width_ = e.width;
  display_height_ = e.height;
  recalc_transform();
}

void camera::on_event(const e_scroll& e)
{
  zoom(e.offset);
}

void camera::on_event(const e_keypress& e)
{
  if (e.action != GLFW_PRESS && e.action != GLFW_REPEAT)
    return;
  switch (e.key)
  {
    case GLFW_KEY_LEFT:
      x_look_at_ += 10.0f;
      break;
    case GLFW_KEY_RIGHT:
      x_look_at_ -= 10.0f;
      break;
    case GLFW_KEY_UP:
      y_look_at_ -= 10.0f;
      break;
    case GLFW_KEY_DOWN:
      y_look_at_ += 10.0f;
      break;
    default:
      return;
  }
  recalc_transform();
}
