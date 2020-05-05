//
// Created by Venyatha MANNE on 4/25/20.
//

#ifndef FINALPROJECT_IMAGEPROCESSOR_H
#define FINALPROJECT_IMAGEPROCESSOR_H

#include <cinder/Surface.h>
#include <cinder/gl/Context.h>
#include <string>

namespace mylibrary {
  // checks validity of image provided by the user
  std::string CheckValidFile(std::string file_path);
  // returns vector of textures cropped to the size of a tile in a 3x3 game
  std::vector<cinder::gl::Texture2dRef> MakeTextureVec(std::string filepath);
  const int tile_width_ = 267;
  const int tile_height_ = 200;

}  // namespace mylibrary

#endif  // FINALPROJECT_IMAGEPROCESSOR_H
