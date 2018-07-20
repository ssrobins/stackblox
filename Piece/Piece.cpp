#include "Piece.h"
#include <assert.h>
#include <random>

int xOffsetCenter(const std::vector<std::vector<int>>& piece, int numTilesWidth)
{
    return ((numTilesWidth - static_cast<int>(piece.at(0).size())) / 2);
}

int yOffsetTop(const std::vector<std::vector<int>>& piece)
{
    unsigned int ytop;

    [&] {
        for (unsigned int y = 0; y < piece.size(); y++)
        {
            for (unsigned int x = 0; x < piece[y].size(); x++)
            {
                if (piece.at(y).at(x) == 1)
                {
                    ytop = y;
                    return;
                }
            }
        }
    }();

    return (0 - ytop);
}

bool Color::operator==(const Color& other) const
{
    return (r == other.r) &&
           (g == other.g) &&
           (b == other.b) &&
           (a == other.a);
}

bool Color::operator!=(const Color& other) const
{
    return (r != other.r) ||
           (g != other.g) ||
           (b != other.b) ||
           (a != other.a);
}

Piece::Piece()
{}

Piece::Piece(std::vector<std::vector<int>> piece, int x, int y, Color color)
    : color(color), xOffset(x), yOffset(y), yDefaultOffset(y)
{
    assert(matrixIsSquare(piece));

    rotation = 0;

    tileCoords = calcTileCoordinates(piece);
    tileCoords0 = tileCoords;
    tileCoords90 = calcTileCoordinates(calcRotation(piece));
    tileCoords180 = calcTileCoordinates(calcRotation(piece));
    tileCoords270 = calcTileCoordinates(calcRotation(piece));
}

bool Piece::matrixIsSquare(const std::vector<std::vector<int>>& piece)
{
    bool matrixIsSquare = true;

    auto firstDimension = piece.size();
    for (unsigned int i = 0; i < firstDimension; ++i)
    {
        if (firstDimension != piece.at(i).size())
        {
            matrixIsSquare = false;
            break;
        }
    }
    return matrixIsSquare;
}

const Color Piece::getColor() const
{
    return color;
}

std::vector<Point> Piece::getTileCoordinates() const
{
    std::vector<Point> tileCoordsOffset = tileCoords;

    for (unsigned int tile = 0; tile < tileCoords.size(); ++tile)
    {
        tileCoordsOffset.at(tile).x += xOffset;
        tileCoordsOffset.at(tile).y += yOffset;
    }

    return tileCoordsOffset;
}

std::vector<Point> Piece::rotate()
{
    if (rotation == 3)
        rotation = 0;
    else
        rotation++;

    switch (rotation)
    {
        case 0: tileCoords = tileCoords0;
            break;
        case 1: tileCoords = tileCoords90;
            break;
        case 2: tileCoords = tileCoords180;
            break;
        case 3: tileCoords = tileCoords270;
            break;
        default: break;
    }

    return getTileCoordinates();
}

void Piece::move(int x, int y)
{
    xOffset += x;
    yOffset += y;
}

bool Piece::atTop()
{
    return (yDefaultOffset == yOffset);
}

std::vector<Point> Piece::calcTileCoordinates(const std::vector<std::vector<int>>& piece)
{
    std::vector<Point> tiles;
    for (int row = 0; row < static_cast<int>(piece.size()); ++row)
    {
        for (int col = 0; col < static_cast<int>(piece[row].size()); ++col)
        {
            if (piece.at(row).at(col) == 1)
            {
                tiles.push_back({ col, row });
            }
        }
    }

    return tiles;
}

// Clockwise rotation of data in a square 2D matrix
// Rotation is done by saving the top row value, and taking the value from
// 90 degrees counter-clockwise and moving it to the top.
// Repeat for each of the four sides, then repeat for each item in the row.  Finally,
// Repeat for each layer of the matrix starting from the outside layer and working to the inside.
// Let's say you have a 4x4 matrix, m, with the following coordinates:
// 0,0   1,0   2,0   3,0
// 0,1   1,1   2,1   3,1
// 0,2   1,2   2,2   3,2
// 0,3   1,3   2,3   3,3
// Here is how the point-by-point rotation would work:
// layer = 0, first = 0, last = 3
// ==============================
// i = 0, offset = 3
// top = m(0,0)
// m(0,0) = m(0,3)
// m(0,3) = m(3,3)
// m(3,3) = m(3,0)
// m(3,0) = top
// ------------------------------
// i = 1, offset = 2
// top = m(1,0)
// m(1,0) = m(0,2)
// m(0,2) = m(2,3)
// m(2,3) = m(3,1)
// m(3,1) = top
// ------------------------------
// i = 2, offset = 1
// top = m(2,0)
// m(2,0) = m(0,1)
// m(0,1) = m(1,3)
// m(1,3) = m(3,2)
// m(3,2) = top
// ------------------------------
// layer = 1, first = 1, last = 2
// ==============================
// i = 1, offset = 2
// top = m(1,1)
// m(1,1) = m(1,2)
// m(1,2) = m(2,2)
// m(2,2) = m(2,1)
// m(2,1) = top
std::vector<std::vector<int>>& Piece::calcRotation(std::vector<std::vector<int>>& piece)
{
    auto length = piece.size();
    auto maxIndex = length - 1;
    for (unsigned int layer = 0; layer < length / 2; ++layer)
    {
        auto first = layer;
        auto last = maxIndex - layer;
        for (unsigned int i = first; i < last; ++i)
        {
            auto offset = maxIndex - i;

            // save top
            int top = piece.at(first).at(i);

            // left -> top
            piece.at(first).at(i) = piece.at(offset).at(first);

            // bottom -> left
            piece.at(offset).at(first) = piece.at(last).at(offset);

            // right -> bottom
            piece.at(last).at(offset) = piece.at(i).at(last);

            // top -> right
            piece.at(i).at(last) = top;
        }
    }

    return piece;
}

PieceCollection::PieceCollection(std::initializer_list<Piece> pieceCollection)
    : pieceCollection(pieceCollection)
    , currentPieceIndex(0)
{
}

Piece& PieceCollection::getCurrentPiece()
{
    return pieceCollection.at(currentPieceIndex);
}

Piece& PieceCollection::getRandomPiece()
{
    static std::random_device rd;
    static std::mt19937 engine(rd());
    static std::uniform_int_distribution<int> dist{ 0, static_cast<int>(pieceCollection.size() - 1) };

    currentPieceIndex = dist(engine);

    return getCurrentPiece();
}
