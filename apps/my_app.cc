// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/GeomIo.h>
#include <cinder/app/App.h>
#include <mylibrary/ImageReader.h>
#include <pretzel/PretzelGui.h>

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() :game_board_(3) {};

void MyApp::setup() {
  auto img = loadImage( loadAsset( "colourwheel.jpeg" ) );
  mTexture = cinder::gl::Texture::create( img );
  //mylibrary::GridAreas("string");

  mRadius = 25;
  gui = pretzel::PretzelGui::create("Puzzle settings");
  gui->setSize(cinder::vec2(10,10));
  gui->setPos(cinder::vec2(1000,10));

  gui->addSlider("Puzzle Size", &mRadius, 2, 100);


  gui->addSaveLoad();
  gui->loadSettings();    // load the last saved settings automatically



  //ci::gl::enableAlphaBlending();
}

void MyApp::update() {

}

void MyApp::draw() {
  cinder::gl::setMatricesWindow( getWindowSize() );

  cinder::gl::clear(cinder::Color::white());
  //DrawBoard();
  gui->drawAll();
  cinder::gl::translate(-360,-250);
  DrawBoard();

  /*
  cinder::gl::setMatricesWindow( getWindowSize() );
  cinder::Rectf drawRect( 0, 0, getWindowWidth(),
                          getWindowHeight());
  cinder::gl::draw(mTexture, drawRect);
  cinder::gl::color( cinder::Color( 1, 0, 0 ) );
  cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);
     cinder::gl::enableAlphaBlending();

   */

}

void MyApp::DrawBoard() {

  //cinder::gl::translate( getWindowCenter().x, 75 );
  ;
  cinder::gl::translate( getWindowCenter().x, getWindowCenter().y);
  cinder::gl::translate(-200,-100);


  for (int i = 0; i < 3; i++) {
    //cinder::gl::translate( getWindowCenter().x, getWindowCenter().y);
    //cinder::gl::translate(-200,-100);
    for (int j = 0; j < 3; j++) {

      cinder::gl::color( cinder::Color( 0, 1, 0 ) );
      cinder::Rectf rect(0,
                         0,
                         300,
                         200);
      cinder::gl::drawStrokedRect(rect);

      /*
      cinder::gl::color(cinder::Color::black());
      auto box = cinder::TextBox()
          .alignment(cinder::TextBox::CENTER)
          .font(cinder::Font("Arial", 30))
          .color(cinder::Color::black())
          .backgroundColor(cinder::ColorA(0, 0, 0, 0))
          .text("1");

      const cinder::vec2 locp = {0,0};
      const auto surface = box.render();
      const auto texture = cinder::gl::Texture::create(surface);
      cinder::gl::draw(texture, locp);
      */

      cinder::gl::translate(300,0);
    }
    cinder::gl::translate(-900,200);
  }

  /*
  cinder::gl::color( cinder::Color( 0, 1, 0 ) );
  cinder::Rectf rect(0,
                     0,
                     300,
                     200);
  cinder::gl::drawStrokedRect(rect);

   */

  /*
  double col = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cinder::gl::translate((getWindowWidth()/4)*j, (getWindowHeight()/4)*i);
      cinder::gl::color( cinder::Color( 0, col, 0 ) );
      cinder::Rectf rect(0,
                         0,
                         300,
                         200);
      cinder::gl::drawStrokedRect(rect);
      col+= 0.1;
*/

      //cinder::Rectf rect(getWindowWidth()*j, getWindowHeight()*i, getWindowWidth()*(j+1), getWindowHeight()*(i+1));
      //cinder::gl::color( cinder::Color(1,0,0))
      //cinder::gl::draw(rect);
    //}
  //}

}

void MyApp::keyDown(KeyEvent event) {
  if (event.getChar() == 'g'){
    gui->toggleVisible();	// gui interaction will be disabled when invisible
  }

}

void MyApp::onButtonPress() {}

}  // namespace myapp
