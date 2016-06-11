link_directories(${PROJECT_SOURCE_DIR}/src)
add_executable(Correctness test_correctness.cpp)
target_link_libraries(Correctness ad-hoc)
