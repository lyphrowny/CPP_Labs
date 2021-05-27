cmake_minimum_required(VERSION 3.19)
project(Gems)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_PREFIX_PATH "./qt")
set(CMAKE_AUTOMOC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)


SET(GEMS gem/base_gem/hdr/base_gem.h gem/base_gem/src/base_gem.cpp gem/swap/hdr/swap.h gem/swap/src/swap.cpp
        gem/bomb/hdr/bomb.h gem/bomb/src/bomb.cpp gem/recolor/hdr/recolor.h gem/recolor/src/recolor.cpp)
SET(MARKER marker/hdr/marker.h)
SET(TILE tile/hdr/tile.h tile/src/tile.cpp)
SET(FIELD field/hdr/field.h field/src/field.cpp)

add_executable(${PROJECT_NAME} main.cpp ${GEMS} ${TILE} ${MARKER} ${FIELD})

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
