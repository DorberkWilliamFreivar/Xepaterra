#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "raylib.h"
#include "rlImGui.h"
#include "imgui.h"

int randint(int below, int upper){
    static std::random_device rmc;
    static std::mt19937 random_machine(rmc());
    std::uniform_int_distribution<> filter_machine(below, upper);
    int rand_num = filter_machine(random_machine);
    return rand_num; 
}

enum class MobMovesets {
    MOVE_RIGHT_DOWN = 0,
    MOVE_RIGHT_UP = 1,
    MOVE_LEFT_DOWN = 2,
    MOVE_LEFT_UP = 3,
    MOVE_RIGHT = 4,
    MOVE_LEFT = 5,
    MOVE_DOWN = 6,
    MOVE_UP = 7,
};

enum class MobAction {
    RUN = 0,
    ATTACK = 1,
    BLEED = 2,
    DRINK = 3,
    EAT = 4,
    SLEEP = 5,  // soon, ill add it
    IN_GROUPS = 6,  // soon, ill add it
    BARK_SCREAM = 7, // soon, ill add it
};

// Env Nature
class Grass{
    public:
        std::string grass_file;
        Texture2D grass;
        Rectangle crop;
        Vector2 cor;
        int many_tiles_x;
        int many_tiles_y;
        Grass(int x, int y){
            grass_file = "assets/img/grass.png";
            grass = LoadTexture(grass_file.c_str());
            crop = {32, 0, 32, 32};
            cor = {0, 0};
            many_tiles_x = x;
            many_tiles_y = y;
        
        }
        ~Grass(){
            UnloadTexture(grass);
        }

       void draw(){
            cor.x = 0;
            cor.y = 0;
            
            for(int i=0; i<=many_tiles_x; i++){
                for(int j=0;j<=many_tiles_y; j++){
                    DrawTextureRec(grass, crop, cor, WHITE);
                    cor.y += 32;
                }
                cor.x += 32;
                cor.y = 0;
            }  
       } 
};

class Pond{
    public:
    std::string pond_file;
    Texture2D pond;
    Rectangle crop;
    Rectangle size_up;
    Vector2 cor;
    float timer_pond;
    Pond(){
        pond_file = "assets/img/pond.png";
        pond = LoadTexture(pond_file.c_str());
        crop = {0, 0, 96, 96};
        size_up = {0, 0, 192, 192};
        cor = {0, 0};
        timer_pond = 0.0f;
    }
    ~Pond(){
        UnloadTexture(pond);
    }

    void draw(){
        // DrawTextureRec(pond, crop, cor, WHITE);
        DrawTexturePro(pond, crop, size_up, cor, 0.0f, WHITE);
        timer_pond += GetFrameTime();

        if (timer_pond >= 0.50f) {
            timer_pond = 0.0;

            crop.x += 96;
            if (crop.x >= 673) {crop.x = 0;}
        }
    }
};

// Mobs
class Wolf{
    public:
        std::string wolf_file;
        Texture2D wolf;
        Rectangle crop;
        Vector2 cor;
        MobMovesets move_state;
        float timer_wolf;
        int dx;
        int dy;
        Wolf(){
            wolf_file = "assets/img/wolf.png";
            wolf = LoadTexture(wolf_file.c_str());
            crop = {0, 0, -32, 32};
            cor = {0, 0};
            timer_wolf = 0.0f;
            move_state = static_cast<MobMovesets>(::randint(0, 7));
        }
        ~Wolf(){
            UnloadTexture(wolf);
        }

        template<typename Mob_Type>
        void attack(Mob_Type* Mob){
            // interaksi dgn mob lain
        }
        
        void checkStatus(){
            // check current statue
        }

        void dead(){
            // status mati
        }

        void drink(){
            // interaksi dengan air
        }

        void sleep(){
            // turu
        }
        
        
        void draw(){
            DrawTextureRec(wolf, crop, cor, WHITE);
            timer_wolf += GetFrameTime();
            
            if (timer_wolf >= 0.15f) {
                timer_wolf = 0.0f;
                switch (move_state) {
                    case MobMovesets::MOVE_RIGHT_DOWN: dy = 1; dx = 1; break;
                    case MobMovesets::MOVE_RIGHT_UP: dy = -1; dx = 1; break;
                    case MobMovesets::MOVE_LEFT_DOWN: dy = 1; dx = -1; break;
                    case MobMovesets::MOVE_LEFT_UP: dy = -1; dx = -1; break;
                    case MobMovesets::MOVE_RIGHT: dy = 0; dx = 1; break;
                    case MobMovesets::MOVE_LEFT: dy = 0; dx = -1; break;
                    case MobMovesets::MOVE_DOWN: dy = 1; dx = 0; break;
                    case MobMovesets::MOVE_UP: dy = -1; dx = 0; break;
                }
                cor.x += dx; 
                cor.y += dy; 
                crop.x += 32;
                //  inverse img
                if (dx == 1) {crop.width = -32;} 
                else if (dx == -1) {crop.width = 32;}

                // reset img
                if (crop.x >= 160) {crop.x = 0;}

                // reset x
                if (cor.x >= 1920) {cor.x = 0;} 
                else if (cor.x <= 0) {cor.x = 1920;}
                
                // reset y
                if (cor.y >= 1080) {cor.y = 0;} 
                else if (cor.y <= 0) {cor.y = 1080;}
            }
        }
};

class Sheep{
    public:
        std::string sheep_file;
        Texture2D sheep;
        Rectangle crop;
        Vector2 cor;
        MobMovesets move_state;
        float timer_sheep;
        int dx;
        int dy;
        Sheep(){
            sheep_file = "assets/img/sheep.png";
            sheep = LoadTexture(sheep_file.c_str());
            crop = {0, 0, -32, 32};
            cor = {67, 67};
            timer_sheep = 0.0f;
            move_state = static_cast<MobMovesets>(::randint(0, 7));
        }
        ~Sheep(){
            UnloadTexture(sheep);
        }

        void draw(){
            DrawTextureRec(sheep, crop, cor, WHITE);
            timer_sheep += GetFrameTime();
            
            if (timer_sheep >= 0.15f) {
                timer_sheep = 0.0f;
                switch (move_state) {
                    case MobMovesets::MOVE_RIGHT_DOWN: dy = 1; dx = 1; break;
                    case MobMovesets::MOVE_RIGHT_UP: dy = -1; dx = 1; break;
                    case MobMovesets::MOVE_LEFT_DOWN: dy = 1; dx = -1; break;
                    case MobMovesets::MOVE_LEFT_UP: dy = -1; dx = -1; break;
                    case MobMovesets::MOVE_RIGHT: dy = 0; dx = 1; break;
                    case MobMovesets::MOVE_LEFT: dy = 0; dx = -1; break;
                    case MobMovesets::MOVE_DOWN: dy = 1; dx = 0; break;
                    case MobMovesets::MOVE_UP: dy = -1; dx = 0; break;
                }
                cor.x += dx; 
                cor.y += dy; 
                crop.x += 32;
                //  inverse img
                if (dx == 1) {crop.width = -32;} 
                else if (dx == -1) {crop.width = 32;}

                // reset img
                if (crop.x >= 160) {crop.x = 0;}

                // reset x
                if (cor.x >= 1920) {cor.x = 0;} 
                else if (cor.x <= 0) {cor.x = 1920;}
                
                // reset y
                if (cor.y >= 1080) {cor.y = 0;} 
                else if (cor.y <= 0) {cor.y = 1080;}
            }
        }
};

template <typename Type_Mob>
void RemoveTextures(std::vector<Type_Mob*>& Mobs){
    for(int i=0;i<Mobs.size();i++){
        delete Mobs[i];
    }
    Mobs.clear();
}

template <typename Type_Mob>
void summonMobs(int manys, std::vector<Type_Mob*>& Mobs){
    for(int i=0; i<manys; i++){
        Mobs.push_back(new Type_Mob());
        int rand_num1 = randint(1, 1000);
        int rand_num2 = randint(1, 1000);
        Mobs[i]->cor.x = rand_num1;
        Mobs[i]->cor.y = rand_num2;
    }
}

template <typename Type_Mob>
void drawAllMobs(std::vector<Type_Mob*>& Mobs){
    for(int i=0; i<Mobs.size(); i++){
        Mobs[i]->draw();
    }
}


template <typename TM1, typename TM2>
void checkCollisions(std::vector<TM1*>& Mobs1, std::vector<TM2*>& Mobs2){
    for(int i = 0; i<Mobs1.size(); i++) {
        for(int j = 0; j<Mobs2.size(); j++) {
            if (Mobs1[i]->cor.x == Mobs2[j]->cor.x + 32) {
                int rand_state = randint(4, 7);
                Mobs1[i]->move_state = static_cast<MobMovesets>(rand_state);
            }
        }
    }
}

void closeAllTasks(){
    rlImGuiShutdown();
    CloseWindow();
}

int main() {
    int w_layer = 1920;
    int h_layer = 1080;
    int many_tiles_x = w_layer / 32;
    int many_tiles_y = h_layer / 32;
    std::vector<Sheep*> Sheepys;
    std::vector<Wolf*> Wolfys;
    
    InitWindow(w_layer, h_layer, "New Genesis - Simulation of Life");
    ToggleFullscreen();
    SetTargetFPS(60);
    rlImGuiSetup(true);
    Color Random = {255, 0, 0, 255};

    Pond pond;
    Grass grass(many_tiles_x, many_tiles_y);
    summonMobs(20, Sheepys);
    summonMobs(20, Wolfys);

    Camera3D tes_cam;
    UpdateCamera(&tes_cam, CAMERA_FREE);
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        grass.draw();
        pond.draw();
        drawAllMobs(Sheepys);
        drawAllMobs(Wolfys);
        // DrawPixel(67, 67, Random);
        // DrawLine(67, 67, 100, 100, Random);
        // DrawCircle(67, 67, 10.5, Random);
        checkCollisions(Sheepys, Wolfys);

        rlImGuiBegin();
        rlImGuiEnd();
        EndDrawing();
    }

    IsKeyPressed(KEY_A);

    RemoveTextures(Sheepys);
    RemoveTextures(Wolfys);
    closeAllTasks();
    return 0;
}