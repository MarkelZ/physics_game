add_executable(game 
    main.cpp
    game.cpp
    entity.cpp
    physics/collider.cpp
    physics/dynamicobject.cpp
    physics/pointparticle.cpp
    physics/rigidlink.cpp
    physics/simulation.cpp
    physics/trigger.cpp
    utils/debugwriter.cpp
    utils/input.cpp)
target_link_libraries(game sfml-graphics sfml-audio)

# Copy required files to build folder after building
# https://thomas.trocha.com/blog/cmake--copy-files-after-build/
add_custom_command(
        TARGET game POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${PROJECT_SOURCE_DIR}/content
            ${CMAKE_CURRENT_BINARY_DIR}/content
)
