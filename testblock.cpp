#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

// headers from PA's main.cpp
#include "block.h"
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;


// build a block with no edge cases
TEST_CASE("block::basic build","[weight=1][part=block]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");
    PNG result;
    result.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin,20,150);
    cout << "build passed" <<endl;
    b.greyscale();
    cout << "greyscale passed" <<endl;
    b.render(result,20);
    cout << "render passed" <<endl;

    PNG expected; 
    expected.readFromFile("images/given-blocktest.png");

    REQUIRE(result==expected);
}

// build a block starting from position 0
TEST_CASE("block::grading build front","[weight=1][part=block]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");
    PNG result;
    result.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin,0,150);
    b.render(result,20);

    PNG expected; 
    expected.readFromFile("images/given-blockfront.png");

    REQUIRE(result==expected);
}

// build a block ending at position last
TEST_CASE("block::grading build end","[weight=1][part=block]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");
    PNG result;
    result.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin,pngin.width() - 60 - 1,60);
    b.render(result,20);

    PNG expected; 
    expected.readFromFile("images/given-blockend.png");

    REQUIRE(result==expected);
}

// build a block from the whole image
TEST_CASE("block::grading build all","[weight=1][part=block]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");
    PNG result;
    result.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin,0,pngin.width());
    b.render(result,0);

    REQUIRE(result==pngin);
}
