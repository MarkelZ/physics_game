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
