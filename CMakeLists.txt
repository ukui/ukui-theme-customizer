cmake_minimum_required(VERSION 3.0)
project(UKUIThemeCustomizer)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
# Instruct CMake to create code from Qt designer ui files
set(CMAKE_AUTOUIC ON)

set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(ukuithemecustomizer_SRC
  src/iniThemeTemplate.qrc
  src/main.cpp
)


# Tell CMake to create the helloworld executable
add_executable(ukuithemecustomizer ${ukuithemecustomizer_SRC})

add_subdirectory(src/packagecreator/)
add_subdirectory(src/ukuithemecustomizerwindow/)
add_subdirectory(src/logger/)
add_subdirectory(src/ukuithemeelement/)

target_link_libraries(ukuithemecustomizer
   Qt5::Core
   Qt5::Widgets
   packagecreator
   ukuithemecustomizerwindow
   logger
)

# Install the executable
install(TARGETS ukuithemecustomizer DESTINATION bin)
