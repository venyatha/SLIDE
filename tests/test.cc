// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/GameBoard.h>

#include <catch2/catch.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

/*
TEST_CASE("constructor") {
  mylibrary::GameBoard g(3);
  REQUIRE(g.grid_[0][0] == 1);
  REQUIRE(g.grid_[1][0] == 2);
  REQUIRE(g.grid_[2][2] == 9);
}

TEST_CASE("move up") {
  mylibrary::GameBoard g(3);
  g.MoveUp(5);
  REQUIRE(g.grid_[1][0] == 5);
  REQUIRE(g.grid_[1][1] == 2);

}

TEST_CASE("illegal move up") {
  mylibrary::GameBoard g(3);
  g.MoveUp(2);
  REQUIRE(g.grid_[1][0] == 2);
  REQUIRE(g.grid_[1][1] == 5);

}
 */

TEST_CASE("Tile equality") {
  mylibrary::Tile one(1);
  mylibrary::Tile two(1);

  REQUIRE(one == two);
}
TEST_CASE("Tile Vector equality") {
  mylibrary::Tile one(1);
  mylibrary::Tile two(2);

  std::vector<mylibrary::Tile> vec;
  vec.push_back(one);
  vec.push_back(two);

  mylibrary::Tile three(1);
  mylibrary::Tile four(2);

  std::vector<mylibrary::Tile> other_vec;
  other_vec.push_back(three);
  other_vec.push_back(four);

  REQUIRE(vec == other_vec);
}
