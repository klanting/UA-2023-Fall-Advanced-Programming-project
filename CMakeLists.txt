CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)
PROJECT(ProjectPacman)

set(controller
        src/logic/Controller/Controller.cpp
        src/logic/Controller/Controller.h
        src/logic/Controller/ControllerObserver.cpp
        src/logic/Controller/ControllerObserver.h
        src/logic/Controller/MovementController.cpp
        src/logic/Controller/MovementController.h

)

set(subjects
        src/logic/Subjects/Subject.cpp
        src/logic/Subjects/Subject.h
        src/logic/Subjects/EntityModel.cpp
        src/logic/Subjects/EntityModel.h
        src/logic/Subjects/Ghost.cpp
        src/logic/Subjects/Ghost.h
        src/logic/Subjects/Wall.cpp
        src/logic/Subjects/Wall.h
        src/logic/Subjects/Collectable.cpp
        src/logic/Subjects/Collectable.h
        src/logic/Subjects/Pacman.cpp
        src/logic/Subjects/Pacman.h
        src/logic/Subjects/Coin.cpp
        src/logic/Subjects/Coin.h
        src/logic/Subjects/Fruit.cpp
        src/logic/Subjects/Fruit.h
)

set(move_strategies
        src/logic/MoveStrategy/ModeManager.cpp
        src/logic/MoveStrategy/ModeManager.h
        src/logic/MoveStrategy/Mode.cpp
        src/logic/MoveStrategy/Mode.h
        src/logic/MoveStrategy/FearMode.cpp
        src/logic/MoveStrategy/FearMode.h
        src/logic/MoveStrategy/ChaseMode.cpp
        src/logic/MoveStrategy/ChaseMode.h
        src/logic/MoveStrategy/ControlMode.cpp
        src/logic/MoveStrategy/ControlMode.h
        src/logic/MoveStrategy/PassiveMode.cpp
        src/logic/MoveStrategy/PassiveMode.h)

set(logic
        ${subjects}
        ${controller}
        ${move_strategies}

        src/logic/World.cpp
        src/logic/World.h
        src/logic/Random.cpp
        src/logic/Random.h
        src/logic/Stopwatch.cpp
        src/logic/Stopwatch.h
        src/logic/LogicHandler.cpp
        src/logic/LogicHandler.h
        src/logic/Vector2D.cpp
        src/logic/Vector2D.h
)



set(view)


ADD_EXECUTABLE(ProjectPacman
        src/main.cpp
        ${logic}
        ${view}

)

set(CMAKE_INSTALL_PREFIX install)

install(TARGETS ProjectPacman
        DESTINATION ${CMAKE_INSTALL_PREFIX}
)