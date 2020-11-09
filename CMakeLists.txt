cmake_minimum_required(VERSION 3.5)

project(MuseTargeting LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Qt5_DIR "D:/Qt/5.15.1/msvc2019/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

#set (CMAKE_BINARY_DIR Debug_x32)
#set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_output_)
#set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_output_)
#set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_output_)

#add_subdirectory(libs/libCore)
set (libCore_src
	libs/libCore/libCore.cpp
	libs/libCore/libCore.h

    libs/libCore/Core/Constants.cpp
	libs/libCore/Core/Constants.h
	libs/libCore/Core/CoreExceptions.cpp
	libs/libCore/Core/CoreExceptions.h
	libs/libCore/Core/EventUtils.h
	libs/libCore/Core/Image.cpp
	libs/libCore/Core/Image.h
	libs/libCore/Core/sigslot.h
	libs/libCore/Core/STLTools.cpp
	libs/libCore/Core/STLTools.h
	libs/libCore/Core/Tools.cpp
	libs/libCore/Core/Tools.h

	libs/libCore/Core/Maths/BoundingBox.cpp
	libs/libCore/Core/Maths/BoundingBox.h
	libs/libCore/Core/Maths/Line.cpp
	libs/libCore/Core/Maths/Line.h
	libs/libCore/Core/Maths/Matrix.cpp
	libs/libCore/Core/Maths/Matrix.h
	libs/libCore/Core/Maths/Matrix2.cpp
	libs/libCore/Core/Maths/Matrix2.h
	libs/libCore/Core/Maths/Matrix3.cpp
	libs/libCore/Core/Maths/Matrix3.h
	libs/libCore/Core/Maths/Matrix4.cpp
	libs/libCore/Core/Maths/Matrix4.h
	libs/libCore/Core/Maths/Plane.cpp
	libs/libCore/Core/Maths/Plane.h
	libs/libCore/Core/Maths/Polygon.cpp
	libs/libCore/Core/Maths/Polygon.h
	libs/libCore/Core/Maths/Segment.cpp
	libs/libCore/Core/Maths/Segment.h
	libs/libCore/Core/Maths/Triangle.cpp
	libs/libCore/Core/Maths/Triangle.h
	libs/libCore/Core/Maths/Trihedron.cpp
	libs/libCore/Core/Maths/Trihedron.h
	libs/libCore/Core/Maths/Vector2.cpp
	libs/libCore/Core/Maths/Vector2.h
	libs/libCore/Core/Maths/Vector3.cpp
	libs/libCore/Core/Maths/Vector3.h
	libs/libCore/Core/Maths/Vector4.cpp
	libs/libCore/Core/Maths/Vector4.h
)
add_library (libCore SHARED ${libCore_src})
target_compile_definitions (libCore PRIVATE LIBCORE_EXPORTS=1)

add_executable(MuseTargeting
    src/MuseTargeting.cpp
    src/PseudoTGDriver.h
    src/PseudoTGDriver.cpp
    src/PseudoTGDriver.ui
    src/MuseTargetingView.h
    src/MuseTargetingView.cpp
    src/MuseTargetingView.ui
    src/MuseTargetingModel.h
    src/MuseTargetingModel.cpp
    src/MuseTargetingSettings.h
    src/MuseTargetingSettings.cpp
    src/MuseTargetingDOF.h
    src/MuseTargetingDOF.cpp
)

target_link_libraries(MuseTargeting PRIVATE Qt5::Widgets PUBLIC libCore)
