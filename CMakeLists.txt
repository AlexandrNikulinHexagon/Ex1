cmake_minimum_required(VERSION 3.10)

project(ip_filter VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
#include(${PROJECT_SOURCE_DIR}/cmake/conan.cmake)
#conan_cmake_run(
#  CONANFILE conanfile.txt
#  BASIC_SETUP
#  CMAKE_TARGETS # individual targets to link to
#  BUILD
#    missing 
#)
set(CMAKE_CXX_STANDARD 17)
#option(BUILD_TESTS "Build unittests" OFF)

#include_directories(${PROJECT_SOURCE_DIR})
#add_subdirectory(lib)
add_subdirectory(src)

#if(BUILD_TESTS)
#    add_subdirectory(tests)
#endif()

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
