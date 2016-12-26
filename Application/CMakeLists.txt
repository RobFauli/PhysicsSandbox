set(QT_MIN_VERSION "5.7.0")

set(CMAKE_AUTOMOC ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Quick
        )
        
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DNO_QRC)
    set(CMAKE_AUTORCC ON)
    qt5_add_resources(RESOURCES QML/app.qrc)
endif()

set(Library_FILES
        CPP/app.cpp CPP/Object.cpp CPP/QViPhyManager.cpp 
        CPP/QuickView.cpp)

add_library(viphy ${Library_FILES} ${RESOURCES})

target_link_libraries(viphy
        Qt5::Core
        Qt5::Quick
        visualization physics)
