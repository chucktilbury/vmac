project(vm_common)

include(${PROJECT_SOURCE_DIR}/../../CMakeBuildOpts.txt)

add_library(${PROJECT_NAME} STATIC
    opcodes.c
    registers.c
)
