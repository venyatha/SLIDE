//
// Created by Venyatha MANNE on 4/25/20.
//

#include "mylibrary/Tile.h"

namespace mylibrary {

Tile::Tile(int num, bool b) {
  num_ = num;
  null_tile_ = b;
}

Tile::Tile(int num) {
  num_ = num;
  null_tile_ = false;
}

bool Tile::operator==(const Tile& rhs) const {
  if (num_ == rhs.num_ && null_tile_ == rhs.null_tile_) {
    return true;
  }
}

}  // namespace mylibrary
