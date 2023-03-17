# Copyright 2023 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.14...3.25)

project(rw_spinlock_test LANGUAGES CXX)

include(FetchContent)

function(fetch_boost_library name)

  FetchContent_Declare(boostorg_${name} GIT_REPOSITORY https://github.com/boostorg/${name} GIT_TAG master)
  FetchContent_MakeAvailable(boostorg_${name})

endfunction()

fetch_boost_library(core)
fetch_boost_library(assert)
fetch_boost_library(config)
fetch_boost_library(static_assert)
fetch_boost_library(throw_exception)
fetch_boost_library(smart_ptr)
fetch_boost_library(move)
fetch_boost_library(type_traits)

set(CMAKE_CXX_STANDARD 11)

include(CTest)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

link_libraries(Boost::smart_ptr Boost::core Threads::Threads)

add_executable(rw_spinlock_test rw_spinlock_test.cpp)
add_test(rw_spinlock_test rw_spinlock_test)

add_executable(rw_spinlock_test2 rw_spinlock_test2.cpp)
add_test(rw_spinlock_test2 rw_spinlock_test2)

add_executable(rw_spinlock_test3 rw_spinlock_test3.cpp)
add_test(rw_spinlock_test3 rw_spinlock_test3)
