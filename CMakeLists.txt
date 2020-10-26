cmake_minimum_required(VERSION 3.1)

project(TryCI VERSION 1.0
        DESCRIPTION "I need to make coverage and valgrind"
        LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

# Добавление покрытия кода
if (CMAKE_BUILD_TYPE MATCHES Debug)
  include(CodeCoverage)
  append_coverage_compiler_flags()
  setup_target_for_coverage_gcovr_html(
    NAME coverage
    EXECUTABLE valgrind --leak-check=full --show-leak-kinds=all ctest
    BASE_DIRECTORY "${PROJECT_SOURCE_DIR}"
    EXCLUDE "build/*" "test/*" "src/main.c" "src/customer.c")
endif()

# enable_testing()

##
### Test definitions ###
##

configure_file(CMakeLists.txt.in
        googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
        ${CMAKE_BINARY_DIR}/googletest-build)

enable_testing()

add_subdirectory(test)

##
### Source definitions ###
##

include_directories("${PROJECT_SOURCE_DIR}/include")

file(GLOB sources
  "${PROJECT_SOURCE_DIR}/include/testy/*.h"
  "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(main ${sources})