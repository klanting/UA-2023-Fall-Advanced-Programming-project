CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)
PROJECT(ProjectPacman)

IF (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET (CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/installed" CACHE PATH "default install path" FORCE)
ENDIF()


FIND_PACKAGE(SFML 2 COMPONENTS system window graphics)
INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})

set(controller
        src/logic/Controller/Controller.cpp
        src/logic/Controller/Controller.h
        src/logic/Controller/MovementController.cpp
        src/logic/Controller/MovementController.h

)

set(states
        src/view/States/StateManager.cpp
        src/view/States/StateManager.h
        src/view/States/State.cpp
        src/view/States/State.h
        src/view/States/MenuState.cpp
        src/view/States/MenuState.h
        src/view/States/LevelState.cpp
        src/view/States/LevelState.h
        src/view/States/PausedState.cpp
        src/view/States/PausedState.h
        src/view/States/VictoryState.cpp
        src/view/States/VictoryState.h
        src/view/States/GameOverState.cpp
        src/view/States/GameOverState.h
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
        src/logic/Subjects/Intersection.cpp
        src/logic/Subjects/Intersection.h
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
        src/logic/AbstractFactory.cpp
        src/logic/AbstractFactory.h
        src/logic/Observer.cpp
        src/logic/Observer.h
        src/logic/Score.cpp
        src/logic/Score.h
)



set(view
        ${states}
        src/view/Game.cpp
        src/view/Game.h
        src/view/ConcreteFactory.cpp
        src/view/ConcreteFactory.h
        src/view/EntityView/EntityView.cpp
        src/view/EntityView/EntityView.h
        src/view/EntityView/PacmanView.cpp
        src/view/EntityView/PacmanView.h
        src/view/EntityView/GhostView.cpp
        src/view/EntityView/GhostView.h
        src/view/EntityView/CoinView.cpp
        src/view/EntityView/CoinView.h
        src/view/EntityView/FruitView.cpp
        src/view/EntityView/FruitView.h
        src/view/EntityView/WallView.cpp
        src/view/EntityView/WallView.h
        src/view/Camera.cpp
        src/view/Camera.h
        src/view/RenderWindowSingleton.cpp
        src/view/RenderWindowSingleton.h
        src/view/Scoreboard.cpp
        src/view/Scoreboard.h
        src/view/UIObjects/Button.cpp
        src/view/UIObjects/Button.h
        src/view/UIObjects/StartButton.cpp
        src/view/UIObjects/StartButton.h
        src/view/EntityView/IntersectionView.cpp
        src/view/EntityView/IntersectionView.h
        src/view/UIObjects/UIObject.cpp
        src/view/UIObjects/UIObject.h)


ADD_EXECUTABLE(ProjectPacman
        src/main.cpp
        ${logic}
        ${view}

)

set(CMAKE_INSTALL_PREFIX install)

TARGET_LINK_LIBRARIES(ProjectPacman sfml-system sfml-graphics sfml-window)

install(TARGETS ProjectPacman
        DESTINATION ${CMAKE_INSTALL_PREFIX}
)