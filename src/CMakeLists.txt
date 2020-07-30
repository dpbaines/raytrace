configure_file(RayConfig.h.in RayConfig.h)

file(GLOB raytrace_SRC
    "*.h"
    "*.cpp"
)

add_executable(raytrace ${raytrace_SRC})

target_link_libraries(raytrace -lsfml-window)
target_link_libraries(raytrace -lsfml-graphics)
target_link_libraries(raytrace -lsfml-system)
target_include_directories(raytrace PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )