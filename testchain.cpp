#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

// headers from PA's main.cpp
#include "chain.h"
#include "block.h"
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

TEST_CASE("chain::basic mirrorSwap forward", "[weight=1][part=chain]"){
    PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.mirrorSwap(4);
    PNG result = c.render(12);

    PNG expected;
    expected.readFromFile("images/given-mirrorswap.png");

    REQUIRE(result==expected);

}

TEST_CASE("chain::basic mirrorSwap reverse", "[weight=1][part=chain]"){
    PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.mirrorSwap(4);
    PNG result = c.renderBack(12);

    PNG expected;
    expected.readFromFile("images/given-mirrorswap.png");

    REQUIRE(result==expected);

}

TEST_CASE("chain::basic lazyFilter forward", "[weight=1][part=chain]"){
    PNG pngin;
    pngin.readFromFile("images/given-weaveSameSize.png");

    Chain c(pngin,25);
    c.lazyFilter(0.4);
    PNG result = c.render(c.size());
    //result.writeToFile("images/given-lazyFilter.png");

    PNG expected;
    expected.readFromFile("images/given-lazyFilter.png");

    REQUIRE(result==expected);

}

TEST_CASE("chain::basic lazyFilter reverse", "[weight=1][part=chain]"){
    PNG pngin;
    pngin.readFromFile("images/given-weaveSameSize.png");

    Chain c(pngin,25);
    c.lazyFilter(0.4);
    PNG result = c.renderBack(c.size());

    PNG expected;
    expected.readFromFile("images/given-lazyFilter.png");

    REQUIRE(result==expected);
}

// test moveBack function with no boundary cases
TEST_CASE("chain::basic moveBack forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,5,4);
    PNG result = c.render(12);

    PNG expected; 
    expected.readFromFile("images/given-moveBack.png");

    REQUIRE(result==expected);
}

// test moveBack function rendered in reverse with no boundary cases
TEST_CASE("chain::basic moveBack reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,5,4);
    PNG result = c.renderBack(12);

    PNG expected; 
    expected.readFromFile("images/given-moveBack.png");

    REQUIRE(result==expected);
}

// test weave function with no boundaries and same size Chains
// bad test... assumes block test passed.
TEST_CASE("chain::basic weave","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    PNG pngin2(pngin1);
    //pngin2.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin1,20,150);
    b.greyscale();
    b.render(pngin2,20);

    Chain c(pngin1,12);
    Chain d(pngin2,12);
    c.weave(d);

    PNG result = c.render(18);

    PNG expected; 
    expected.readFromFile("images/given-weaveSameSize.png");

    REQUIRE(result==expected);
}

// test weave function with no boundaries and same size Chains in reverse
// bad test... assumes block test passed.
TEST_CASE("chain::basic weave reverse","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    PNG pngin2;
    pngin2.readFromFile("images/rosegarden.png");
    
    Block b;
    b.build(pngin1,20,150);
    b.greyscale();
    b.render(pngin2,20);

    Chain c(pngin1,12);
    Chain d(pngin2,12);
    c.weave(d);

    PNG result = c.renderBack(18);

    PNG expected; 
    expected.readFromFile("images/given-weaveRenderBack.png");
    //result.writeToFile("images/given-weaveRenderBack.png");

    REQUIRE(result==expected);
}

// chain copy constructor
TEST_CASE("chain::basic copy constructor","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,18);
    Chain d(c);

    PNG result = d.render(18);

    REQUIRE(result==pngin);
}

// chain copy constructor reverse
TEST_CASE("chain::basic copy constructor reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,18);
    Chain d(c);

    PNG result = d.renderBack(18);

    REQUIRE(result==pngin);
}

// test moveBack function 3, 10, 0
TEST_CASE("chain::grading moveBack 3, 10, 0, forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,10,0);
    PNG result = c.render(12);

    REQUIRE(result==pngin);
}

// test moveBack function 3, 10, 0
TEST_CASE("chain::grading moveBack 3, 10, 0, reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(3,10,0);
    PNG result = c.renderBack(12);

    REQUIRE(result==pngin);
}

// test moveBack function 1, 10, 2
TEST_CASE("chain::grading moveBack 1, 10, 2, forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,10,2);
    PNG result = c.render(12);

    PNG expected; 
    expected.readFromFile("images/given-move1102.png");

    REQUIRE(result==expected);
}

// test moveBack function 1, 10, 2
TEST_CASE("chain::grading moveBack 1, 10, 2, reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,10,2);
    PNG result = c.renderBack(12);

    PNG expected; 
    expected.readFromFile("images/given-move1102.png");

    REQUIRE(result==expected);
}

// test moveBack function 1, 12, 0
TEST_CASE("chain::grading moveBack 1, 12, 0, forward","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,12,0);
    PNG result = c.render(12);

    REQUIRE(result==pngin);
}

// test moveBack function 1, 10, 2
TEST_CASE("chain::grading moveBack 1, 12, 0, reverse","[weight=1][part=chain]"){

	PNG pngin;
    pngin.readFromFile("images/rosegarden.png");

    Chain c(pngin,12);
    c.moveBack(1,12,0);
    PNG result = c.renderBack(12);

    REQUIRE(result==pngin);
}

// test weave function with shorter first forward
TEST_CASE("chain::grading weave shorter first forward","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    
    Chain c(pngin1,18);

    PNG pngin2 = c.render(9);
    Chain d(pngin2,9);
    
    d.weave(c);

    PNG result = d.render(27);

    PNG expected; 
    expected.readFromFile("images/given-weaveShorterFirst.png");

    REQUIRE(result==expected);
}

// test weave function with shorter first back
TEST_CASE("chain::grading weave shorter first reverse","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");

    Chain c(pngin1,18);

    PNG pngin2 = c.render(9);
    Chain d(pngin2,9);

    d.weave(c);

    PNG result = d.renderBack(27);

    PNG expected; 
    expected.readFromFile("images/given-weaveShorterFirst.png");

    REQUIRE(result==expected);
}

// test weave function with longer first forward
TEST_CASE("chain::grading weave longer first forward","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");
    
    Chain c(pngin1,18);

    PNG pngin2 = c.render(9);
    Chain d(pngin2,9);
    
    c.weave(d);

    PNG result = c.render(27);

    PNG expected; 
    expected.readFromFile("images/given-weaveLongerFirst.png");

    REQUIRE(result==expected);
}

// test weave function with longer first back
TEST_CASE("chain::grading weave longer first reverse","[weight=1][part=chain]"){

	PNG pngin1;
    pngin1.readFromFile("images/rosegarden.png");

    Chain c(pngin1,18);

    PNG pngin2 = c.render(9);
    Chain d(pngin2,9);

    c.weave(d);

    PNG result = c.renderBack(27);

    PNG expected; 
    expected.readFromFile("images/given-weaveLongerFirst.png");

    REQUIRE(result==expected);
}

