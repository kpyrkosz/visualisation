#include <graph_renderer.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

std::vector<glm::vec2> edge_model(
{
  { 0, -1 },
  { 0, 1 },
  { 1, -1 },
  { 0, 1 },
  { 1, 1 },
  { 1, -1 }
});

std::vector<glm::vec2> graph_renderer::generate_circle(unsigned edge_count, float radius)
{
  std::vector<glm::vec2> res(edge_count * 3);
  float curr_angle = 0.0f;
  const float step = glm::pi<float>() * (2.0f / static_cast<float>(edge_count));
  for (unsigned i = 0; i < edge_count; ++i)
  {
    res[3 * i] = { 0, 0 };
    res[3 * i + 2] = { radius * cos(curr_angle), radius * sin(curr_angle) };
    curr_angle += step;
    res[3 * i + 1] = { radius * cos(curr_angle), radius * sin(curr_angle) };
  }
  return res;
}

graph_renderer::graph_renderer(game_event_dispatcher& game_dispatcher)
  : event_handler<e_set_label_rendering_mode>(game_dispatcher),
    vertex_template_vb_(generate_circle(16, 30.0f)),
    edge_template_vb_(edge_model),
    pos_color_shader_(R"(rsrc/pos_color.vs)", R"(rsrc/pos_color.fs)"),
    render_labels_(true)
{
}

void graph_renderer::render(const model::graph& graph, const camera& cam, gui_brush& brush)
{
  pos_color_shader_.use();
  for (const auto& e : graph.edges())
  {
    float angle = glm::orientedAngle({ 1, 0 }, glm::normalize(e.to.loc - e.from.loc));
    glm::mat4 edge_transform = glm::translate(glm::mat4(1), glm::vec3(e.from.loc.x, e.from.loc.y, 0));
    edge_transform = glm::rotate(edge_transform, angle, { 0, 0, 1 });
    edge_transform = glm::scale(edge_transform, { glm::length(e.from.loc - e.to.loc), 3, 1 });
    if (e.is_selected)
    {
      pos_color_shader_.set_3f_uniform("color", color::blue);
      glm::mat4 outline_transform = glm::translate(glm::mat4(1), glm::vec3(e.from.loc.x, e.from.loc.y, 0));
      outline_transform = glm::rotate(outline_transform, angle, { 0, 0, 1 });
      outline_transform = glm::scale(outline_transform, {1.0f, 1.3f, 1.0f });
      outline_transform = glm::scale(outline_transform, { glm::length(e.from.loc - e.to.loc), 3, 1 });
      pos_color_shader_.set_mat4_uniform("transform", cam.get_transform() * outline_transform);
      edge_template_vb_.draw();
    }
    pos_color_shader_.set_3f_uniform("color", e.color);
    pos_color_shader_.set_mat4_uniform("transform", cam.get_transform() * edge_transform);
    edge_template_vb_.draw();
  }
  for (const auto& v : graph.vertices())
  {
    if (v.is_selected)
    {
      pos_color_shader_.set_3f_uniform("color", color::green);
      glm::mat4 transform = glm::translate(glm::mat4(1), glm::vec3(v.loc.x, v.loc.y, 0));
      transform = glm::scale(transform, glm::vec3(1.3f, 1.3f, 1.0f));
      pos_color_shader_.set_mat4_uniform("transform", cam.get_transform() * transform);
      vertex_template_vb_.draw();
    }
    pos_color_shader_.set_3f_uniform("color", v.color);
    glm::mat4 translation = glm::translate(glm::mat4(1), glm::vec3(v.loc.x, v.loc.y, 0));
    pos_color_shader_.set_mat4_uniform("transform", cam.get_transform() * translation);
    vertex_template_vb_.draw();
  }
  if (render_labels_)
  {
    for (const auto& e : graph.edges())
    {
      glm::vec2 midpoint = glm::vec2(e.from.loc.x + e.to.loc.x, e.from.loc.y + e.to.loc.y) * 0.5f;
      midpoint = cam.world_to_screen(midpoint.x, midpoint.y);
      brush.draw_text(std::to_wstring(e.weight), midpoint.x, midpoint.y - 25.0f, color::blue, font_type::ebrima_24_bold);
    }
  }
}

void graph_renderer::on_event(const e_set_label_rendering_mode& e)
{
  render_labels_ = e.enable_or_disable;
}
