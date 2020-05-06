//
// Created by Venyatha MANNE on 4/25/20.
//

#include "mylibrary/ImageProcessor.h"

#include <mylibrary/GameBoard.h>

#include <string>

#include "cinder/gl/Texture.h"

namespace mylibrary {
cinder::gl::Texture2dRef MakeTexture(cinder::Surface& surface, int x, int y, int tile_width, int tile_height) {
  // hard-coded to the size of a tile in a 3x3 grid
  cinder::Surface new_surface(tile_width,tile_height,false);

  // set every pixel in new_surface to the color of the corresponding pixel in surface
  for (int i = 0; i < tile_width; i++) {
    for (int j = 0; j < tile_height; j++) {
      auto color = surface.getPixel(ci::ivec2(i+x,j+y));
      new_surface.setPixel(ci::ivec2(i,j), color);
    }
  }
  return ci::gl::Texture2d::create(new_surface);
}

std::string CheckValidFile(std::string file_path, int tile_width, int tile_height) {
  if (std::ifstream(file_path).fail()) {
    return "please input a valid filepath\n";
  // if width too small
  } else if (ci::loadImage(file_path)->getWidth() < tile_width) {
    std::stringstream ss;
    ss << "please pick an image that has a width greater than " << tile_width << " pixels\n";
    return ss.str();
  // if height too small
  } else if (ci::loadImage(file_path)->getWidth() < tile_height) {
    std::stringstream ss;
    ss << "please pick an image that has a height greater than " << tile_height << " pixels\n";
    return ss.str();
  } else {
    // valid file
    return " ";
  }
}

std::vector<cinder::gl::Texture2dRef> MakeTextureVec(std::string filepath, int tile_width, int tile_height) {
  ci::Surface surface;
  if (CheckValidFile(filepath, tile_width, tile_height) != " ") {
    std::cerr << CheckValidFile(filepath, tile_width, tile_height);
  }
  surface = ci::Surface(cinder::loadImage(filepath));
  std::vector<ci::gl::Texture2dRef> toReturn;

  // makes textures for the 9 tiles in a 3x3 game
  for (int y = 0; y < (tile_height*3); y = y + tile_height) {
    for (int x = 0; x < (tile_width*3); x = x + tile_width) {
      toReturn.push_back(MakeTexture(surface, x, y, tile_width, tile_height));
    }
  }
  return toReturn;
}
}  // namespace mylibrary