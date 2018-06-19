#include "Well.h"
#include "gtest/gtest.h"


TEST(collision, blankNoPiece)
{
    Well well(0, 0);
    well.newPiece(Piece(std::vector<std::vector<int>>{}));

    EXPECT_FALSE(well.collision());
}

TEST(collision, blankWithPiece)
{
    Well well(0, 0);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}));

    EXPECT_TRUE(well.collision());
}

TEST(collision, wellWidthNoHeightWithPiece)
{
    Well well(1, 0);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}));

    EXPECT_TRUE(well.collision());
}

TEST(collision, wellHeightNoWidthWithPiece)
{
    Well well(0, 1);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}));

    EXPECT_TRUE(well.collision());
}

TEST(collision, pieceInWell)
{
    Well well(1, 1);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}));

    EXPECT_FALSE(well.collision());
}

TEST(collision, pieceNegativeCoord)
{
    Well well(1, 1);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}, -1));

    EXPECT_TRUE(well.collision());
}

TEST(collision, pieceRightOfWell)
{
    Well well(1, 1);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}, 1));

    EXPECT_TRUE(well.collision());
}

TEST(collision, pieceBelowWell)
{
    Well well(1, 1);
    well.newPiece(Piece(std::vector<std::vector<int>>{{1}}, 0, 1));

    EXPECT_TRUE(well.collision());
}


void expectWellsEqual(const std::vector<std::vector<Color>>& wellValsRef, const std::vector<std::vector<Color>>& wellVals)
{
    ASSERT_EQ(wellValsRef.size(), wellVals.size());

    for (unsigned int x = 0; x < wellValsRef.size(); x++)
    {
        ASSERT_EQ(wellValsRef[x].size(), wellVals[x].size());
        for (unsigned int y = 0; y < wellValsRef[x].size(); y++)
        {
            EXPECT_EQ(wellValsRef.at(x).at(y), wellVals.at(x).at(y));
        }
    }
}

TEST(deleteCompleteLines, emptyWell)
{
    Well well(0, 0);
    well.newPiece(Piece(std::vector<std::vector<int>>{}, 0, 0, Color{ 1, 0, 0, 0 }));
    well.addPieceToWell();

    std::vector<std::vector<Color>> wellValsRef = well.getWellValues();

    well.deleteCompleteLines();

    std::vector<std::vector<Color>> wellVals = well.getWellValues();
    expectWellsEqual(wellValsRef, wellVals);
}

TEST(deleteCompleteLines, noLinesComplete)
{
    Well well(2, 2);
    well.newPiece(Piece(std::vector<std::vector<int>> { { 0, 0 }, { 1, 0 } }, 0, 0, Color{ 1, 0, 0, 0 }));
    well.addPieceToWell();

    std::vector<std::vector<Color>> wellValsRef = well.getWellValues();

    well.deleteCompleteLines();

    std::vector<std::vector<Color>> wellVals = well.getWellValues();
    expectWellsEqual(wellValsRef, wellVals);
}

TEST(deleteCompleteLines, oneLineComplete)
{
    Well well(2, 2);
    well.newPiece(Piece(std::vector<std::vector<int>> { { 0, 0 }, { 1, 1 } }, 0, 0, Color{ 1, 0, 0, 0 }));

    well.addPieceToWell();
    well.deleteCompleteLines();
    std::vector<std::vector<Color>> wellVals = well.getWellValues();

    std::vector<std::vector<Color>> wellValsRef = {
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
    };

    expectWellsEqual(wellValsRef, wellVals);
}

TEST(deleteCompleteLines, twoLinesComplete)
{
    std::vector<std::vector<int>> piece = {
        { 1, 1 },
        { 1, 1 }
    };
    Well well(2, 2);
    well.newPiece(Piece(piece, 0, 0, Color{ 1, 0, 0, 0 }));

    well.addPieceToWell();
    well.deleteCompleteLines();
    std::vector<std::vector<Color>> wellVals = well.getWellValues();

    std::vector<std::vector<Color>> wellValsRef = {
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
    };

    expectWellsEqual(wellValsRef, wellVals);
}

TEST(deleteCompleteLines, twoLinesCompleteSeparate)
{
    std::vector<std::vector<int>> piece = {
        { 1, 1, 1 },
        { 1, 0, 1 },
        { 1, 1, 1 },
    };
    Well well(3, 3);
    well.newPiece(Piece(piece, 0, 0, Color{ 1, 0, 0, 0 }));

    well.addPieceToWell();
    well.deleteCompleteLines();
    std::vector<std::vector<Color>> wellVals = well.getWellValues();

    std::vector<std::vector<Color>> wellValsRef = {
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
        { Color{ 1, 0, 0, 0 }, Color{ 0, 0, 0, 0 }, Color{ 1, 0, 0, 0 } }
    };

    expectWellsEqual(wellValsRef, wellVals);
}


TEST(getDropDelay, default)
{
    Well well(0, 0);
    EXPECT_EQ(std::chrono::milliseconds{ 1000 }, well.getDropDelay());
}


TEST(decreaseDropDelay, decreaseOneInterval)
{
    Well well(0, 0);
    EXPECT_EQ(std::chrono::milliseconds{ 995 }, well.decreaseDropDelay());
}


TEST(decreaseDropDelay, decreaseToSmallestInterval)
{
    Well well(0, 0);
    for (unsigned int n = 1; n < 179; n++)
    {
        well.decreaseDropDelay();
    }
    EXPECT_EQ(std::chrono::milliseconds{ 105 }, well.decreaseDropDelay());
    EXPECT_EQ(std::chrono::milliseconds{ 100 }, well.decreaseDropDelay());
    EXPECT_EQ(std::chrono::milliseconds{ 100 }, well.decreaseDropDelay());
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
