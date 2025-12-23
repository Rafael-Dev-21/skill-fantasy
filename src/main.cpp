#include <raylib.h>
#include <raymath.h>

#include <cmath>

struct Cell {
  uint32_t fg;
  uint32_t bg;
  char ch;
};

struct Input {
  uint8_t key;
  uint8_t mods;
};

enum {
  W=80,
  H=25,
  M=128
};

static Cell cells[H][W];

void gfx_setCell(int x, int y, char ch, uint32_t fg, uint32_t bg);

Vector2 IsoMapToScreen(Vector2 map, float scaleX, float scaleY)
{
    return Vector2{
        (map.x - map.y)*(scaleX/2),
        (map.x + map.y)*(scaleY/2)
    };
}

Vector2 IsoScreenToMap(Vector2 screen, float scaleX, float scaleY)
{
    return Vector2{
        (screen.x/(scaleX/2) + screen.y/(scaleY/2))/2,
        (screen.y/(scaleY/2) - screen.x/(scaleX/2))/2
    }
}

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 720;
    const float tileWidth = 32.0f;
    const float tileHeight = 16.0f;
    //const Vector2 tileDims{tileWidth, tileHeight};

    const float scale = static_cast<float>(screenHeight)/240.0f;

    const float viewWidthInTiles = (static_cast<float>(screenWidth)/scale)/tileWidth*4;
    const float viewHeightInTiles = (static_cast<float>(screenHeight)/scale)/tileHeight*4;

    int cTiles = static_cast<int>(std::ceil(viewWidthInTiles)) + 3;
    cTiles |= 1;
    int rTiles = static_cast<int>(std::ceil(viewHeightInTiles)) + 3;
    rTiles |= 1;

    InitWindow(screenWidth, screenHeight, "Skill Fantasy v0.4.0");
    SetTargetFPS(60);

    Texture player = LoadTexture("./data/commoner.png");
    if (player.id == 0) {
        Image img = GenImageColor(32, 32, RED);
        player = LoadTextureFromImage(img);
        UnloadImage(img);

        printf("Aviso: não foi possivel carregar ./data/commoner.png - usando fallback.\n");
    }
    SetTextureFilter(player, TEXTURE_FILTER_POINT);
    Texture grass = LoadTexture("./data/iso-grass.png");
    if (grass.id == 0) {
        Image img = GenImageColor(32, 16, LIME);
        grass = LoadTextureFromImage(img);
        UnloadImage(img);

        printf("Aviso: não foi possivel carregar ./data/iso-grass.png - usando fallback.\n");
    }
    SetTextureFilter(grass, TEXTURE_FILTER_POINT);

    Vector2 playerPos{100, 100};
    const float playerspeed = 8.0f;

    Camera2D cam{};
    cam.zoom = scale;
    cam.offset = Vector2{screenWidth*0.5f, screenHeight*0.5f};

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();
        const float playervel = playerspeed * dt;
        Vector2 dir{0,0};
        if (IsKeyDown(KEY_H)) {
            dir.x-=1;
        }
        if (IsKeyDown(KEY_L)) {
            dir.x+=1;
        }
        if (IsKeyDown(KEY_K)) {
            dir.y-=1;
        }
        if (IsKeyDown(KEY_J)) {
            dir.y+=1;
        }
        //dir = IsoScreenToMap(dir, 1, 1);
        playerPos += dir * playervel;
        cam.target = IsoMapToScreen(playerPos, tileWidth, tileHeight);

        //const float halfViewW = (screenWidth / (2.0f * cam.zoom));
        const float halfViewH = (screenHeight / (0.5f * cam.zoom));
        const float viewLeft = cam.target.x;
        const float viewTop  = cam.target.y - halfViewH;

        //const Vector2 startScreen{viewLeft, viewTop};
        const Vector2 startScreenFloored{
            viewLeft*2 - std::floor(viewLeft/tileWidth)*tileWidth - tileWidth,
            viewTop*2 - std::floor(viewTop/tileHeight)*tileHeight - tileHeight
        };
        const auto startMap = IsoScreenToMap(startScreenFloored, tileWidth, tileHeight);

        BeginDrawing();
        ClearBackground(RAYWHITE);
            BeginMode2D(cam);
                for (int tj = 0; tj < rTiles; tj++) {
                    for (int ti = 0; ti < cTiles; ti++) {
                        Vector2 tilePos{
                            static_cast<float>(ti),
                            static_cast<float>(tj)
                        };
                        Vector2 screenPos = IsoMapToScreen(tilePos, tileWidth, tileHeight);
                        tilePos = tilePos + startMap;
                        screenPos = screenPos + startScreenFloored;
                        //const int tileX = static_cast<int>(std::floor(tilePos.x));
                        //const int tileY = static_cast<int>(std::floor(tilePos.y));

                        //const int parity = (tileX&1)^(tileY&1);
                        //if (parity) continue;
                        
                        DrawTextureV(grass, screenPos, WHITE);
                    }
                }
                DrawTextureV(player, Vector2SubtractValue(IsoMapToScreen(playerPos, tileWidth, tileHeight), 16), WHITE);
            EndMode2D();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
