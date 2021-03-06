cmake_minimum_required(VERSION 2.8)
project(runThis)

set(SOURCES
    src/main.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/Particles/ParticleSystem.cpp
    src/Particles/Particle.cpp
    src/MarchingCubes.cpp
    src/TransformFeedback.cpp
    src/Rainbow.cpp
)
set(HEADERS
    src/Shader.hpp
    src/Texture.hpp
    src/Camera.hpp
    src/Particles/ParticleSystem.hpp
    src/Particles/Particle.hpp
    src/MarchingCubes.hpp
    src/constants.hpp
    src/TransformFeedback.hpp
    src/Rainbow.hpp
)
set(SHADERS
)
set(RESOURCES
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
foreach(FOLDERNAME IN ITEMS "Particles" "Graphics" "imgui" "Input" "QuadTree" "rapidjson" "Renderers")
    string(CONCAT FILEREGEX "src/" ${FOLDERNAME} "/.*")

    source_group("Source Files\\${FOLDERNAME}" REGULAR_EXPRESSION "${FILEREGEX}\\.cpp")
    source_group("Header Files\\${FOLDERNAME}" REGULAR_EXPRESSION "${FILEREGEX}\\.hpp")
endforeach(FOLDERNAME)

set(CMAKE_CXX_STANDARD 11)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}
    DEPENDS ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/imgui)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/Users/ashleydattalo/cmake/modules/")
find_package(GLFW REQUIRED)
if (GLFW_FOUND)
    include_directories(${CMAKE_PROJECT_NAME} ${GLFW_INCLUDE_DIR})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${GLFW_LIBRARY})
else()
    message(FATAL_ERROR "Can't find GLFW")
endif()

find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${CMAKE_PROJECT_NAME} ${OPENGL_INCLUDE_DIR})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_gl_LIBRARY})
else()
    message(FATAL_ERROR "Can't find OpenGL")
endif()

find_package(GLEW)
if (GLEW_FOUND)
    include_directories(${CMAKE_PROJECT_NAME} ${GLEW_INCLUDE_DIRS})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${GLEW_LIBRARIES})
elseif (DEFINED ENV{GLEW_INCLUDE_DIR})
    message(STATUS "using GLEW_INCLUDE_DIR environment variable")
    include_directories(${CMAKE_PROJECT_NAME} "$ENV{GLEW_INCLUDE_DIR}/include")
    
    if (APPLE)
       target_link_libraries(${CMAKE_PROJECT_NAME} "$ENV{GLEW_INCLUDE_DIR}/lib/libGLEW.a")
    elseif (WIN32)
       target_link_libraries(${CMAKE_PROJECT_NAME} "$ENV{GLEW_INCLUDE_DIR}/lib/Release/Win32/glew32s.lib")
    endif()
else()
    message(FATAL_ERROR "Can't find GLEW")
endif()

if (DEFINED ENV{GLM_LOCATION})
    message(STATUS "using GLM_LOCATION environment variable")
    include_directories(${CMAKE_PROJECT_NAME} "$ENV{GLM_LOCATION}")
endif()

find_package(SFML COMPONENTS audio system)
if (SFML_FOUND)
    include_directories(${CMAKE_PROJECT_NAME} ${SFML_INCLUDE_DIR})
    target_link_libraries(${CMAKE_PROJECT_NAME} ${SFML_LIBRARIES})
else()
    message(FATAL_ERROR "Can't find SFML. Set environment variable SFML_ROOT.")
endif()
