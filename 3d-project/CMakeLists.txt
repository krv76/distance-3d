FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)

set (sources
  "src/point_3d.cpp"
  "src/vector_3d.cpp"
  "src/segment_3d.cpp"
  "src/distance.cpp"
)

add_executable(
    tests
    "tests/gtests_main.cpp"
    "tests/basic_tests.cpp"
    "tests/point_3d_tests.cpp"
    "tests/distance_tests.cpp"
    ${sources}
)

target_link_libraries(tests gtest_main)

add_executable(
    app_main
    "src/app_main.cpp"
)

target_link_libraries(app_main -lm)

include(GoogleTest)

gtest_discover_tests(tests)
