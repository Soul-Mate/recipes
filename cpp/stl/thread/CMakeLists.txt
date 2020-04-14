add_executable(thread_01 thread_01.cc)
add_executable(thread_02 thread_02.cc)
add_executable(thread_03 thread_03.cc)
add_executable(thread_04 thread_04.cc)
add_executable(thread_05 thread_05.cc)


target_link_libraries(thread_02 pthread)
target_link_libraries(thread_02 pthread)
target_link_libraries(thread_03 pthread)
target_link_libraries(thread_04 pthread)
target_link_libraries(thread_05 pthread)