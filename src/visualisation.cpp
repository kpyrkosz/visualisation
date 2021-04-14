#include <visualisation.hpp>
#include <color.hpp>
#include <kruskal.hpp>
#include <dijkstra.hpp>
#include <random>
#include <GLFW/glfw3.h>
#include <graph_helpers.hpp>
#include <fstream>
#include <locale>
#include <codecvt>
#include <bfs.hpp>
#include <dfs.hpp>
#include <biparite.hpp>

visualisation::visualisation(model::graph& graph, const camera& cam, game_event_dispatcher& game_dispatcher, gui_event_dispatcher& gui_dispatcher)
  : application(graph),
    event_handler<e_button_pressed>(gui_dispatcher),
    event_handler<e_play_request>(gui_dispatcher),
    event_handler<e_import_request>(gui_dispatcher),
    event_handler<e_export_request>(gui_dispatcher),
    event_handler<e_algo_finished>(game_dispatcher),
    cam_(cam),
    game_event_sink_(game_dispatcher),
    current_mode_(idle)
{
}

void visualisation::update(float elapsed_time)
{
  static float qq = 0.0f;
  qq += elapsed_time;
  if (qq > 0.3f)
  {
    if (current_mode_ == algorithm_running)
      current_algo_->step();
    qq = 0;
  }
}

void visualisation::on_event(const e_button_pressed& e)
{
  if(current_mode_ == algorithm_stepping && e.button_name == L"step")
    current_algo_->step();
  if (e.button_name == L"exit" && (current_mode_ == algorithm_stepping || current_mode_ == algorithm_running))
  {
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Algorithm iterrupted"));
    graph_helpers::recolor_all_edges(graph_, color::light_grey);
    graph_helpers::recolor_all_vertices(graph_, color::white);
    current_mode_ = idle;
  }
  if (current_mode_ == idle && e.button_name == L"refresh")
  {
    graph_.clear();
    std::random_device rd;
    std::uniform_int_distribution<> dist(0, 80);
    const int side_size = 2 + dist(rd) / 3;
    std::vector<const model::vertex*> temp;
    for (int x = 0; x < side_size; ++x)
      for (int y = 0; y < side_size; ++y)
        temp.push_back(&graph_.add_vertex("", (x - side_size / 2) * 200 - 300 + dist(rd), (y - side_size / 2) * 200 - 500 + dist(rd)));
    for (int x = 0; x < side_size - 1; ++x)
      for (int y = 0; y < side_size - 1; ++y)
      {
        graph_.add_edge(*temp[side_size * y + x], *temp[side_size * y + x + 1], dist(rd));
        graph_.add_edge(*temp[side_size * y + x], *temp[side_size * (y + 1) + x], dist(rd));
        if (dist(rd) / 20 == 0)
          graph_.add_edge(*temp[side_size * y + x], *temp[side_size * (y + 1) + x + 1], dist(rd));
        if (dist(rd) / 20 == 0 && x != 0)
          graph_.add_edge(*temp[side_size * y + x], *temp[side_size * (y + 1) + x - 1], dist(rd));
      }
    for (int i = 0; i < side_size - 1; ++i)
    {
      graph_.add_edge(*temp[side_size * i + (side_size - 1)], *temp[side_size * (i + 1) + (side_size - 1)], dist(rd));
      graph_.add_edge(*temp[side_size * (side_size - 1) + i], *temp[side_size * (side_size - 1) + i + 1], dist(rd));
    }
  }
  if (current_mode_ == algorithm_running && e.button_name == L"pause")
    current_mode_ = algorithm_stepping;
}

void visualisation::on_event(const e_play_request& e)
{
  if (current_mode_ == idle)
  {
    graph_helpers::recolor_all_edges(graph_, color::light_grey);
    graph_helpers::recolor_all_vertices(graph_, color::white);
    if (e.name == L"Kruskal")
      current_algo_ = std::make_unique<kruskal>(graph_, game_event_sink_);
    if (e.name == L"Biparite")
      current_algo_ = std::make_unique<biparite>(graph_, game_event_sink_);
    if (e.name == L"Dijkstra")
    {
      auto verts = graph_helpers::get_selected_vertices(graph_);
      if (verts.size() != 1)
      {
        game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Select exactly one vertex as a start point"));
        return;
      }
      current_algo_ = std::make_unique<dijkstra>(graph_, verts.front(), game_event_sink_);
    }
    if (e.name == L"BFS")
    {
      auto verts = graph_helpers::get_selected_vertices(graph_);
      if (verts.size() != 1)
      {
        game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Select exactly one vertex as a start point"));
        return;
      }
      current_algo_ = std::make_unique<bfs>(graph_, verts.front(), game_event_sink_);
    }
    if (e.name == L"DFS")
    {
      auto verts = graph_helpers::get_selected_vertices(graph_);
      if (verts.size() != 1)
      {
        game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Select exactly one vertex as a start point"));
        return;
      }
      current_algo_ = std::make_unique<dfs>(graph_, verts.front(), game_event_sink_);
    }
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Starting!"));
    current_mode_ = algorithm_stepping;
    return;
  }
  if (current_mode_ == algorithm_stepping)
    current_mode_ = algorithm_running;
}

void visualisation::on_event(const e_import_request& e)
{
  //assuming validity of the file
  if (current_mode_ != idle)
  {
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Enter idle mode to import"));
    return;
  }
  //fstream does not accept wide strings...
  std::ifstream filein(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(e.name));
  if (!filein)
  {
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Unable to open file"));
    return;
  }
  graph_.clear();
  std::map<unsigned, const model::vertex*> exported_id_to_vert; // exported graph does not necessarily have continuous vertex indices
  unsigned count;
  filein >> count;
  while (count--)
  {
    unsigned index;
    float x, y;
    filein >> index >> x >> y;
    exported_id_to_vert[index] = &graph_.add_vertex("", x, y);
  }
  filein >> count;
  while (count--)
  {
    unsigned from, to;
    int weight;
    filein >> from >> to >> weight;
    graph_.add_edge(*exported_id_to_vert[from], *exported_id_to_vert[to], weight);
  }
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Loaded new graph!"));
}

void visualisation::on_event(const e_export_request& e)
{
  if (current_mode_ != idle)
  {
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Enter idle mode to export"));
    return;
  }
  std::ofstream fileout(std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(e.name));
  if (!fileout)
  {
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Unable to create file"));
    return;
  }
  fileout << graph_.vertices().size() << std::endl;
  for (const auto& v : graph_.vertices())
    fileout << v.index << ' ' << v.loc.x << ' ' << v.loc.y << std::endl;
  fileout << graph_.edges().size() << std::endl;
  for (const auto& e : graph_.edges())
    fileout << e.from.index << ' ' << e.to.index << ' ' << e.weight << ' ' << std::endl;
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Exported the graph!"));
}

void visualisation::on_event(const e_algo_finished& e)
{
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Algorithm finished!"));
  current_mode_ = idle;
}

void visualisation::on_key(int key)
{
  switch (key)
  {
    case GLFW_KEY_DELETE:
      {
        auto verts = graph_helpers::get_selected_vertices(graph_);
        for (const auto& elem : verts)
          graph_.remove_vertex(*elem);
        auto edges = graph_helpers::get_selected_edges(graph_);
        for (const auto& elem : edges)
          graph_.remove_edge(*elem);
      }
      break;
    case GLFW_KEY_V:
      {
        if (current_mode_ == drawing)
        {
          game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Switched to idle mode!"));
          current_mode_ = idle;
        }
        else if (current_mode_ == idle)
        {
          game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Switched to drawing mode!"));
          current_mode_ = drawing;
        }
      }
      break;
    case GLFW_KEY_E:
      if (current_mode_ == drawing)
      {
        auto verts = graph_helpers::get_selected_vertices(graph_);
        for (auto first = verts.begin(); first != verts.end(); ++first)
          for (auto second = std::next(first); second != verts.end(); ++second)
            graph_.add_edge(**first, **second);
      }
      break;
    case GLFW_KEY_A:
      if (current_mode_ == drawing || current_mode_ == idle)
        graph_helpers::unselect_all(graph_);
      break;
    case GLFW_KEY_EQUAL:
    case GLFW_KEY_KP_ADD:
      if (current_mode_ == drawing)
      {
        auto edges = graph_helpers::get_selected_edges(graph_);
        for (const auto& elem : edges)
          ++elem->weight;
      }
      break;
    case GLFW_KEY_KP_SUBTRACT:
    case GLFW_KEY_MINUS:
      if (current_mode_ == drawing)
      {
        auto edges = graph_helpers::get_selected_edges(graph_);
        for (const auto& elem : edges)
          --elem->weight;
      }
      break;
  }
}

void visualisation::on_left_click(float loc_x, float loc_y)
{
  if(current_mode_ == idle)
    graph_helpers::select(graph_, cam_, loc_x, loc_y, 30.0f);
  if (current_mode_ == drawing)
  {
    auto point = cam_.screen_to_world(loc_x, loc_y);
    graph_.add_vertex("", point.x, point.y).is_selected = true;
  }
}
