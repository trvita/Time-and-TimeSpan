add_library(mytime
    time/time.cpp
    time/time.hpp
)
target_include_directories(mytime
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/time
)