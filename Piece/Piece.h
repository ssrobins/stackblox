#pragma once

#include <vector>

int xOffsetCenter(const std::vector<std::vector<int>>& piece, int numTilesWidth);
int yOffsetTop(const std::vector<std::vector<int>>& piece);

struct Point
{
    int x;
    int y;
};

struct Color
{
    int r;
    int g;
    int b;
    int a;

    bool operator==(const Color& other) const;
    bool operator!=(const Color& other) const;
};

static Color black = { 0, 0, 0, 255 };

class Piece
{
public:
    Piece();
    Piece(std::vector<std::vector<int>> piece, int x = 0, int y = 0, Color color = black);
    bool matrixIsSquare(const std::vector<std::vector<int>>& piece);
    const Color getColor() const;
    std::vector<Point> getTileCoordinates() const;
    std::vector<Point> rotate();
    void move(int xOffset, int yOffset);
    bool atTop();
private:
    std::vector<Point> calcTileCoordinates(const std::vector<std::vector<int>>& piece);
    std::vector<std::vector<int>>& calcRotation(std::vector<std::vector<int>>& piece);
    int rotation;  // 0, 1, 2, 3
    std::vector<Point> tileCoords;
    std::vector<Point> tileCoords0;
    std::vector<Point> tileCoords90;
    std::vector<Point> tileCoords180;
    std::vector<Point> tileCoords270;
    Color color;
    int xOffset;
    int yOffset;
    int yDefaultOffset;
};

class PieceCollection
{
public:
    PieceCollection(std::initializer_list<Piece> pieceCollection);
    Piece& getCurrentPiece();
    Piece& getRandomPiece();
private:
    std::vector<Piece> pieceCollection;
    int currentPieceIndex;
};

const std::vector<std::vector<int>> pieceI{
    { 0, 0, 1, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const Color pieceIcolor = { 0, 255, 255, 255 };

const std::vector<std::vector<int>> pieceJ{
    { 0, 1, 0, },
    { 1, 1, 1, },
    { 0, 0, 1, }
};
const Color pieceJcolor = { 0, 0, 255, 255 };

const std::vector<std::vector<int>> pieceL{
    { 0, 1, 0, },
    { 1, 1, 1, },
    { 1, 0, 0, }
};
const Color pieceLcolor = { 255, 165, 0, 255 };

const std::vector<std::vector<int>> pieceO{
    { 1, 1, 1, },
    { 1, 1, 0, },
    { 0, 0, 0, }
};
const Color pieceOcolor = { 255, 255, 0, 255 };

const std::vector<std::vector<int>> pieceS{
    { 0, 1, 1, },
    { 1, 1, 0, },
    { 1, 0, 0, }
};
const Color pieceScolor = { 0, 255, 0, 255 };

const std::vector<std::vector<int>> pieceT{
    { 0, 1, 0, },
    { 1, 1, 1, },
    { 0, 1, 0, }
};
const Color pieceTcolor = { 128, 0, 128, 255 };

const std::vector<std::vector<int>> pieceZ{
    { 1, 1, 0, },
    { 0, 1, 1, },
    { 0, 0, 1, }
};
const Color pieceZcolor = { 255, 0, 0, 255 };


/*const std::vector<std::vector<int>> pieceI{
    { 0, 0, 0, 0 },
    { 1, 1, 1, 1 },
    { 0, 0, 0, 0 },
    { 0, 0, 0, 0 }
};
const Color pieceIcolor = { 0, 255, 255, 255 };

const std::vector<std::vector<int>> pieceJ{
    { 0, 0, 0, },
    { 1, 1, 1, },
    { 0, 0, 1, }
};
const Color pieceJcolor = { 0, 0, 255, 255 };

const std::vector<std::vector<int>> pieceL{
    { 0, 0, 0, },
    { 1, 1, 1, },
    { 1, 0, 0, }
};
const Color pieceLcolor = { 255, 165, 0, 255 };

const std::vector<std::vector<int>> pieceO{
    { 1, 1, },
    { 1, 1, }
};
const Color pieceOcolor = { 255, 255, 0, 255 };

const std::vector<std::vector<int>> pieceS{
    { 0, 1, 1, },
    { 1, 1, 0, },
    { 0, 0, 0, }
};
const Color pieceScolor = { 0, 255, 0, 255 };

const std::vector<std::vector<int>> pieceT{
    { 0, 0, 0, },
    { 1, 1, 1, },
    { 0, 1, 0, }
};
const Color pieceTcolor = { 128, 0, 128, 255 };

const std::vector<std::vector<int>> pieceZ{
    { 1, 1, 0, },
    { 0, 1, 1, },
    { 0, 0, 0, }
};
const Color pieceZcolor = { 255, 0, 0, 255 };*/
