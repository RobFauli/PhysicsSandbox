
set(QT_MIN_VERSION "5.7.0")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
        Core
        Quick
        )

set(Library_FILES
        CPP/Object.cpp CPP/QViPhyManager.cpp CPP/QuickView.cpp CPP/QuickView.hpp)
qt5_add_resources(RESOURCES QML/app.qrc)

add_library(viphy ${Library_FILES} ${RESOURCES})

target_link_libraries(viphy
        Qt5::Core
        Qt5::Quick
        visualization physics)
