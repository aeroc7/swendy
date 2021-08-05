# Copy obj file to binary output directory
file(COPY
        ${CMAKE_CURRENT_LIST_DIR}/monkey.obj
    DESTINATION
        ${CMAKE_BINARY_DIR}
)