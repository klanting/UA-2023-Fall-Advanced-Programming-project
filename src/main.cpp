#include "logic/Vector2D.h"
#include "logic/Random.h"
#include <iostream>
using namespace std;

int main(){
    std::shared_ptr<Logic::Random> r = Logic::Random::getInstance();
    std::cout << r->getRandomIndex(0, 1) << std::endl;

    return 0;
}