#include "logic/Vector2D.h"
#include "logic/Random.h"
#include <iostream>
#include "logic/MoveStrategy/ChaseMode.h"
#include "logic/MoveStrategy/FearMode.h"
using namespace std;

int main(){

    Logic::Move::ChaseMode c;
    Logic::Move::FearMode f;

    int a = 0;
    for (int i=0; i<100; i++){
        Logic::Vector2D v = f.getDirection(Logic::Vector2D{1, 1}, {Logic::Vector2D{1, 0}, Logic::Vector2D{0, -2}});
        if (abs(v.getLength() -1) < 0.01){
            a += 1;
        }

    }
    std::cout << a << std::endl;
    return 0;
}