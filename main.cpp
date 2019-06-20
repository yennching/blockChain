/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include "block.h"
#include <iostream>
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

int main() {
    PNG png1,result1;
    png1.readFromFile("images/rosegarden.png");
    result1.readFromFile("images/rosegarden.png");

    //basic block functionality
    Block b;
    b.build(png1,20,150); // grab a strip of png1 starting at 20, and 150p wide.
    b.greyscale(); // change the block to be grey
    b.render(result1,20); //put the ubcified strip onto a new image.
    result1.writeToFile("images/out-blocktest.png");


    PNG expected1; expected1.readFromFile("images/given-blocktest.png");
    if (expected1 == result1) cout<< "block passed" << endl;

//chain
    Chain c(png1,12); // img, number of strips.

    c.moveBack(3,5,4);

    PNG result2 = c.render(12);
    PNG result2r = c.renderBack(12);
    result2.writeToFile("images/out-moveBack.png");
    result2r.writeToFile("images/out-moveBackReverse.png");

    PNG expected2; expected2.readFromFile("images/given-moveBack.png");
    if (expected2 == result2) cout<< "moveBack passed" << endl;
    PNG expected2r; expected2r.readFromFile("images/given-moveBackReverse.png");
    if (expected2r == result2r) cout<< "moveBackReverse passed" << endl;


    Chain d(png1,12);
    d.mirrorSwap(4);
    PNG result3 = d.render(12);
    PNG result3r = d.renderBack(12);
    result3.writeToFile("images/out-mirrorSwap.png");
    result3r.writeToFile("images/out-mirrorSwapReverse.png");

    PNG expected3; expected3.readFromFile("images/given-mirrorSwap.png");
    if (expected3 == result3) cout<< "reverseEasy passed" << endl;
    PNG expected3r; expected3r.readFromFile("images/given-mirrorSwapReverse.png");
    if (expected3r == result3r) cout<< "mirrorSwap reverse passed" << endl;

    Chain e(png1,36);
    Chain g(e); // quick test of copy constructor
    Chain f(result1,36);
    g.weave(f);
    PNG result6 = g.render(64); // deliberately rendering only part
    PNG result8 = g.renderBack(64); // deliberately rendering only back part
    result6.writeToFile("images/out-weaveSameSize64.png");
    result8.writeToFile("images/out-weaveRenderBack64.png");

    PNG expected6; expected6.readFromFile("images/given-weaveSameSize64.png");
    if (expected6 == result6) cout<< "weaveSameSize passed" << endl;
    PNG expected8; expected8.readFromFile("images/given-weaveRenderBack64.png");
    if (expected8 == result8) cout<< "weaveRenderBack passed" << endl;

    return 0;
}
