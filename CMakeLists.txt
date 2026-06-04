cmake_minimum_required(VERSION 3.10)
project(vmac)

set(CMAKE_VERBOSE_MAKEFILE OFF )

set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")

find_package(Doxygen 1.9 REQUIRED)

add_subdirectory(src)
add_subdirectory(tests EXCLUDE_FROM_ALL)
add_subdirectory(docs EXCLUDE_FROM_ALL)

file(GLOB_RECURSE format_xxfiles
    ${PROJECT_SOURCE_DIR}/src/asm/*.c
    ${PROJECT_SOURCE_DIR}/src/asm/*.h
    ${PROJECT_SOURCE_DIR}/src/common/*.c
    ${PROJECT_SOURCE_DIR}/src/common/*.h
    ${PROJECT_SOURCE_DIR}/src/disasm/*.c
    ${PROJECT_SOURCE_DIR}/src/disasm/*.h
    ${PROJECT_SOURCE_DIR}/src/hexdump/*.c
    ${PROJECT_SOURCE_DIR}/src/hexdump/*.h
    ${PROJECT_SOURCE_DIR}/src/macros/*.c
    ${PROJECT_SOURCE_DIR}/src/macros/*.h
    ${PROJECT_SOURCE_DIR}/src/vm/*.c
    ${PROJECT_SOURCE_DIR}/src/vm/*.h
    ${PROJECT_SOURCE_DIR}/src/vm_common/*.c
    ${PROJECT_SOURCE_DIR}/src/vm_common/*.h
)

add_custom_target(format
    COMMENT "Format the source code"
    COMMAND clang-format --verbose -i ${format_xxfiles}
)

add_custom_target(test
    COMMENT "Run all tests"
    COMMAND python3 ../tests/runtests.py
)
