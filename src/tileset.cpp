#include <tileset.hpp>

tileset::tileset(const std::string tileset_name, unsigned row_count)
  : tile_tex_(tileset_name),
    row_count_(row_count)
{
}

const texture& tileset::get_tile_tex() const
{
  return tile_tex_;
}

unsigned tileset::get_row_count() const
{
  return row_count_;
}
