// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/GeomIo.h>
#include <cinder/app/App.h>
#include <mylibrary/ImageReader.h>
#include <pretzel/PretzelGui.h>

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  auto img = loadImage( loadAsset( "colourwheel.jpeg" ) );
  mTexture = cinder::gl::Texture::create( img );
  mylibrary::GridAreas("string");

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
  cinder::gl::clear(cinder::Color::white());

  cinder::gl::setMatricesWindow( getWindowSize() );
  cinder::Rectf drawRect( 0, 0, getWindowWidth(),
                  getWindowHeight());

  //cinder::Area area(drawRect);
  //area.clipBy(cinder::Area(0, 0, 213, 400));
  //0,640
  //0,400
  //cinder::Area a = mylibrary::GridAreas("string");
  //mTexture->setCleanBounds(cinder::Area(0, 0, mTexture->getWidth()/3, mTexture->getHeight()/3));


  //cinder::Area area(mTexture);
  //getAreaTexCoords (area);

  cinder::gl::draw(mTexture, drawRect);

  //cinder::gl::draw( mTexture, drawRect);
  cinder::gl::color( cinder::Color( 1, 0, 0 ) );
  cinder::gl::drawSolidCircle(cinder::vec2(getWindowCenter()), mRadius);
  gui->drawAll();

}

void MyApp::keyDown(KeyEvent event) {
  if (event.getChar() == 'g'){
    gui->toggleVisible();	// gui interaction will be disabled when invisible
  }

}

void MyApp::onButtonPress() {}

}  // namespace myapp
