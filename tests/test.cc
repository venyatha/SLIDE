// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <mylibrary/GameBoard.h>
#include <mylibrary/Tile.h>

#include <mylibrary/ImageProcessor.h>

#include <catch2/catch.hpp>

// Tile
TEST_CASE("Tile Equality") {
  mylibrary::Tile one(0,0,1);
  mylibrary::Tile two(0,0,1);

  SECTION("simple tile equality") {
    REQUIRE(one == two);
  }

  SECTION("same number, one is null tile") {
    mylibrary::Tile another_one(0,0,1, true);
    REQUIRE(!(another_one == two));
  }
}

TEST_CASE("Tile Vector Equality") {
  std::vector<mylibrary::Tile> vec;
  mylibrary::Tile one(0,0,1);
  mylibrary::Tile two(0,0,2);
  vec.push_back(one);
  vec.push_back(two);

  std::vector<mylibrary::Tile> other_vec;
  mylibrary::Tile three(0,0,1);
  mylibrary::Tile four(0,0,2);
  other_vec.push_back(three);
  other_vec.push_back(four);

  SECTION("equal tile vectors") {
    REQUIRE(vec == other_vec);
  }

  SECTION("different size vectors") {
    vec.push_back(mylibrary::Tile(1,1,1));
    REQUIRE(vec != other_vec);
  }

  SECTION("different num values") {
    vec.push_back(mylibrary::Tile(1,1,1));
    vec.push_back(mylibrary::Tile(1,1,2));
    REQUIRE(vec != other_vec);
  }

  SECTION("different null tile values") {
    vec.push_back(mylibrary::Tile(3,3,4,true));
    other_vec.push_back(mylibrary::Tile(3,3,4,false));
    REQUIRE(vec != other_vec);
  }
}


// GameBoard
TEST_CASE("GameBoard Constructor") {
  SECTION("size 3") {
    mylibrary::GameBoard g(3);
    REQUIRE(g.GetGrid()[1][0] == mylibrary::Tile(0,0,2));
    REQUIRE(g.GetGrid()[2][2].GetNullTile());
    REQUIRE(g.GetSize() == 3);
  }

  SECTION("size 6") {
    mylibrary::GameBoard g(6);
    REQUIRE(g.GetGrid()[0][5] == mylibrary::Tile(0,0,31));
    REQUIRE(g.GetGrid()[5][5].GetNullTile());
    REQUIRE(g.GetSize() == 6);
  }
}

TEST_CASE("Outstream Operator") {
  mylibrary::GameBoard g(3);

  SECTION("just initialized") {
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "456\n"
                        "78 \n");
  }

  SECTION("moved one tile") {
    g.MoveTile(2,1,mylibrary::Direction::kDown);
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "45 \n"
                        "786\n");

  }
}

TEST_CASE("Move Tile") {
  mylibrary::GameBoard g(3);
  g.MoveTile(2,1,mylibrary::Direction::kDown);

  SECTION("successful move down") {

    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "45 \n"
                        "786\n");
    REQUIRE(g.GetGrid()[2][1].GetNullTile());
    // check that inherent x and y values stay the same
    REQUIRE(g.GetGrid()[2][2].GetX() == 2);
    REQUIRE(g.GetGrid()[2][1].GetY() == 2);
  }

  g.MoveTile(2,2,mylibrary::Direction::kUp);
  SECTION("successful move up") {
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "456\n"
                        "78 \n");
  }

  g.MoveTile(1,2,mylibrary::Direction::kRight);
  SECTION("successful move right") {
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "456\n"
                        "7 8\n");
  }

  g.MoveTile(2,2,mylibrary::Direction::kRight);
  SECTION("successful move left") {
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "456\n"
                        "78 \n");
  }

  SECTION("failed move") {
    g.MoveTile(0,0,mylibrary::Direction::kDown);
    std::ostringstream os;
    os << g;
    REQUIRE(os.str() == "123\n"
                        "456\n"
                        "78 \n");
  }
}


TEST_CASE("Check Win") {
  mylibrary::GameBoard g(3);

  SECTION("just initialized") {
    REQUIRE(g.CheckWin());
  }
  SECTION("move one") {
    g.MoveTile(2,1,mylibrary::Direction::kDown);
    REQUIRE(!g.CheckWin());
  }
}

TEST_CASE("is solvable") {
  mylibrary::GameBoard g(3);

  SECTION("just initialized") {
    REQUIRE(g.IsSolvable());
  }

  SECTION("move two") {
    g.MoveTile(1,2,mylibrary::Direction::kRight);
    g.MoveTile(1,1,mylibrary::Direction::kDown);
    REQUIRE(g.IsSolvable());
  }

  mylibrary::GameBoard gb(4);
  SECTION("even sized board") {
    gb.MoveTile(2,3,mylibrary::Direction::kRight);
    gb.MoveTile(2,2,mylibrary::Direction::kDown);
    REQUIRE(gb.IsSolvable());
  }
}

TEST_CASE("shuffle board") {
  mylibrary::GameBoard g(3);
  g.ShuffleBoard();
  std::ostringstream os;
  os << g;

  SECTION("size 3") {
    REQUIRE(os.str() != "123\n456\n789\n");
    REQUIRE(g.IsSolvable());
  }

  SECTION("shuffle twice") {
    g.ShuffleBoard();
    std::ostringstream os2;
    os2 << g;
    REQUIRE(os.str() != os2.str());
    REQUIRE(g.IsSolvable());
  }

  SECTION("two different boards") {
    mylibrary::GameBoard b(3);
    b.ShuffleBoard();
    std::ostringstream os2;
    os2 << b;
    REQUIRE(os.str() != os2.str());
    REQUIRE(b.IsSolvable());
  }

  SECTION("size 4") {
    mylibrary::GameBoard b(4);
    b.ShuffleBoard();
    std::ostringstream os2;
    os2 << b;
    REQUIRE(os2.str() != "1234\n5678\n9101112\n131415 ");
    REQUIRE(b.IsSolvable());
  }
}

// Image
TEST_CASE("Check Valid File") {
  SECTION("Invalid path") {
    std::string path= "v1/Desktop/cinder_0.9.2_mac/my-projects/final-project-vmanne3/tests/assets/test.jpg";
    REQUIRE(mylibrary::CheckValidFile(path, 267, 200) == "please input a valid filepath\n");
  }
}