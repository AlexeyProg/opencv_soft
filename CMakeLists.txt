cmake_minimum_required(VERSION 3.25.2)
project(OpenCVExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/Users/sokol/Qt/6.5.1/macos")

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

include_directories(${Qt6Widgets_INCLUDE_DIRS})

set(CMAKE_AUTOMOC ON)
# qt_wrap_cpp(MOC_Files graphics/application.h)
# add_library(OpenCVExample SHARED ${MOC_Files})


# Найдем пакет OpenCV
find_package(OpenCV REQUIRED)

# Включим заголовочные файлы OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})

# Создадим исполняемый файл из main.cpp
add_executable(main main.cpp graphics/application.h graphics/application.cpp obj/detect.h obj/detect.cpp)

# Свяжем библиотеки OpenCV с исполняемым файлом
target_link_libraries(main PRIVATE ${OpenCV_LIBS} Qt6::Core Qt6::Widgets)
