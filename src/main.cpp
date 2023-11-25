#include "logic/Vector2D.h"
#include "logic/Random.h"
#include <iostream>
#include "logic/MoveStrategy/ChaseMode.h"
#include "logic/MoveStrategy/FearMode.h"
#include "logic/Stopwatch.h"
#include "logic/Subjects/Pacman.h"
using namespace std;

int main(){

    Logic::Move::ChaseMode c;
    Logic::Move::FearMode f;
    using namespace Logic;
    Pacman p{Vector2D{0,0}};

    int a = 0;
    for (int i=0; i<100; i++){
        f.makeDirection(Logic::Vector2D{1, 1}, {Logic::Vector2D{1, 0}, Logic::Vector2D{0, -2}});
        if (abs(f.getDirection().getLength() -1) < 0.01){
            a += 1;
        }

    }

    p.move();

    p.move();
    std::cout << a << std::endl;
    return 0;
}