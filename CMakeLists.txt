# --------------------------------------------------- #
#                     put-license                     #
#         Copyright (c) 2014 Mikhail Artemyev         #
#         http://code.google.com/p/put-license        #
#     See LICENSE.txt file for license information    #
# --------------------------------------------------- #

cmake_minimum_required(VERSION 2.8)


project(put-license)


# --- define and connect some important directories ---
set(CMAKE_PREFIX_PATH $ENV{HOME}/install)
set(INCLUDE_DIR ${CMAKE_PREFIX_PATH}/include)
set(LIB_DIR     ${CMAKE_PREFIX_PATH}/lib)
include_directories(${INCLUDE_DIR})
# -----------------------------------------------------


# --- boost ---
set(Boost_INCLUDE_DIR ${INCLUDE_DIR})
set(Boost_LIBRARY_DIR ${LIB_DIR})
find_package(Boost 1.55 COMPONENTS system filesystem REQUIRED)
# -------------


aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})

