cmake_minimum_required(VERSION 3.10)
project(app)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory( ${PROJECT_SOURCE_DIR}/src
SRC_LIST
)

add_executable(${PROJECT_NAME}
   ${SRC_LIST}
)