cmake_minimum_required(VERSION 3.7)
project(Comet_raid)

set(CMAKE_CXX_STANDARD 17)

# Använd C++ 17.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# På skolans Linux-system finns två versioner av GCC. Se vilken som används:
if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/6.1.0.*"))
    set(CMAKE_CXX_COMPILER /sw/gcc-6.1.0/bin/g++)

    if (DEFINED ENV{SFML_ROOT})
        list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
    endif()
endif()

if (DEFINED ENV{LOADEDMODULES} AND ("$ENV{LOADEDMODULES}" MATCHES ".*prog/gcc/7.1.0.*"))
    set(CMAKE_CXX_COMPILER /sw/gcc-7.1.0/bin/g++)

    if (DEFINED ENV{SFML_ROOT})
        list(APPEND CMAKE_MODULE_PATH "$ENV{SFML_ROOT}/share/SFML/cmake/Modules")
    endif()
endif()

# Välj vilka delar av SFML som ska användas.
set(SFML_MODULES network graphics window system)

# Försök att hitta SFML genom att anropa 'FindSFML.cmake'.
find_package(SFML 2 COMPONENTS ${SFML_MODULES})
include_directories(${SFML_INCLUDE_DIR})

# Om det inte gick hoppas vi att det är installerat i alla fall.
if (NOT (${SFML_FOUND} STREQUAL "TRUE"))
    set(SFML_LIBRARIES "")
    foreach(i ${SFML_MODULES})
        list(APPEND SFML_LIBRARIES "sfml-${i}")
    endforeach(i)
endif()

# Ange källfiler, lägg till de filer som ni behöver!

set(SOURCE_FILES main.cpp DynamicObject.cpp DynamicObject.h State.cpp State.h GameState.cpp GameState.h Ship.cpp Ship.h IceBlock.cpp IceBlock.h Collision.cpp Collision.h Comet.cpp Comet.h StaticObject.cpp StaticObject.h Bomb.cpp Bomb.h BombSite.cpp BombSite.h Explosion.cpp Explosion.h Object.cpp Object.h WinState.cpp WinState.h MenuState.cpp MenuState.h Constants.cpp Constants.h Projectile.cpp Projectile.h PausMenuState.cpp PausMenuState.h)



# Säg till CMake att skapa en körbar fil som heter 'sfml'.
add_executable(sfml ${SOURCE_FILES})


# Länka med biblioteken som vi hittade tidigare.
target_link_libraries(sfml ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


