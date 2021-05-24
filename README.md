# Comet raids
A 2D game in C++ and SFML

////////////////////////////////
// Installationsinstruktioner //
////////////////////////////////

Kompilera med 'cmake . && make'
Ovan kommando skapar en körbar fil som heter sfml
Programmet körs sedan med kommando ./sfml

Verifiera att images och textFiles mapparna ligger i sama katalog som den körbara filen som görs av make.


////////////////
// Kontroller //
////////////////

rotation styrs av Q ,E tagenterna
acceleration frammåt styrs av W
acceleration bakåt styrs av S
acceleration i sidled styrs av A och D respektive.

/////////////////
// Filstruktur //
/////////////////
.
├── Bomb.cpp
├── Bomb.h
├── BombSite.cpp
├── BombSite.h
├── cmake-build-debug
│   ├── CMakeCache.txt
│   ├── CMakeFiles
│   │   ├── 3.15.3
│   │   │   ├── CMakeCCompiler.cmake
│   │   │   ├── CMakeCXXCompiler.cmake
│   │   │   ├── CMakeDetermineCompilerABI_C.bin
│   │   │   ├── CMakeDetermineCompilerABI_CXX.bin
│   │   │   ├── CMakeSystem.cmake
│   │   │   ├── CompilerIdC
│   │   │   │   ├── a.out
│   │   │   │   └── CMakeCCompilerId.c
│   │   │   └── CompilerIdCXX
│   │   │       ├── a.out
│   │   │       └── CMakeCXXCompilerId.cpp
│   │   ├── clion-environment.txt
│   │   ├── clion-log.txt
│   │   ├── cmake.check_cache
│   │   ├── CMakeDirectoryInformation.cmake
│   │   ├── CMakeOutput.log
│   │   ├── Makefile2
│   │   ├── Makefile.cmake
│   │   ├── progress.marks
│   │   ├── sfml.dir
│   │   │   ├── build.make
│   │   │   ├── cmake_clean.cmake
│   │   │   ├── CXX.includecache
│   │   │   ├── DependInfo.cmake
│   │   │   ├── depend.internal
│   │   │   ├── depend.make
│   │   │   ├── flags.make
│   │   │   ├── link.txt
│   │   │   └── progress.make
│   │   └── TargetDirectories.txt
│   ├── cmake_install.cmake
│   ├── Comet_raid.cbp
│   ├── images
│   │   ├── Bana1.png
│   │   ├── bomb.png
│   │   ├── bombSiteGreen.png
│   │   ├── bombSiteRed.png
│   │   ├── bombSites.png
│   │   ├── explosion_4.png
│   │   ├── IceBlock_rect.png
│   │   ├── IceBlock_square.png
│   │   ├── INVASION2000.TTF
│   │   ├── pizzadudedotdk.txt
│   │   └── ship0.png
│   ├── Makefile
│   ├── sfml
│   └── textFiles
│       └── LEVELS.txt
├── CMakeLists.txt
├── Collision.cpp
├── Collision.h
├── Comet.cpp
├── Comet.h
├── Constants.cpp
├── Constants.h
├── DynamicObject.cpp
├── DynamicObject.h
├── Explosion.cpp
├── Explosion.h
├── GameState.cpp
├── GameState.h
├── IceBlock.cpp
├── IceBlock.h
├── main.cpp
├── MenuState.cpp
├── MenuState.h
├── Object.cpp
├── Object.h
├── PausMenuState.cpp
├── PausMenuState.h
├── Projectile.cpp
├── Projectile.h
├── README.md
├── Ship.cpp
├── Ship.h
├── State.cpp
├── State.h
├── StaticObject.cpp
├── StaticObject.h
├── WinState.cpp
└── WinState.h

8 directories, 81 files
