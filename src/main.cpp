#include "logic/Vector2D.h"
#include "logic/Random.h"
#include <iostream>
#include "logic/MoveStrategy/ChaseMode.h"
#include "logic/MoveStrategy/FearMode.h"
#include "logic/Stopwatch.h"
#include "logic/Subjects/Pacman.h"
#include "view/Game.h"
#include "logic/World/WFC/WFCWorldGenerator.h"
using namespace std;

int main(){
    //View::Game g{};

    Logic::WFC::WFCWorldGenerator w{};

    w.print();
    w.printKey();

    return 0;
}