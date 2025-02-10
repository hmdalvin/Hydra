cmake_minimum_required(VERSION 3.10)
project(Hydra C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

set(SRC_DIR src)
set(INC_DIR include)

file(GLOB SOURCES "${SRC_DIR}/*.c")

add_executable(program ${SOURCES})

target_include_directories(program PRIVATE ${INC_DIR} ${GTK4_INCLUDE_DIRS})

target_link_libraries(program PRIVATE ${GTK4_LIBRARIES})
