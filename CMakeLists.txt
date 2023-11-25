CMAKE_MINIMUM_REQUIRED(VERSION 3.22.1)
PROJECT(ProjectPacman)




set(logic
        src/logic/Subjects/Subject.cpp
        src/logic/Subjects/Subject.h)



set(view)


ADD_EXECUTABLE(ProjectPacman
        src/main.cpp
        ${logic}
        ${view}

)

