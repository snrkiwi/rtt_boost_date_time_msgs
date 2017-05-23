cmake_minimum_required(VERSION 2.8.3)
project(rtt_boost_date_time_msgs)

## Find Orocos RTT and plugins
find_package(OROCOS-RTT 2.0.0 COMPONENTS rtt-scripting rtt-marshalling)
if (NOT OROCOS-RTT_FOUND)
  message(FATAL_ERROR "\n   RTT not found. Is the version correct? Use the CMAKE_PREFIX_PATH cmake or environment variable to point to the installation directory of RTT.")
else()
  include(${OROCOS-RTT_USE_FILE_PATH}/UseOROCOS-RTT.cmake)
  #add_definitions( -DRTT_COMPONENT )
endif()

## find catkin and catkin dependencies
find_package(catkin REQUIRED COMPONENTS rtt_roscomm boost_date_time_msgs)
catkin_destinations()

## Build options

if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

ADD_DEFINITIONS(-DBOOST_DATE_TIME_POSIX_TIME_STD_CONFIG)

## Build typekit and transport plugins
include_directories(
  include
  include/orocos
  ${catkin_INCLUDE_DIRS}
)

# Build typekit plugin
orocos_typekit(rtt-boost_date_time_msgs-ros-transport
  src/ros_boost_date_time_msgs_transport.cpp
)
target_link_libraries(rtt-boost_date_time_msgs-ros-transport ${catkin_LIBRARIES})

# Add an explicit dependency between the typekits and message files
# TODO: Add deps for all msg dependencies
if(boost_date_time_msgs_EXPORTED_TARGETS)
  if(NOT boost_date_time_msgs STREQUAL ${PROJECT_NAME})
    add_dependencies(rtt-boost_date_time_msgs-ros-transport ${boost_date_time_msgs_EXPORTED_TARGETS})
  endif()
endif()

## Install headers
install(
  DIRECTORY include/orocos
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
)

## Generate Orocos package
orocos_generate_package(
  DEPENDS boost_date_time_msgs
  DEPENDS_TARGETS rtt_roscomm boost_date_time_typekit
)
