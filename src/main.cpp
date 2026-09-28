#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "rlImGui.h"
#include "imgui.h"

#include "raylib.h"
#include "raymath.h"
#include "main.h"

int randint(int below, int upper){
    static std::random_device rmc;
    static std::mt19937 random_machine(rmc());
    std::uniform_int_distribution<> filter_machine(below, upper);
    int rand_num =  filter_machine(random_machine);
    return rand_num;
}

typedef struct {
    Vector3 position;
    Vector3 velocity;
    bool isGrounded;
} Body;

class Player{
    public:
        const int MAX_HP = 100;
        std::string NAME_CHAR;
        Body body = {0};

        Player(std::string InputName){
            NAME_CHAR = InputName;
        }

        void move(){
            //under construction
        }
};

class Game{
    public:
        const int SCREEN_WIDTH = 1000;
        const int SCREEN_HEIGHT = 900;
        const std::string TITLE = "Xepaterra - DevVersion";

        Game(Camera* camera, Player* player){
           camera->position = (Vector3){
            player->body.position.x,
            player->body.position.y,
            player->body.position.z,
           };
        }

        void initGame(){
            InitWindow(SCREEN_WIDTH, SCREEN_WIDTH, TITLE.c_str());
        }
};


int main() {
    // need camera
    // need body
    // need math
    // need somebody that i love, but unfortunately she leaved me :c
    // and remember to refactoring this sometimes
    // and.. arange the code cleanly with its own code file (.h and .cpp)

    return 0;
}






























// FREE PALESTINE, FUCK ISRAEL