#include "Display.h"
#include "gtest/gtest.h"

TEST(display, widthIsTheLimitingDimension)
{
    Display display(12, 20);
    display.setDisplaySize(101, 333, 1.0f, false);
    EXPECT_EQ(101, display.getScreenWidth());
    EXPECT_EQ(333, display.getScreenHeight());
    EXPECT_EQ(96, display.getGameWidth());
    EXPECT_EQ(160, display.getGameHeight());
    EXPECT_EQ(8, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, widthIsTheLimitingDimensionWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(101, 333, 1.0f, true);
    EXPECT_EQ(101, display.getScreenWidth());
    EXPECT_EQ(333, display.getScreenHeight());
    EXPECT_EQ(98, display.getGameWidth());
    EXPECT_EQ(162, display.getGameHeight());
    EXPECT_EQ(8, display.getTileSize());
    EXPECT_EQ(1, display.getOutlineOffsetWidth());
    EXPECT_EQ(1, display.getOutlineOffsetHeight());
}

TEST(display, heightIsTheLimitingDimension)
{
    Display display(12, 20);
    display.setDisplaySize(320, 240, 1.0f, false);
    EXPECT_EQ(320, display.getScreenWidth());
    EXPECT_EQ(240, display.getScreenHeight());
    EXPECT_EQ(144, display.getGameWidth());
    EXPECT_EQ(240, display.getGameHeight());
    EXPECT_EQ(12, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, heightIsTheLimitingDimensionWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(320, 240, 1.0f, true);
    EXPECT_EQ(320, display.getScreenWidth());
    EXPECT_EQ(240, display.getScreenHeight());
    EXPECT_EQ(146, display.getGameWidth());
    EXPECT_EQ(240, display.getGameHeight());
    EXPECT_EQ(12, display.getTileSize());
    EXPECT_EQ(1, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, neitherWidthNorHeightIsTheLimitingDimension)
{
    Display display(12, 20);
    display.setDisplaySize(60, 100, 1.0f, false);
    EXPECT_EQ(60, display.getScreenWidth());
    EXPECT_EQ(100, display.getScreenHeight());
    EXPECT_EQ(60, display.getGameWidth());
    EXPECT_EQ(100, display.getGameHeight());
    EXPECT_EQ(5, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, neitherWidthNorHeightIsTheLimitingDimensionWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(60, 100, 1.0f, true);
    EXPECT_EQ(60, display.getScreenWidth());
    EXPECT_EQ(100, display.getScreenHeight());
    EXPECT_EQ(60, display.getGameWidth());
    EXPECT_EQ(100, display.getGameHeight());
    EXPECT_EQ(5, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, zeroScaling)
{
    Display display(12, 20);
    display.setDisplaySize(320, 240, 0.0f, false);
    EXPECT_EQ(320, display.getScreenWidth());
    EXPECT_EQ(240, display.getScreenHeight());
    EXPECT_EQ(0, display.getGameWidth());
    EXPECT_EQ(0, display.getGameHeight());
    EXPECT_EQ(0, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, zeroScalingWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(320, 240, 0.0f, true);
    EXPECT_EQ(320, display.getScreenWidth());
    EXPECT_EQ(240, display.getScreenHeight());
    EXPECT_EQ(2, display.getGameWidth());
    EXPECT_EQ(2, display.getGameHeight());
    EXPECT_EQ(0, display.getTileSize());
    EXPECT_EQ(1, display.getOutlineOffsetWidth());
    EXPECT_EQ(1, display.getOutlineOffsetHeight());
}

TEST(display, halfScaling)
{
    Display display(12, 20);
    display.setDisplaySize(320, 240, 0.5f, false);
    EXPECT_EQ(320, display.getScreenWidth());
    EXPECT_EQ(240, display.getScreenHeight());
    EXPECT_EQ(72, display.getGameWidth());
    EXPECT_EQ(120, display.getGameHeight());
    EXPECT_EQ(6, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, halfScalingWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(320, 240, 0.5f, true);
    EXPECT_EQ(320, display.getScreenWidth());
    EXPECT_EQ(240, display.getScreenHeight());
    EXPECT_EQ(74, display.getGameWidth());
    EXPECT_EQ(122, display.getGameHeight());
    EXPECT_EQ(6, display.getTileSize());
    EXPECT_EQ(1, display.getOutlineOffsetWidth());
    EXPECT_EQ(1, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenOnePlus5)
{
    Display display(12, 20);
    display.setDisplaySize(1080, 1920, 1.0f, false);
    EXPECT_EQ(1080, display.getScreenWidth());
    EXPECT_EQ(1920, display.getScreenHeight());
    EXPECT_EQ(1080, display.getGameWidth());
    EXPECT_EQ(1800, display.getGameHeight());
    EXPECT_EQ(90, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenOnePlus5WithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(1080, 1920, 1.0f, true);
    EXPECT_EQ(1080, display.getScreenWidth());
    EXPECT_EQ(1920, display.getScreenHeight());
    EXPECT_EQ(1080, display.getGameWidth());
    EXPECT_EQ(1814, display.getGameHeight());
    EXPECT_EQ(90, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(7, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenMotorolaMotoXPureEdition)
{
    // Note: Screen height is 2392 because the nav stays on the screen,
    // at least in SDL 2.0.8
    Display display(12, 20);
    display.setDisplaySize(1440, 2392, 1.0f, false);
    EXPECT_EQ(1440, display.getScreenWidth());
    EXPECT_EQ(2392, display.getScreenHeight());
    EXPECT_EQ(1428, display.getGameWidth());
    EXPECT_EQ(2380, display.getGameHeight());
    EXPECT_EQ(119, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenMotorolaMotoXPureEditionWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(1440, 2392, 1.0f, true);
    EXPECT_EQ(1440, display.getScreenWidth());
    EXPECT_EQ(2392, display.getScreenHeight());
    EXPECT_EQ(1428, display.getGameWidth());
    EXPECT_EQ(2380, display.getGameHeight());
    EXPECT_EQ(119, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIpadMini2)
{
    Display display(12, 20);
    display.setDisplaySize(1536, 2048, 1.0f, false);
    EXPECT_EQ(1536, display.getScreenWidth());
    EXPECT_EQ(2048, display.getScreenHeight());
    EXPECT_EQ(1224, display.getGameWidth());
    EXPECT_EQ(2040, display.getGameHeight());
    EXPECT_EQ(102, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIpadMini2WithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(1536, 2048, 1.0f, true);
    EXPECT_EQ(1536, display.getScreenWidth());
    EXPECT_EQ(2048, display.getScreenHeight());
    EXPECT_EQ(1240, display.getGameWidth());
    EXPECT_EQ(2040, display.getGameHeight());
    EXPECT_EQ(102, display.getTileSize());
    EXPECT_EQ(8, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphone4s)
{
    Display display(12, 20);
    display.setDisplaySize(640, 960, 1.0f, false);
    EXPECT_EQ(640, display.getScreenWidth());
    EXPECT_EQ(960, display.getScreenHeight());
    EXPECT_EQ(576, display.getGameWidth());
    EXPECT_EQ(960, display.getGameHeight());
    EXPECT_EQ(48, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphone4sWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(640, 960, 1.0f, true);
    EXPECT_EQ(640, display.getScreenWidth());
    EXPECT_EQ(960, display.getScreenHeight());
    EXPECT_EQ(582, display.getGameWidth());
    EXPECT_EQ(960, display.getGameHeight());
    EXPECT_EQ(48, display.getTileSize());
    EXPECT_EQ(3, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphone8)
{
    Display display(12, 20);
    display.setDisplaySize(1242, 2208, 1.0f, false);
    EXPECT_EQ(1242, display.getScreenWidth());
    EXPECT_EQ(2208, display.getScreenHeight());
    EXPECT_EQ(1236, display.getGameWidth());
    EXPECT_EQ(2060, display.getGameHeight());
    EXPECT_EQ(103, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphone8WithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(1242, 2208, 1.0f, true);
    EXPECT_EQ(1242, display.getScreenWidth());
    EXPECT_EQ(2208, display.getScreenHeight());
    EXPECT_EQ(1236, display.getGameWidth());
    EXPECT_EQ(2076, display.getGameHeight());
    EXPECT_EQ(103, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(8, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphoneX)
{
    Display display(12, 20);
    display.setDisplaySize(1125, 2436, 1.0f, false);
    EXPECT_EQ(1125, display.getScreenWidth());
    EXPECT_EQ(2436, display.getScreenHeight());
    EXPECT_EQ(1116, display.getGameWidth());
    EXPECT_EQ(1860, display.getGameHeight());
    EXPECT_EQ(93, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphoneXWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(1125, 2436, 1.0f, true);
    EXPECT_EQ(1125, display.getScreenWidth());
    EXPECT_EQ(2436, display.getScreenHeight());
    EXPECT_EQ(1116, display.getGameWidth());
    EXPECT_EQ(1874, display.getGameHeight());
    EXPECT_EQ(93, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(7, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphoneXs)
{
    Display display(12, 20);
    display.setDisplaySize(1242, 2688, 1.0f, false);
    EXPECT_EQ(1242, display.getScreenWidth());
    EXPECT_EQ(2688, display.getScreenHeight());
    EXPECT_EQ(1236, display.getGameWidth());
    EXPECT_EQ(2060, display.getGameHeight());
    EXPECT_EQ(103, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenIphoneXsWithOutline)
{
    Display display(12, 20);
    display.setDisplaySize(1242, 2688, 1.0f, true);
    EXPECT_EQ(1242, display.getScreenWidth());
    EXPECT_EQ(2688, display.getScreenHeight());
    EXPECT_EQ(1236, display.getGameWidth());
    EXPECT_EQ(2076, display.getGameHeight());
    EXPECT_EQ(103, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(8, display.getOutlineOffsetHeight());
}

TEST(display, windowMacBookProRetina13inchEarly2015)
{
    Display display(12, 20);
    display.setDisplaySize(2560, 1600, 0.80f, false);
    EXPECT_EQ(2560, display.getScreenWidth());
    EXPECT_EQ(1600, display.getScreenHeight());
    EXPECT_EQ(768, display.getGameWidth());
    EXPECT_EQ(1280, display.getGameHeight());
    EXPECT_EQ(64, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, windowSurfacePro4)
{
    Display display(12, 20);
    display.setDisplaySize(2736, 1824, 0.80f, false);
    EXPECT_EQ(2736, display.getScreenWidth());
    EXPECT_EQ(1824, display.getScreenHeight());
    EXPECT_EQ(864, display.getGameWidth());
    EXPECT_EQ(1440, display.getGameHeight());
    EXPECT_EQ(72, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenMacbookRes60)
{
    Display display(32, 18);
    display.setDisplaySize(2560, 1600, 1.0f, false);
    EXPECT_EQ(2560, display.getScreenWidth());
    EXPECT_EQ(1600, display.getScreenHeight());
    EXPECT_EQ(2560, display.getGameWidth());
    EXPECT_EQ(1440, display.getGameHeight());
    EXPECT_EQ(80, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenMacbookRes60WithOutline)
{
    Display display(32, 18);
    display.setDisplaySize(2560, 1600, 1.0f, true);
    EXPECT_EQ(2560, display.getScreenWidth());
    EXPECT_EQ(1600, display.getScreenHeight());
    EXPECT_EQ(2560, display.getGameWidth());
    EXPECT_EQ(1458, display.getGameHeight());
    EXPECT_EQ(80, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(9, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenStandardRes60Tile)
{
    Display display(32, 18);
    display.setDisplaySize(1920, 1080, 1.0f, false);
    EXPECT_EQ(1920, display.getScreenWidth());
    EXPECT_EQ(1080, display.getScreenHeight());
    EXPECT_EQ(1920, display.getGameWidth());
    EXPECT_EQ(1080, display.getGameHeight());
    EXPECT_EQ(60, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}

TEST(display, fullscreenStandardRes32Tile)
{
    Display display(60, 33);
    display.setDisplaySize(1920, 1080, 1.0f, false);
    EXPECT_EQ(1920, display.getScreenWidth());
    EXPECT_EQ(1080, display.getScreenHeight());
    EXPECT_EQ(1920, display.getGameWidth());
    EXPECT_EQ(1056, display.getGameHeight());
    EXPECT_EQ(32, display.getTileSize());
    EXPECT_EQ(0, display.getOutlineOffsetWidth());
    EXPECT_EQ(0, display.getOutlineOffsetHeight());
}
