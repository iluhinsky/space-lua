cmake_minimum_required(VERSION 3.17)
project(space_lua)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/Application)
include_directories(src/Engine/Graphics)
include_directories(src/Engine/Graphics/GraphicsObject)
include_directories(src/Engine/Graphics/Management)
include_directories(src/Engine/Graphics/Model)
include_directories(src/Engine/Graphics/Particles)
include_directories(src/Engine/Graphics/Shaders)
include_directories(src/Engine/Graphics/Skybox)
include_directories(src/Engine/Graphics/Texture)
include_directories(src/Engine/Logic/Controllers)
include_directories(src/Engine/Logic/Controllers/Players)
include_directories(src/Engine/Math)
include_directories(src/Engine/Objects)
include_directories(src/Engine/Physics)
include_directories(src/Game)
include_directories(src/Game/Ship)
include_directories(src/Game/Ship/Blocks)
include_directories(src/Game/World)
include_directories(src/Game/World/Effects)
include_directories(src/Platform/Win)

add_executable(space_lua
        src/Application/Application.cpp
        src/Application/Application.h
        src/Application/Window.cpp
        src/Application/Window.h
        src/Engine/Graphics/GraphicsObject/GraphicsObject.cpp
        src/Engine/Graphics/GraphicsObject/GraphicsObject.h
        src/Engine/Graphics/GraphicsObject/GraphicsObjectFactory.cpp
        src/Engine/Graphics/GraphicsObject/GraphicsObjectFactory.h
        src/Engine/Graphics/Management/ModelManager.cpp
        src/Engine/Graphics/Management/ModelManager.h
        src/Engine/Graphics/Management/ShaderProgManager.cpp
        src/Engine/Graphics/Management/ShaderProgManager.h
        src/Engine/Graphics/Management/TextureManager.cpp
        src/Engine/Graphics/Management/TextureManager.h
        src/Engine/Graphics/Model/Mesh.cpp
        src/Engine/Graphics/Model/Mesh.h
        src/Engine/Graphics/Model/Model.cpp
        src/Engine/Graphics/Model/Model.h
        src/Engine/Graphics/Model/ModelParser.cpp
        src/Engine/Graphics/Model/ModelParser.h
        src/Engine/Graphics/Particles/Particle.cpp
        src/Engine/Graphics/Particles/Particle.h
        src/Engine/Graphics/Particles/ParticleSystem.cpp
        src/Engine/Graphics/Particles/ParticleSystem.h
        src/Engine/Graphics/Particles/ParticleSystemFactory.cpp
        src/Engine/Graphics/Particles/ParticleSystemFactory.h
        src/Engine/Graphics/Shaders/ShaderManager.cpp
        src/Engine/Graphics/Shaders/ShaderManager.h
        src/Engine/Graphics/Shaders/ShaderProg.cpp
        src/Engine/Graphics/Shaders/ShaderProg.h
        src/Engine/Graphics/Skybox/Skybox.cpp
        src/Engine/Graphics/Skybox/Skybox.h
        src/Engine/Graphics/Texture/PngLoader.cpp
        src/Engine/Graphics/Texture/PngLoader.h
        src/Engine/Graphics/GraphicsObjectManager.cpp
        src/Engine/Graphics/GraphicsObjectManager.h
        src/Engine/Graphics/GraphicsWorld.cpp
        src/Engine/Graphics/GraphicsWorld.h
        src/Engine/Logic/Controllers/Players/Player.cpp
        src/Engine/Logic/Controllers/Players/Player.h
        src/Engine/Logic/Controllers/Controller.cpp
        src/Engine/Logic/Controllers/Controller.h
        src/Engine/Math/Camera.cpp
        src/Engine/Math/Camera.h
        src/Engine/Math/math_3d.cpp
        src/Engine/Math/math_3d.h
        src/Engine/Math/Pipeline.cpp
        src/Engine/Math/Pipeline.h
        src/Engine/Objects/GameObject.cpp
        src/Engine/Objects/GameObject.h
        src/Engine/Physics/CollisionObject.cpp
        src/Engine/Physics/CollisionObject.h
        src/Engine/Physics/PhysicsWorld.cpp
        src/Engine/Physics/PhysicsWorld.h
        src/Game/Ship/Blocks/Block.cpp
        src/Game/Ship/Blocks/Block.h
        src/Game/Ship/Blocks/BlockEngine.cpp
        src/Game/Ship/Blocks/BlockEngine.h
        src/Game/Ship/Blocks/BlockFactory.cpp
        src/Game/Ship/Blocks/BlockFactory.h
        src/Game/Ship/Blocks/BlockMain.cpp
        src/Game/Ship/Blocks/BlockMain.h
        src/Game/Ship/Blocks/BlockShield.cpp
        src/Game/Ship/Blocks/BlockShield.h
        src/Game/Ship/Blocks/BlockTypes.h
        src/Game/Ship/Blocks/BlockWeapon.cpp
        src/Game/Ship/Blocks/BlockWeapon.h
        src/Game/Ship/Blocks/OrientedBlock.cpp
        src/Game/Ship/Blocks/OrientedBlock.h
        src/Game/Ship/Ship.cpp
        src/Game/Ship/Ship.h
        src/Game/Ship/ShipController.cpp
        src/Game/Ship/ShipController.h
        src/Game/Ship/ShipFactory.cpp
        src/Game/Ship/ShipFactory.h
        src/Game/World/Effects/Bullet.cpp
        src/Game/World/Effects/Bullet.h
        src/Game/World/World.cpp
        src/Game/World/World.h
        src/Game/World/WorldLoader.cpp
        src/Game/World/WorldLoader.h
        src/Game/CollisionObjectTypes.h
        src/Platform/Win/Platform.cpp
        src/Platform/Win/Platform.h
        src/Include.h
        src/main.cpp)
