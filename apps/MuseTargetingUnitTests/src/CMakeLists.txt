
cmake_minimum_required(VERSION 3.15)
project(museTargetingUnitTests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

if (CMAKE_GENERATOR MATCHES "Visual Studio .*")
	string (REGEX REPLACE "Visual Studio [0-9]+ ([0-9]+).*" "\\1" vs_version ${CMAKE_GENERATOR})
	set (generator vs${vs_version})
elseif (CMAKE_GENERATOR STREQUAL "Ninja")
	set (generator ${CMAKE_C_COMPILER})  # ninja_${CMAKE_C_COMPILER}
elseif (CMAKE_GENERATOR STREQUAL "Unix Makefiles")
	set (generator ${CMAKE_C_COMPILER})  # gmake_${CMAKE_C_COMPILER}
endif()

if (MSVC)
	# Warning: does not seem to work as expected (value is X86 even when called with Win64)
	# ${CMAKE_HOST_SYSTEM_PROCESSOR} = AMD64  = processor of the PC running cmake, not what we want
	# CMAKE_CXX_COMPILER_ARCHITECTURE_ID = "X86" or "x64"  (yes X for 86 and x for 64)
	string (TOLOWER "${CMAKE_CXX_COMPILER_ARCHITECTURE_ID}" targetArch)
	if (targetArch STREQUAL "x86")
		set (targetArch "x32")
	endif()
endif()
message ("Arch=${targetArch}, Gen=${CMAKE_GENERATOR}")

set (LIBS_PATH_VER $ENV{LIBS_PATH}/${generator}_${targetArch})
set (LIBS_PATH_COM $ENV{LIBS_PATH}/common)
set (MUSE_TARGETING_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../MuseTargeting/src) 

find_package (Catch2 2.11 REQUIRED CONFIG PATHS ${LIBS_PATH_COM}/Catch2-2.11.3 NO_DEFAULT_PATH)

if (MSVC)
	add_compile_options (/MP4 /W4)  # /WX /W4 warning level 4, /WX warning as error
endif()
set (CMAKE_DEBUG_POSTFIX _d)

set (sources
    main.cpp
    MTDOFTests.cpp
    MTSettingsTests.cpp
)

set (progname "museTargetingUnitTests")
add_executable(${progname} ${sources})

target_link_libraries (${progname} Catch2::Catch2 Qt5::Widgets)
target_include_directories (${progname} PRIVATE ${LIBS_PATH_COM} ${MUSE_TARGETING_PATH})  # for catch2, Muse Targeting classes