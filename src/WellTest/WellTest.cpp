#include "Well.h"
#include "gtest/gtest.h"


TEST(score, zero)
{
    Score score;
    EXPECT_EQ(0, score.getScore());
}

TEST(score, firstPiece)
{
    Score score;
    score.setScore(0, 0);
    EXPECT_EQ(1, score.getScore());
}

TEST(score, maxDropDelay)
{
    Score score;
    score.setScore(0, 900);
    EXPECT_EQ(901, score.getScore());
}

TEST(score, oneLine)
{
    Score score;
    score.setScore(1, 0);
    EXPECT_EQ(101, score.getScore());
}

TEST(score, twoLines)
{
    Score score;
    score.setScore(2, 0);
    EXPECT_EQ(251, score.getScore());
}

TEST(score, threeLines)
{
    Score score;
    score.setScore(3, 0);
    EXPECT_EQ(451, score.getScore());
}

TEST(score, fourLines)
{
    Score score;
    score.setScore(4, 0);
    EXPECT_EQ(701, score.getScore());
}

TEST(score, fiveLines)
{
    Score score;
    score.setScore(5, 0);
    EXPECT_EQ(1001, score.getScore());
}

TEST(score, maxPieceScore)
{
    Score score;
    score.setScore(5, 900);
    EXPECT_EQ(1901, score.getScore());
}


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


TEST(addPieceToWell, pieceHasNagativeCoordinates)
{
    Well well(2, 2);
    std::vector<std::vector<int>> piece = {
        { 0, 0 },
        { 1, 1 },
    };
    well.newPiece(Piece(piece, 0, yOffsetTop(piece), Color{ 1, 0, 0, 0 }));
    well.rotatePiece();

    well.addPieceToWell();
    std::vector<std::vector<Color>> wellVals = well.getWellValues();

    std::vector<std::vector<Color>> wellValsRef = {
        { Color{ 1, 0, 0, 0 }, Color{ 0, 0, 0, 0 } },
        { Color{ 0, 0, 0, 0 }, Color{ 0, 0, 0, 0 } }
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
