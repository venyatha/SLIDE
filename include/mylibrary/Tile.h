//
// Created by Venyatha MANNE on 4/25/20.
//

#ifndef FINALPROJECT_TILE_H
#define FINALPROJECT_TILE_H

namespace mylibrary {
class Tile {
 public:

  int num_;
  bool null_tile_;

  Tile(int num, bool b);
  explicit Tile(int num);

  bool operator==(const Tile& rhs) const;
};

}  // namespace mylibrary


#endif  // FINALPROJECT_TILE_H
