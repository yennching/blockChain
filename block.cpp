#include "block.h"
#include <vector>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

//Returns the width of the current block
int Block::width() const { 
  return data.size();
}

//Returns the height of the current block.
int Block::height() const{
  return data[0].size();
}

//From im, grabs the vertical strip of pixels whose
//upper left corner is at position (column,0),
//and whose width is width.
void Block::build(PNG & im, int column, int width){
  for(unsigned int x = column; x <(unsigned int) (column + width); x++){
    vector<HSLAPixel> temp;
    for(unsigned int y = 0; y < (unsigned int) im.height(); y++){
      HSLAPixel *pixel = im.getPixel(x, y);
      temp.push_back(*pixel);
    }
    data.push_back(temp);
  }
}

// Draws the current block at position (column,0) in im.
void Block::render(PNG & im, int column) const{
  for (unsigned int x = 0; x < (unsigned int) width(); x++){
    for (unsigned int y = 0; y < (unsigned int) height(); y++){
      //Draws the current block
      HSLAPixel* pixel = im.getPixel((x + column),y);
      *pixel = data[x][y];
    }
  }
}


//Returns the avg saturation value
//of a pixel in the block (eg: 0 for a greyscale image)
double Block::avgSaturation() const{
  double sat = 0;
  for (unsigned int x = 0; x < (unsigned int) width(); x++){
    for (unsigned int y = 0; y < (unsigned int) height(); y++){
      sat += (data[x][y].s);
      //whole thing divided by image width * height 
    }
  }
  return (sat/ (width() * height()));
}


//This function changes the saturation of every pixel in the block to 0,
//which removes the color, leaving grey.
void Block::greyscale(){
  for (unsigned int x = 0; x < (unsigned int) width(); x++){
    for (unsigned int y = 0; y < (unsigned int) height(); y++){
      (data[x][y]).s = 0;
    }
  }
}


