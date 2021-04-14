#include <kruskal.hpp>
#include <algorithm>

kruskal::kruskal(const model::graph& graph, event_sink<game_event_dispatcher>& game_event_sink)
  : graph_algorithm(graph),
    game_event_sink_(game_event_sink)
{
  for (const auto& v : graph_.vertices())
    subset_representants_[&v] = &v;
  for(const auto& elem : graph.edges())
    edges_in_order_.push(&elem);
}

void kruskal::step()
{
  if (edges_in_order_.empty())
  {
    game_event_sink_.add_event(std::make_unique<e_algo_finished>());
    return;
  }
  auto top = edges_in_order_.top();
  edges_in_order_.pop();
  std::wstring msg(L"Checking edge from " + std::to_wstring(top->from.index) + L" to " +
                   std::to_wstring(top->to.index) + L" weight " + std::to_wstring(top->weight));
  game_event_sink_.add_event(std::make_unique<e_log_msg>(msg));
  if (subset_representants_[&top->to] == subset_representants_[&top->from])
  {
    top->color = { 0.05f, 0.05f, 0.05f };
    game_event_sink_.add_event(std::make_unique<e_log_msg>(L"They belong to the same subtree, skipping"));
    return;
  }
  top->color = { 0.8f, 0.95f, 0.7f };
  game_event_sink_.add_event(std::make_unique<e_log_msg>(L"Adding the edge to the resulting tree"));
  auto* from = subset_representants_[&top->from];
  auto* to = subset_representants_[&top->to];
  from->color = { 0.2f, 0.8f, 0.9f };
  to->color = { 0.2f, 0.8f, 0.9f };
  for (auto& kv_pair : subset_representants_)
  {
    if (kv_pair.second == from)
      kv_pair.second = to;
  }
}
