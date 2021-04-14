#pragma once

#include <graph.hpp>
#include <generic_shader.hpp>
#include <vertex_buffer.hpp>
#include <camera.hpp>
#include <font_renderer.hpp>
#include <gui_brush.hpp>
#include <game_event_dispatcher.hpp>

class graph_renderer
  : public event_handler<e_set_label_rendering_mode>
{
    vertex_buffer vertex_template_vb_;
    vertex_buffer edge_template_vb_;
    generic_shader pos_color_shader_;
    bool render_labels_;

    static std::vector<glm::vec2> generate_circle(unsigned edge_count, float radius);

  public:

    graph_renderer(game_event_dispatcher& game_dispatcher);
    void render(const model::graph& graph, const camera& cam, gui_brush& brush);
    virtual void on_event(const e_set_label_rendering_mode& e) override;
};
