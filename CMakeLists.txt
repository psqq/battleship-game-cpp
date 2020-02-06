# CMakeList.txt: проект CMake для CMakeProject1; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
