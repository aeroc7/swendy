# Source file storage
add_library(project_source INTERFACE)

add_subdirectory(output)

# Standalone executable
add_executable(swendy_standalone main.cpp)

add_library(project_libraries INTERFACE)

if(WIN32)
    target_link_libraries(project_libraries
        INTERFACE
            -static
            -static-libgcc
            -static-libstdc++
    )
elseif(UNIX AND NOT APPLE)
   target_link_libraries(project_libraries
        INTERFACE
            -static-libgcc
            -static-libstdc++
   )
elseif(APPLE)
endif()

target_link_libraries(swendy_standalone
    PRIVATE
        project_source
        project_options
        project_warnings
        project_libraries
)