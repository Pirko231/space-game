cmake_minimum_required(VERSION 3.27)
project(CMakeSFMLProject LANGUAGES CXX)

# Ustawienie katalogu dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Określenie wersji builda (Debug domyślnie)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 🟢 Ustawienie ścieżek do SFML (zmień na swoją lokalizację SFML)
set(SFML_ROOT "C:/SFML/SFML-3.0.0")
set(CMAKE_PREFIX_PATH "C:/SFML/SFML-3.0.0")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src/perf)
include_directories(${CMAKE_SOURCE_DIR}/src/utils)
include_directories(${CMAKE_SOURCE_DIR}/src/game/interfaces)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game/gameObjects)
include_directories(${CMAKE_SOURCE_DIR}/src/game/playerUI)


# Znalezienie (wersja 2.6.1)
#find_package(SFML 2.6.1 COMPONENTS system window graphics audio network REQUIRED)
find_package(SFML 3.0.0 COMPONENTS System Window Graphics Audio Network REQUIRED)


set(SFML_LIBS SFML::Graphics SFML::Window SFML::System SFML::Audio SFML::Network)


set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")

file(COPY "${RESOURCES_DIR}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Tworzenie pliku wykonywalnego
add_executable(main 
    src/main.cpp 
    src/program.cpp 

    src/game/playerUI/player.cpp
    src/game/playerUI/bar.cpp
    src/game/playerUI/radar.cpp
    src/game/playerUI/missilePicker.cpp
    src/game/playerUI.cpp

    src/game/gameObjects/managers/asteroidManager.cpp
    src/game/gameObjects/hitChecker.cpp
    src/game/gameObjects/managers/missileManager.cpp

    src/game/gameObjects/missiles/laser.cpp
    src/game/gameObjects/missiles/rocket.cpp
    src/game/gameObjects/missiles/mine.cpp


    src/perf/speedTracker.cpp
)

#add_compile_definitions(MEMTRACKER)
#add_compile_definitions(SPEEDTRACKER)
#add_compile_definitions(DEVINFO)

if(NOT MSVC)
	target_compile_options(main PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(main PRIVATE -Wno-unused-parameter)
endif()

# Ustawienie wersji standardu C++
target_compile_features(main PRIVATE cxx_std_20)

# Linkowanie SFML
target_link_libraries(main PRIVATE ${SFML_LIBS})
