#pragma once

#include <application.hpp>
#include <game_event_dispatcher.hpp>
#include <gui_event_dispatcher.hpp>
#include <graph_algorithm.hpp>
#include <camera.hpp>

class visualisation
  : public application,
    public event_handler<e_button_pressed>,
    public event_handler<e_play_request>,
    public event_handler<e_import_request>,
    public event_handler<e_export_request>,
    public event_handler<e_algo_finished>
{
    enum mode
    {
      idle,
      drawing,
      algorithm_running,
      algorithm_stepping
    };

    const camera& cam_;
    event_sink<game_event_dispatcher>& game_event_sink_;
    std::unique_ptr<graph_algorithm> current_algo_;
    mode current_mode_;

  public:

    visualisation(model::graph& graph, const camera& cam, game_event_dispatcher& game_dispatcher, gui_event_dispatcher& gui_dispatcher);

    virtual void update(float elapsed_time) override;
    virtual void on_event(const e_button_pressed& e) override;
    virtual void on_event(const e_play_request& e) override;
    virtual void on_event(const e_import_request& e) override;
    virtual void on_event(const e_export_request& e) override;
    virtual void on_event(const e_algo_finished& e) override;
    virtual void on_key(int key) override;
    virtual void on_left_click(float loc_x, float loc_y) override;
};
