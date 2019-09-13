#include "Piece.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <iostream>


// This plus the gmock include above are simply to test that gmock works. Remove when any tests start using gmock for real.
using ::testing::AtLeast;

void expectTileCoordinatesEqual(const std::vector<Point>& tilesRef, const std::vector<Point>& tiles, const std::string& testName)
{
    ASSERT_EQ(tilesRef.size(), tiles.size());

    for (unsigned int tile = 0; tile < tiles.size(); ++tile)
    {
        std::cout << testName << " tile #" << tile << std::endl;
        EXPECT_EQ(tilesRef.at(tile).x, tiles.at(tile).x);
        EXPECT_EQ(tilesRef.at(tile).y, tiles.at(tile).y);
    }
}


const std::vector<std::vector<int>> samplePiece{
    { 0, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
};


TEST(coordinates, piece)
{
    Piece piece(samplePiece);

    std::vector<Point> tilesRef0{
        { 0, 1 },       // O O O O
        { 1, 1 },       // X X X X
        { 2, 1 },       // O O O O
        { 3, 1 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 2, 0 },       // O O X O
        { 2, 1 },       // O O X O
        { 2, 2 },       // O O X O
        { 2, 3 },       // O O X O
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 0, 2 },       // O O O O
        { 1, 2 },       // O O O O
        { 2, 2 },       // X X X X
        { 3, 2 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 1, 0 },       // O X O O
        { 1, 1 },       // O X O O
        { 1, 2 },       // O X O O
        { 1, 3 },       // O X O O
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, piece)
{
    EXPECT_EQ(-1, yOffsetTop(samplePiece));
}


TEST(move, positiveX)
{
    Piece piece(samplePiece);

    piece.move(1, 0);
    std::vector<Point> tilesRef{
        { 1, 1 },       // O O O O
        { 2, 1 },       // X X X X
        { 3, 1 },       // O O O O
        { 4, 1 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef, piece.getTileCoordinates(), "");
}


TEST(move, negativeX)
{
    Piece piece(samplePiece);

    piece.move(-1, 0);
    std::vector<Point> tilesRef{
        {-1, 1 },       // O O O O
        { 0, 1 },       // X X X X
        { 1, 1 },       // O O O O
        { 2, 1 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef, piece.getTileCoordinates(), "");
}


TEST(move, positiveY)
{
    Piece piece(samplePiece);

    piece.move(0, 2);
    std::vector<Point> tilesRef{
        { 0, 3 },       // O O O O
        { 1, 3 },       // X X X X
        { 2, 3 },       // O O O O
        { 3, 3 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef, piece.getTileCoordinates(), "");
}


TEST(move, negativeY)
{
    Piece piece(samplePiece);

    piece.move(0, -2);
    std::vector<Point> tilesRef{
        { 0,-1 },       // O O O O
        { 1,-1 },       // X X X X
        { 2,-1 },       // O O O O
        { 3,-1 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef, piece.getTileCoordinates(), "");
}


TEST(move, thenRotate)
{
    Piece piece(samplePiece);

    piece.move(4, -3);
    std::vector<Point> tilesRef{
        { 6,-3 },       // O O X O
        { 6,-2 },       // O O X O
        { 6,-1 },       // O O X O
        { 6, 0 },       // O O X O
    };
    expectTileCoordinatesEqual(tilesRef, piece.rotate(), "");
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
