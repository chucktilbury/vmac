project(vm)

include(${PROJECT_SOURCE_DIR}/../../CMakeBuildOpts.txt)

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.c
    class1.c
    class2.c
    class3.c
    class4.c
    class5.c
    class6.c
    class7.c
    class8.c
    run.c
    stack.c
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

