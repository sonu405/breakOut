add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_library(stb_image_impl STATIC stb_image_impl.cpp)
target_link_libraries(stb_image_impl PUBLIC stb)