TESTBLOCK = testblock
TESTCHAIN = testchain
OBJSCHAIN = testchain.o PNG.o HSLAPixel.o lodepng.o chain.o block.o 
OBJSBLOCK = testblock.o PNG.o HSLAPixel.o lodepng.o block.o 

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lpthread -lm

all : $(TESTBLOCK) $(TESTCHAIN)

$(TESTBLOCK) : $(OBJSBLOCK)
	$(LD) $(OBJSBLOCK) $(LDFLAGS) -o $(TESTBLOCK)

$(TESTCHAIN) : $(OBJSCHAIN)
	$(LD) $(OBJSCHAIN) $(LDFLAGS) -o $(TESTCHAIN)

testchain.o : testchain.cpp chain.h cs221util/PNG.h cs221util/HSLAPixel.h block.h
	$(CXX) $(CXXFLAGS) testchain.cpp

testblock.o : testblock.cpp cs221util/PNG.h cs221util/HSLAPixel.h block.h
	$(CXX) $(CXXFLAGS) testblock.cpp

chain.o : chain_given.cpp chain.cpp chain.h block.h
	$(CXX) $(CXXFLAGS) chain.cpp

block.o : block.cpp block.h cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/HSLAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

HSLAPixel.o : cs221util/HSLAPixel.cpp cs221util/HSLAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/HSLAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(TESTBLOCK) $(TESTCHAIN)
