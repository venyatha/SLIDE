// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/ImageReader.h>

#include <catch2/catch.hpp>

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

TEST_CASE("constructor") {
  mylibrary::GameBoard g(3);
  REQUIRE(g.grid_[0][0] == 0);
  REQUIRE(g.grid_[1][0] == 1);
  REQUIRE(g.grid_[2][2] == 9);
}