#pragma once

#include <texture.hpp>

class tileset
{

    texture tile_tex_;
    const unsigned row_count_;

  public:

    tileset(const std::string tileset_name, unsigned row_count);
    const texture& get_tile_tex() const;
    unsigned get_row_count() const;
};