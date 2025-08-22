cmake_minimum_required(VERSION 3.10.0)
project(app VERSION 0.1.0 LANGUAGES C)
add_executable(app futebol.c)

target_link_libraries(app
    GL
    GLU
    glut
)
