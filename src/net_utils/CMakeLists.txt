set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/net_utils)
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/net_utils/include)

set(TARGET_NAME net_utils)

set (SRC
     ${SRC_ROOT}/display_utils.c
     ${SRC_ROOT}/tcp_server.c
     ${SRC_ROOT}/remove_unused_sockets.c
     ${SRC_ROOT}/peer.c
     ${SRC_ROOT}/fd_set_manage.c
)

add_library(${TARGET_NAME} ${SRC})

target_link_libraries(${TARGET_NAME} ${TARGET_NAME}_auth)

target_include_directories(${TARGET_NAME}
     PUBLIC ${INCLUDE_ROOT}
     PRIVATE ${SRC_ROOT}
)

add_subdirectory(auth)