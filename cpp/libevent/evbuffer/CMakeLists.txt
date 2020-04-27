include_directories("${PROJECT_SOURCE_DIR}/cpp/libevent/include")
# link_directories("${PROJECT_SOURCE_DIR}/cpp/libevent/lib")
add_library(libevent STATIC IMPORTED)
#set_property(TARGET libevent PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/cpp/libevent/lib/libevent.a)

set_property(TARGET libevent PROPERTY IMPORTED_LOCATION /media/xyc/新加卷2/workspace/code/github.com/libevent/build/lib/libevent.a)

add_executable(parse_socket4 parse_socket4.cc)

add_executable(expand expand.cc)

target_link_libraries(parse_socket4 libevent pthread)

target_link_libraries(expand libevent pthread)
