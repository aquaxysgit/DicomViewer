cmake_minimum_required(VERSION 3.16)
project(DicomViewer)

set(CMAKE_CXX_STANDARD 17)

find_package(DCMTK REQUIRED)
find_package(VTK REQUIRED)

add_executable(DicomViewer
    main.cpp
    DicomSeriesLoader.cpp
    Viewer3D.cpp
    MeasurementManager.cpp
    SRWriter.cpp
)

target_include_directories(DicomViewer PRIVATE ${DCMTK_INCLUDE_DIRS})
target_link_libraries(DicomViewer PRIVATE ${DCMTK_LIBRARIES} ${VTK_LIBRARIES})
