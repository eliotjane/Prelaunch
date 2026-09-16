cmake_minimum_required(VERSION 3.16)

project(V1rocket)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

include_directories(include)

add_executable(V1rocket
    src/main.cc
    src/RocketDetectorConstruction.cc
    src/Falcon9FairingDetectorConstructionWithWeapon.cc
    src/Falcon9FairingDetectorConstruction.cc
    src/PrimaryGeneratorAction.cc
)

target_link_libraries(V1rocket
    ${Geant4_LIBRARIES}
)

