#pragma once

#include <window_event_dispatcher.hpp>
#include <glm/glm.hpp>

class camera
  : public event_handler<e_window_resized>,
    public event_handler<e_scroll>,
    public event_handler<e_keypress>
{
    static constexpr float nearest_zoom = 1.0f;
    static constexpr float farthest_zoom = 100.0f;

    float x_look_at_;
    float y_look_at_;
    float current_zoom_;
    float display_width_;
    float display_height_;
    glm::mat4 transform_;
    glm::mat4 inverse_transform_;

    void recalc_transform();

  public:

    camera(float initial_width, float initial_height, window_event_dispatcher& wnd_dispatcher);
    glm::vec2 screen_to_world(float screen_x, float screen_y) const;
    glm::vec2 world_to_screen(float world_x, float world_y) const;
    void zoom(float offset);
    void move(float x_offset, float y_offset);
    const glm::mat4& get_transform() const;

    virtual void on_event(const e_window_resized& e) override;
    virtual void on_event(const e_scroll& e) override;
    virtual void on_event(const e_keypress& e) override;
};