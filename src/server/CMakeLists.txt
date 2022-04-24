set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/server/include)
set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/server)

set (FTP_CMDS_SRC_ROOT ${SRC_ROOT}/ftp_commands)

set(TARGET ${PROJECT_NAME})

set(FTP_CMD_SRC
    ${FTP_CMDS_SRC_ROOT}/user/user.c
)

set(SRC
    ${SRC_ROOT}/main.c
    ${SRC_ROOT}/ftp.c
    ${SRC_ROOT}/commands.c
    ${SRC_ROOT}/reply_codes.c
    ${SRC_ROOT}/exec.c
    ${SRC_ROOT}/client_io.c
    ${SRC_ROOT}/parse_cmd.c
    ${FTP_CMD_SRC}
)

add_executable(${TARGET} ${SRC})

target_link_libraries(${TARGET} net_utils)

target_include_directories(${TARGET}
    PRIVATE ${INCLUDE_ROOT}
    PUBLIC $<TARGET_PROPERTY:net_utils,PUBLIC_INCLUDE_DIRECTORIES>
)

set_target_properties(${TARGET} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
)
