set(Library_FILES
        )

add_library(viphy ${Library_FILES})

target_link_libraries(viphy visualization physics)
target_include_directories(visualization PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})