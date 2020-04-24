#include<iostream>
#include<string>

using namespace std;

#include "olcConsoleGameEngine.h"

class OneLoneCoder_Platformer : public olcConsoleGameEngine {
public:
    OneLoneCoder_Platformer() {
        m_sAppName = L"Tile Based Platform Game";
    }
private:
    //defining the level
    wstring sLevel;
    int nLevelWidth;
    int nLevelHeight;

    float fPlayerPosX = 0.0f;
    float fPlayerPosY = 0.0f;

    float fPlayerVelX = 0.0f;
    float fPlayerVelY = 0.0f;

    float fCameraPosX = 0.0f;
    float fCameraPosY = 0.0f;

protected:
    virtual bool OnUserCreate() {
        nLevelWidth = 64;
        nLevelHeight = 16;
        sLevel += L"................................................................";
        sLevel += L"................................................................";
        sLevel += L"................................................................";
        sLevel += L"........................#.......................................";
        sLevel += L"......................##..................#.#...................";
        sLevel += L".......#...........###....................###...................";
        sLevel += L"..................#.......................#.#...................";
        sLevel += L"................#...............................................";
        sLevel += L"#################################.#############......###########"; //ground of level
        sLevel += L"................................#.#...............###...........";
        sLevel += L"................................#.#............###..............";
        sLevel += L"..................###############...........###.................";
        sLevel += L"..................#......................###....................";
        sLevel += L"..................#...................###.......................";
        sLevel += L"..................####################..........................";
        sLevel += L"................................................................";

        return true;
    }

    virtual bool OnUserUpdate(float fElapsedTime) {
        //Utility Lambdas (??)
        auto GetTile = [&](int x, int y) {
            if(x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
              return sLevel[y * nLevelWidth + x];
            else
                return L' ';
        };

        auto SetTile = [&](int x, int y) {
            if(x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
              return sLevel[y * nLevelWidth + x];
            else
                return L' ';
        };

        fPlayerVelX = 0.0f;
        fPlayerVelY = 0.0f;

        //Handle User Input
        if(IsFocused()) {
            if(GetKey(VK_UP).bHeld) {
                fPlayerVelY = -6.0f;
            }

            if(GetKey(VK_DOWN).bHeld) {
                fPlayerVelY = 6.0f;
            }

            if(GetKey(VK_LEFT).bHeld) {
                fPlayerVelX = -6.0f;
            }

            if(GetKey(VK_RIGHT).bHeld) {
                fPlayerVelX = 6.0f;
            }
        }

        fPlayerPosX = fPlayerPosX + fPlayerVelX * fElapsedTime; //fElapsedTime is time between last frame displayed on screen
        fPlayerPosY = fPlayerPosY + fPlayerVelY * fElapsedTime;



        fCameraPosX = fPlayerPosX;
        fCameraPosY = fPlayerPosY;

        //Draw level
        int nTileWidth = 16;
        int nTileHeight = 16;
        int nVisibleTilesX = ScreenWidth() / nTileWidth;
        int nVisibleTilesY = ScreenHeight() / nTileHeight;

        //Calculate Top-Leftmost visible tile (at 0,0)
        float fOffsetX = fCameraPosX - (float)nVisibleTilesX / 2.0f;
        float fOffsetY = fCameraPosY - (float)nVisibleTilesY / 2.0f;

        //Clamp camera to game bounderies (effectively stops camera movement at bounderies)
        //For left side
        if(fOffsetX < 0) fOffsetX = 0;
        if(fOffsetY < 0) fOffsetY = 0;
        //For right side
        if(fOffsetX > nLevelWidth - nVisibleTilesX) fOffsetX = nLevelWidth - nVisibleTilesX;
        if(fOffsetY > nLevelHeight - nVisibleTilesY) fOffsetY = nLevelHeight - nVisibleTilesY;

        //Draw visible tile map
        for(int x = 0; x < nVisibleTilesX; x++) {
            for(int y = 0; y < nVisibleTilesY; y++) {
                wchar_t sTileID = GetTile(x + fOffsetX, y + fOffsetY);

                switch(sTileID) {
                case L'.': //Sky
                    Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_CYAN);
                    break;
                case L'#':
                    Fill(x * nTileWidth, y * nTileHeight, (x + 1) * nTileWidth, (y + 1) * nTileHeight, PIXEL_SOLID, FG_RED);
                    break;
                default:
                    break;
                }
            }
        }

        //Draw Player
        Fill((fPlayerPosX - fOffsetX) * nTileWidth, (fPlayerPosY - fOffsetY) * nTileHeight, PIXEL_SOLID, FG_GREEN);




        return true;
    }
};

int main() {
    OneLoneCoder_Platformer game;
    if(game.ConstructConsole(160, 120, 8, 8))
        game.Start();
    return 0;
}
