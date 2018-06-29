#include "Display.h"
#include "gtest/gtest.h"

const int numTilesWidth = 12;
const int numTilesHeight = 20;


TEST(display, widthIsTheLimitingDimension)
{
    Display display(numTilesWidth, numTilesHeight, 1.0);
    display.setDisplaySize(1242, 2208); // 5.5" retina display

    EXPECT_EQ(1242, display.getScreenWidth());
    EXPECT_EQ(2208, display.getScreenHeight());
    EXPECT_EQ(1236, display.getGameWidth());
    EXPECT_EQ(2060, display.getGameHeight());
    EXPECT_EQ(103, display.getTileSize());
}

TEST(display, heightIsTheLimitingDimension)
{
    Display display(numTilesWidth, numTilesHeight, 1.0);
    display.setDisplaySize(2048, 2732); // 12.9" retina display

    EXPECT_EQ(2048, display.getScreenWidth());
    EXPECT_EQ(2732, display.getScreenHeight());
    EXPECT_EQ(1632, display.getGameWidth());
    EXPECT_EQ(2720, display.getGameHeight());
    EXPECT_EQ(136, display.getTileSize());
}

TEST(display, neitherWidthNorHeightIsTheLimitingDimension)
{
    Display display(numTilesWidth, numTilesHeight, 1.0);
    display.setDisplaySize(60, 100);

    EXPECT_EQ(60, display.getScreenWidth());
    EXPECT_EQ(100, display.getScreenHeight());
    EXPECT_EQ(60, display.getGameWidth());
    EXPECT_EQ(100, display.getGameHeight());
    EXPECT_EQ(5, display.getTileSize());
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
