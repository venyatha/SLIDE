//
// Created by Venyatha MANNE on 4/25/20.
//

#include "mylibrary/Image.h"
#include <mylibrary/GameBoard.h>
#include "cinder/gl/Texture.h"
#include <string>

namespace mylibrary {
cinder::gl::Texture2dRef MakeTexture(cinder::Surface& surface, int x, int y) {
  // hard-coded to the size of a tile in a 3x3 grid
  cinder::Surface new_surface(tile_width_,tile_height_,false);

  // set every pixel in new_surface to the color of the corresponding pixel in surface
  for (int i = 0; i < tile_width_; i++) {
    for (int j = 0; j < tile_height_; j++) {
      auto color = surface.getPixel(ci::ivec2(i+x,j+y));
      new_surface.setPixel(ci::ivec2(i,j), color);
    }
  }
  return ci::gl::Texture2d::create(new_surface);
}

std::string CheckValidFile(std::string file_path) {
  if (std::ifstream(file_path).fail()) {
    return "please input a valid filepath\n";
  // if width too small
  } else if (ci::loadImage(file_path)->getWidth() < tile_width_) {
    return "please pick an image that has a width greater than 267 pixels\n";
  // if height too small
  } else if (ci::loadImage(file_path)->getWidth() < tile_height_) {
    return "please pick an image that has a height greater than 200 pixels\n";
  } else {
    // valid file
    return " ";
  }
}

std::vector<cinder::gl::Texture2dRef> MakeTextureVec(std::string filepath) {
  ci::Surface surface;
  if (CheckValidFile(filepath) != " ") {
    std::cerr << CheckValidFile(filepath);
  }
  surface = ci::Surface(cinder::loadImage(filepath));
  std::vector<ci::gl::Texture2dRef> toReturn;

  // makes textures for the 9 tiles in a 3x3 game
  for (int y = 0; y < (tile_height_*3); y = y + tile_height_) {
    for (int x = 0; x < (tile_width_*3); x = x + tile_width_) {
      toReturn.push_back(MakeTexture(surface, x, y));
    }
  }
  return toReturn;
}
}  // namespace mylibrary