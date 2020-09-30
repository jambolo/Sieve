cmake_minimum_required (VERSION 3.10)
project(Sieve CXX)

option(BUILD_SHARED_LIBS "Build libraries as DLLs" FALSE)

set(SIEVE_INCLUDE_PATHS
    .
)

set(SIEVE_SOURCES
    Sieve.cpp
)
source_group(Sources FILES ${SIEVE_SOURCES})

add_executable(Sieve ${SIEVE_SOURCES})
target_include_directories(Sieve PRIVATE ${SIEVE_INCLUDE_PATHS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED ON CXX_EXTENSIONS OFF)
target_compile_definitions(Sieve
    PRIVATE
        -DNOMINMAX
        -DWIN32_LEAN_AND_MEAN
        -DVC_EXTRALEAN
        -D_CRT_SECURE_NO_WARNINGS
        -D_SECURE_SCL=0
        -D_SCL_SECURE_NO_WARNINGS
)
