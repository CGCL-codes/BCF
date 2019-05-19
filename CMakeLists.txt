cmake_minimum_required(VERSION 3.8)
project(cuckoofilter_master)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        benchmarks/bulk-insert-and-query.cc
        benchmarks/conext-figure5.cc
        benchmarks/conext-table3.cc
        benchmarks/random.h
        benchmarks/timing.h
        example/test.cc
        src/bitsutil.h
        src/cuckoofilter.h
        src/debug.h
        src/hashutil.cc
        src/hashutil.h
        src/packedtable.h
        src/permencoding.h
        src/printutil.cc
        src/printutil.h
        src/simd-block.h
        src/singletable.h)

add_executable(cuckoofilter_master ${SOURCE_FILES})