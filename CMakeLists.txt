cmake_minimum_required(VERSION 2.8)
project (kmeans)
find_package(Boost REQUIRED unit_test_framework)

include_directories("${PROJECT_SOURCE_DIR}/src")
include(CTest)
enable_testing()

option (PROFILE OFF)
option (NOINLINE "force no inlining for profiling" OFF)
option (VECTOR OFF)
option (TEST OFF)

#if (DEBUG)
#    set (OPTIMIZE_FLAG  "-g -DDEBUG")
#else()
#    set (OPTIMIZE_FLAG  "-g -O3")
#endif(DEBUG)

if (PROFILE)
    set (PROFILE_FLAG  "-pg")
endif()

if (NOINLINE)
    set (PROFILE_FLAG  "-pg -fno-inline -fno-elide-constructors") 
endif()

if (VECTOR)
    set (VECTOR_FLAG  "-g -m64 -O3 -msse4 -ftree-vectorize") 
endif()

set (MY_COMPILE_FLAGS "-Wall ${OPTIMIZE_FLAG} ${PROFILE_FLAG} ${VECTOR_FLAG}")

add_subdirectory(src)
#add_subdirectory(test)
