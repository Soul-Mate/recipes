include_directories("${PROJECT_SOURCE_DIR}/cpp/libevent/include")
link_directories("${PROJECT_SOURCE_DIR}/cpp/libevent/lib")

add_executable(libevent_demo_01 libevent_demo_01.cc)

target_link_libraries(libevent_demo_01 libevent.so)