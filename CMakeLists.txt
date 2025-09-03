cmake_minimum_required(VERSION 3.10.0)
project(app VERSION 0.1.0 LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find required packages
if(APPLE)
    # On macOS, just find OpenGL (GLU is included in the OpenGL framework)
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
else()
    # On Linux and other platforms, try to find GLU separately
    find_package(OpenGL REQUIRED)
    find_package(GLUT REQUIRED)
    # Try to find GLU separately for Linux
    find_library(GLU_LIBRARY GLU)
endif()

# Create executable
file(GLOB SOURCES "src/*.c")

add_executable(app ${SOURCES})

# Platform-specific linking
if(APPLE)
    # macOS specific linking - use frameworks
    target_link_libraries(app
        "-framework OpenGL"
        "-framework GLUT"
    )
elseif(UNIX AND NOT APPLE)
    # Linux specific linking
    target_link_libraries(app
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
        ${GLU_LIBRARY}
        m  # math library
    )
else()
    # Windows or other platforms
    target_link_libraries(app
        ${OPENGL_LIBRARIES}
        ${GLUT_LIBRARY}
    )
endif()

# Include directories
target_include_directories(app PRIVATE
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    "include/"
)
