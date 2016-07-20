
set(QT_MIN_VERSION "5.7.0")

set(CMAKE_AUTOMOC ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        )

set(Library_FILES
        CPP/Object.cpp CPP/QViPhyManager.cpp)

add_library(viphy ${Library_FILES})

target_link_libraries(viphy
        Qt5::Core
        visualization physics)
