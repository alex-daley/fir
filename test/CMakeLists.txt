include(FetchContent)

FetchContent_Declare(
    catch
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v2.13.0)

FetchContent_MakeAvailable(catch)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE fir)
