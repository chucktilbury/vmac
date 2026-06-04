project(vm)

include(${PROJECT_SOURCE_DIR}/../../CMakeBuildOpts.txt)

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.c
    run.c
)

add_definitions(
    -Wno-unused-variable
)

target_link_libraries(${PROJECT_NAME}
    gc
    cord
    common
    vm_common
)

