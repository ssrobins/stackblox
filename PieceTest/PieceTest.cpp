#include "Piece.h"
#include "gtest/gtest.h"
#include <iostream>


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


TEST(coordinates, pieceI)
{
    Piece piece(pieceI);

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


TEST(yOffsetTop, pieceI)
{
    EXPECT_EQ(-1, yOffsetTop(pieceI));
}


TEST(coordinates, pieceJ)
{
    Piece piece(pieceJ);

    std::vector<Point> tilesRef0{
        { 0, 1 },       // O O O
        { 1, 1 },       // X X X
        { 2, 1 },       // O O X
        { 2, 2 },
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 1, 0 },       // O X O
        { 1, 1 },       // O X O
        { 0, 2 },       // X X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 0, 0 },       // X O O
        { 0, 1 },       // X X X
        { 1, 1 },       // O O O
        { 2, 1 },
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 1, 0 },       // O X X
        { 2, 0 },       // O X O
        { 1, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, pieceJ)
{
    EXPECT_EQ(-1, yOffsetTop(pieceJ));
}


TEST(coordinates, pieceL)
{
    Piece piece(pieceL);

    std::vector<Point> tilesRef0{
        { 0, 1 },       // O O O
        { 1, 1 },       // X X X
        { 2, 1 },       // X O O
        { 0, 2 },
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 0, 0 },       // X X O
        { 1, 0 },       // O X O
        { 1, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 2, 0 },       // O O X
        { 0, 1 },       // X X X
        { 1, 1 },       // O O O
        { 2, 1 },
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 1, 0 },       // O X O
        { 1, 1 },       // O X O
        { 1, 2 },       // O X X
        { 2, 2 },
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, pieceL)
{
    EXPECT_EQ(-1, yOffsetTop(pieceL));
}


TEST(coordinates, pieceO)
{
    Piece piece(pieceO);

    std::vector<Point> tilesRef0{
        { 0, 0 },       // X X
        { 1, 0 },       // X X
        { 0, 1 },
        { 1, 1 },
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 0, 0 },       // X X
        { 1, 0 },       // X X
        { 0, 1 },
        { 1, 1 },
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 0, 0 },       // X X
        { 1, 0 },       // X X
        { 0, 1 },
        { 1, 1 },
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 0, 0 },       // X X
        { 1, 0 },       // X X
        { 0, 1 },
        { 1, 1 },
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, pieceO)
{
    EXPECT_EQ(0, yOffsetTop(pieceO));
}


TEST(coordinates, pieceS)
{
    Piece piece(pieceS);

    std::vector<Point> tilesRef0{
        { 1, 0 },       // O X X
        { 2, 0 },       // X X O
        { 0, 1 },       // O O O
        { 1, 1 },
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 1, 0 },       // O X O
        { 1, 1 },       // O X X
        { 2, 1 },       // O O X
        { 2, 2 },
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 1, 1 },       // O O O
        { 2, 1 },       // O X X
        { 0, 2 },       // X X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 0, 0 },       // X O O
        { 0, 1 },       // X X O
        { 1, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, pieceS)
{
    EXPECT_EQ(0, yOffsetTop(pieceS));
}


TEST(coordinates, pieceT)
{
    Piece piece(pieceT);

    std::vector<Point> tilesRef0{
        { 0, 1 },       // O O O
        { 1, 1 },       // X X X
        { 2, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 1, 0 },       // O X O
        { 0, 1 },       // X X O
        { 1, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 1, 0 },       // O X O
        { 0, 1 },       // X X X
        { 1, 1 },       // O O O
        { 2, 1 },
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 1, 0 },       // O X O
        { 1, 1 },       // O X X
        { 2, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, pieceT)
{
    EXPECT_EQ(-1, yOffsetTop(pieceT));
}


TEST(coordinates, pieceZ)
{
    Piece piece(pieceZ);

    std::vector<Point> tilesRef0{
        { 0, 0 },       // X X O
        { 1, 0 },       // O X X
        { 1, 1 },       // O O O
        { 2, 1 },
    };
    expectTileCoordinatesEqual(tilesRef0, piece.getTileCoordinates(), "Original");

    std::vector<Point> tilesRef90{
        { 2, 0 },       // O O X
        { 1, 1 },       // O X X
        { 2, 1 },       // O X O
        { 1, 2 },
    };
    expectTileCoordinatesEqual(tilesRef90, piece.rotate(), "90 Degrees");

    std::vector<Point> tilesRef180{
        { 0, 1 },       // O O O
        { 1, 1 },       // X X O
        { 1, 2 },       // O X X
        { 2, 2 },
    };
    expectTileCoordinatesEqual(tilesRef180, piece.rotate(), "180 Degrees");

    std::vector<Point> tilesRef270{
        { 1, 0 },       // O X O
        { 0, 1 },       // X X O
        { 1, 1 },       // X O O
        { 0, 2 },
    };
    expectTileCoordinatesEqual(tilesRef270, piece.rotate(), "270 Degrees");

    expectTileCoordinatesEqual(tilesRef0, piece.rotate(), "360 Degrees");
}


TEST(yOffsetTop, pieceZ)
{
    EXPECT_EQ(0, yOffsetTop(pieceZ));
}


TEST(offset, positive)
{
    Piece piece(pieceI);

    piece.move(1, 0);
    std::vector<Point> tilesRef{
        { 1, 1 },       // O O O O
        { 2, 1 },       // X X X X
        { 3, 1 },       // O O O O
        { 4, 1 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef, piece.getTileCoordinates(), "Positive Offset");
}


TEST(offset, negative)
{
    Piece piece(pieceI);

    piece.move(-1, 0);
    std::vector<Point> tilesRef{
        {-1, 1 },       // O O O O
        { 0, 1 },       // X X X X
        { 1, 1 },       // O O O O
        { 2, 1 },       // O O O O
    };
    expectTileCoordinatesEqual(tilesRef, piece.getTileCoordinates(), "Negative Offset");
}


TEST(offset, positiveRotated)
{
    Piece piece(pieceI);

    piece.move(1, 0);
    std::vector<Point> tilesRef{
        { 3, 0 },       // O O X O
        { 3, 1 },       // O O X O
        { 3, 2 },       // O O X O
        { 3, 3 },       // O O X O
    };
    expectTileCoordinatesEqual(tilesRef, piece.rotate(), "Positive Rotated Offset");
}


TEST(offset, negativeRotated)
{
    Piece piece(pieceI);

    piece.move(-1, 0);
    std::vector<Point> tilesRef{
        { 1, 0 },       // O O X O
        { 1, 1 },       // O O X O
        { 1, 2 },       // O O X O
        { 1, 3 },       // O O X O
    };
    expectTileCoordinatesEqual(tilesRef, piece.rotate(), "Negative Rotated Offset");
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
