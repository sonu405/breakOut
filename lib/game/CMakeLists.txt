add_library(game
    src/game.cpp
    src/sprite_renderer.cpp
)

target_include_directories(game
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game
    PUBLIC
        glfw
        opengl32
        glad
        glm
        stb
        stb_image_impl   # required for linking stb correctly
        # shader
        utility
)