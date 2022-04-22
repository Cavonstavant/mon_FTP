set (SRC_ROOT ${PROJECT_SOURCE_DIR}/src/net_utils)
set (INCLUDE_ROOT ${PROJECT_SOURCE_DIR}/src/net_utils/include)

set(TARGET_LIB_NAME net_utils)

set (SRC
     ${SRC_ROOT}/display_utils.c
     ${SRC_ROOT}/tcp_server.c
     ${SRC_ROOT}/remove_unused_sockets.c
     ${SRC_ROOT}/peer.c
)

add_library(${TARGET_LIB_NAME} ${SRC})

target_include_directories(net_utils PUBLIC ${INCLUDE_ROOT})
target_include_directories(net_utils PRIVATE ${INCLUDE_ROOT})
