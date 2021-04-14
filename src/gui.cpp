#include <gui.hpp>
#include <button.hpp>
#include <log_window.hpp>
#include <textfield.hpp>
#include <algorithm>
#include <floating_element.hpp>
#include <GLFW/glfw3.h>
#include <query_box.hpp>

gui::gui(gui_event_dispatcher& gui_dispatcher, game_event_dispatcher& g_events)
  : gui_sink_(gui_dispatcher),
    event_handler<e_widget_request_suicide>(gui_dispatcher)
{
  //algorithm selection widget
  auto algo_selection_text = std::make_shared<textfield>(glm::vec2(300, 50), glm::vec2(300, 40), false);
  widgets_.push_front(algo_selection_text);

  //play button, sending play request on click
  widgets_.push_front(std::make_shared<button>(glm::vec2(50, 50), glm::vec2(40, 40), L"play", [algo_selection_text, &gui_dispatcher]()
  {
    gui_dispatcher.add_event(std::make_unique<e_play_request>(algo_selection_text->get_text()));
  }));

  //pause, step, exit, refresh buttons with default behavior
  widgets_.push_front(std::make_shared<button>(glm::vec2(100, 50), glm::vec2(40, 40), L"pause", gui_sink_));
  widgets_.push_front(std::make_shared<button>(glm::vec2(150, 50), glm::vec2(40, 40), L"step", gui_sink_));
  widgets_.push_front(std::make_shared<button>(glm::vec2(200, 50), glm::vec2(40, 40), L"exit", gui_sink_));
  widgets_.push_front(std::make_shared<button>(glm::vec2(660, 50), glm::vec2(40, 40), L"refresh", gui_sink_));

  //export and import which on click spawn query box
  widgets_.push_front(std::make_shared<button>(glm::vec2(710, 50), glm::vec2(40, 40), L"export", [this]()
  {
    auto floating_input_box = std::make_shared<floating_element<query_box>>(gui_sink_, glm::vec2(710, 100), [this](const std::wstring & str)
    {
      gui_sink_.add_event(std::make_unique<e_export_request>(str));
    });
    widgets_.push_front(floating_input_box);
  }));
  widgets_.push_front(std::make_shared<button>(glm::vec2(760, 50), glm::vec2(40, 40), L"import", [this]()
  {
    auto floating_input_box = std::make_shared<floating_element<query_box>>(gui_sink_, glm::vec2(760, 100), [this](const std::wstring & str)
    {
      gui_sink_.add_event(std::make_unique<e_import_request>(str));
    });
    widgets_.push_front(floating_input_box);
  }));

  //vector of strings to be shared between left and right button
  auto shared_stringvec = std::make_shared<std::vector<std::wstring>>(std::vector<std::wstring>({ L"BFS", L"DFS", L"Dijkstra", L"Kruskal", L"Biparite" }));

  //log window
  widgets_.push_front(std::make_shared<log_window>(glm::vec2(50, 400), glm::vec2(250, 400), g_events));

  //left and right buttons which rotate the shared string vector on click
  widgets_.push_front(std::make_shared<button>(glm::vec2(250, 50), glm::vec2(40, 40), L"left", [algo_selection_text, shared_stringvec]()
  {
    auto& v = *shared_stringvec;
    std::rotate(v.begin(), v.begin() + 1, v.end());
    algo_selection_text->set_text(v.front());
  }));
  widgets_.push_front(std::make_shared<button>(glm::vec2(610, 50), glm::vec2(40, 40), L"right", [algo_selection_text, shared_stringvec]()
  {
    auto& v = *shared_stringvec;
    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
    algo_selection_text->set_text(v.front());
  }));
  algo_selection_text->set_text(shared_stringvec->front());
}

void gui::render(gui_brush& brush) const
{
  for (auto& w : widgets_)
    w->draw(brush);
}

bool gui::on_click(const e_mouse_clicked& e)
{
  if (widgets_.empty())
    return false;
  auto& x = e.xpos;
  auto& y = e.ypos;
  auto& front = widgets_.front();
  //if the front widget takes input, we pass it
  if (front->loc().x < x &&
      front->loc().x + front->size().x > x &&
      front->loc().y < y &&
      front->loc().y + front->size().y > y)
  {
    bool handled = front->on_click(x, y, e.action == GLFW_PRESS);
    if (handled)
      return true;
  }
  //he is not interested, so maybe someone deeper is?
  for (auto iter = ++widgets_.begin(); iter != widgets_.end(); ++iter)
  {
    auto& w = *iter;
    if (w->loc().x < x &&
        w->loc().x + w->size().x > x &&
        w->loc().y < y &&
        w->loc().y + w->size().y > y)
    {
      bool handled = w->on_click(x, y, e.action == GLFW_PRESS);
      if (handled)
      {
        for (auto& elem : widgets_)
          elem->on_focus_changed(w.get());
        auto new_front_widget = w;
        widgets_.erase(iter);
        widgets_.push_front(new_front_widget);
        return true;
      }
    }
  }
  for (auto& elem : widgets_)
    elem->on_focus_changed(nullptr);
  return false;
}

bool gui::on_key(const e_keypress& e) const
{
  if (e.action != GLFW_PRESS)
    return true;
  if (widgets_.empty())
    return false;
  return widgets_.front()->on_key(e.key);
}

void gui::on_unicode(const e_unicode_keypress& e) const
{
  if (widgets_.empty())
    return;
  widgets_.front()->on_unicode(e.codepoint);
}

void gui::on_event(const e_widget_request_suicide& e)
{
  auto iter = std::find_if(widgets_.begin(), widgets_.end(), [&e](const std::shared_ptr<widget>& w)
  {
    return e.me == w.get();
  });
  if (iter != widgets_.end())
    widgets_.erase(iter);
}
