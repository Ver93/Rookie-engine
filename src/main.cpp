#include <iostream>
#include "engine.h"
#include "uci.h"

int main(){
    Engine::initialize();
    UCI::run();
    return 0;
}