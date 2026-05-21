project(macros)

include(${PROJECT_SOURCE_DIR}/../../CMakeBuildOpts.txt)

add_executable(${PROJECT_NAME}
    ${PROJECT_NAME}.c
    parse.c
    parse_define.c
    parse_expr.c
    parse_ifelse.c
    parse_ref.c
    symbols.c
    emit.c
)

target_link_libraries(${PROJECT_NAME}
    gc
    cord
    common
)
