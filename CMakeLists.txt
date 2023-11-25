CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)
PROJECT(ProjectPacman)

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

set(logic
        src/logic/World.cpp
        src/logic/World.h
        ${subjects}
        src/logic/Random.cpp
        src/logic/Random.h
        src/logic/Stopwatch.cpp
        src/logic/Stopwatch.h
        src/logic/LogicHandler.cpp
        src/logic/LogicHandler.h
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