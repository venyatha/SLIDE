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

TEST_CASE("Tile equality") {
  mylibrary::Tile one(0,0,1);
  mylibrary::Tile two(0,0,1);

  REQUIRE(one == two);
}
TEST_CASE("Tile Vector equality") {
  mylibrary::Tile one(0,0,1);
  mylibrary::Tile two(0,0,2);

  std::vector<mylibrary::Tile> vec;
  vec.push_back(one);
  vec.push_back(two);

  mylibrary::Tile three(0,0,1);
  mylibrary::Tile four(0,0,2);

  std::vector<mylibrary::Tile> other_vec;
  other_vec.push_back(three);
  other_vec.push_back(four);

  REQUIRE(vec == other_vec);
}

TEST_CASE("constructor") {
  mylibrary::GameBoard g(3);
  mylibrary::Tile two(0,0,2);
  REQUIRE(g.grid_[1][0] == two);
  REQUIRE(g.grid_[2][2].null_tile_);
}

TEST_CASE("Move Tile") {
  SECTION("move down") {
    mylibrary::GameBoard g(3);
    g.MoveTile(2,1,mylibrary::Direction::kDown);
    mylibrary::Tile tile(2,2,6);
    REQUIRE(g.grid_[2][2] == tile);
    REQUIRE(g.grid_[2][2].x == tile.x);
    REQUIRE(g.grid_[2][1].y == tile.y);
  }
}

TEST_CASE("outstream operator") {
  mylibrary::GameBoard g(3);
  std::ostringstream os;
  os << g;
  REQUIRE(os.str() == "123\n456\n789\n");
}

TEST_CASE("check win") {
  SECTION("just init") {
    mylibrary::GameBoard g(3);
    REQUIRE(g.CheckWin());
  }
  SECTION("move one") {
    mylibrary::GameBoard g(3);
    g.MoveTile(2,1,mylibrary::Direction::kDown);
    REQUIRE(!g.CheckWin());
  }
}

TEST_CASE("shuffle") {
  mylibrary::GameBoard g(3);
  g.Shuffle();
  std::ostringstream os;
  os << g;
  REQUIRE(os.str() != "123\n456\n789\n");
}

TEST_CASE("shuffle board") {
  mylibrary::GameBoard g(3);
  g.ShuffleGameBoard();
  std::ostringstream os;
  os << g;

  mylibrary::GameBoard b(3);
  b.ShuffleGameBoard();
  std::ostringstream os2;
  os2 << b;

  REQUIRE(os.str() != os2.str());
  REQUIRE(g.isSolvable());
  REQUIRE(b.isSolvable());
}



/*
TEST_CASE("is solvable") {
  mylibrary::GameBoard g(3);
  g.ShuffleGameBoard();
  REQUIRE(g.isSolvable());
}
 */