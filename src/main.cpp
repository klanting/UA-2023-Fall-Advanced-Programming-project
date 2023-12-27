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

    Logic::WFC::WFCWorldGenerator w{};

    w.print(true);
    w.printKey(true);
    w.printKey(false);
    w.exportData();
    w.load();

    View::Game g{};


    return 0;
}