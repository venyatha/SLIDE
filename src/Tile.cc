//
// Created by Venyatha MANNE on 4/25/20.
//

#include "mylibrary/Tile.h"

namespace mylibrary {

Tile::Tile(int x_val, int y_val, int num, bool b) {
  num_ = num;
  null_tile_ = b;
  x = x_val;
  y = y_val;
}

Tile::Tile(int x_val, int y_val, int num) {
  num_ = num;
  null_tile_ = false;
  x = x_val;
  y = y_val;
}

bool Tile::operator==(const Tile& rhs) const {
  if (num_ == rhs.num_ && null_tile_ == rhs.null_tile_) {
    return true;
  }
}

}  // namespace mylibrary
