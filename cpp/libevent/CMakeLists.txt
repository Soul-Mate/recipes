# include_directories("${PROJECT_SOURCE_DIR}/cpp/libevent/include")
# link_directories("${PROJECT_SOURCE_DIR}/cpp/libevent/lib")
# add_library(libevent STATIC IMPORTED)
# set_property(TARGET libevent PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/cpp/libevent/lib/libevent.a)
# add_executable(libevent_demo_01 libevent_demo_01.cc)
# target_link_libraries(libevent_demo_01 libevent)

add_subdirectory(evbuffer)

