set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/server/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/server)

set(TARGET ${PROJECT_NAME})

set(SRC
    ${SRC_ROOT}/ftp.c
    ${SRC_ROOT}/commands.c
    ${SRC_ROOT}/reply_codes.c
)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} net_utils)
target_include_directories(${TARGET}
    PRIVATE ${INCLUDE_ROOT}
    PRIVATE $<TARGET_PROPERTY:net_utils,PUBLIC_INCLUDE_DIRECTORIES>
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)

