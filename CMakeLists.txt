cmake_minimum_required(VERSION 2.8.3)
project(rtt_boost_date_time_msgs)

## Find Orocos RTT and plugins
find_package(OROCOS-RTT 2.0.0 COMPONENTS rtt-scripting rtt-marshalling rtt-transport-mqueue rtt-transport-corba)
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
# mqueue transport
OPTION(ENABLE_MQ "Build posix message queue transport plugin for ${_package}" OFF)
if(ENABLE_MQ)
  if (OROCOS-RTT_MQUEUE_FOUND)
    message(STATUS "Building MQueue transport plugin for ROS messages in package ${_package} with ${OROCOS-RTT_MQUEUE_LIBRARIES}")
  else()
    message(WARNING "Disabled built of posix message queue transport plugin for ${_package} because the RTT mqueue plugin could not be found.")
    set(ENABLE_MQ OFF CACHE BOOL "Build posix message queue transport plugin for ${_package} (forced to OFF)" FORCE)
  endif()
endif()

# corba transport
OPTION(ENABLE_CORBA "Build CORBA transport plugin for ${_package}" OFF)
if(ENABLE_CORBA)
  if(OROCOS-RTT_CORBA_FOUND)
    message(STATUS "Building CORBA transport plugin for ROS messages in package ${_package} with ${OROCOS-RTT_CORBA_LIBRARIES}")
  else()
    message(WARNING "Disabled built of CORBA transport plugin for ${_package} because the RTT CORBA plugin could not be found.")
    set(ENABLE_CORBA OFF CACHE BOOL "Build CORBA transport plugin for ${_package} (forced to OFF)" FORCE)
  endif()
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_BUILD_TYPE MinSizeRel)
endif()

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

# Build mqueue transport plugin
if(ENABLE_MQ)
  orocos_typekit(rtt-boost_date_time_msgs-ros-transport-mqueue
    ${rtt-kdl_msgs-ros-transport-mqueue_SOURCES}
  )
  target_link_libraries(rtt-boost_date_time_msgs-ros-transport-mqueue ${catkin_LIBRARIES} ${OROCOS-RTT_MQUEUE_LIBRARIES})
endif()

# Add an explicit dependency between the typekits and message files
# TODO: Add deps for all msg dependencies
if(boost_date_time_msgs_EXPORTED_TARGETS)
  if(NOT boost_date_time_msgs STREQUAL ${PROJECT_NAME})
    add_dependencies(rtt-boost_date_time_msgs-ros-transport ${boost_date_time_msgs_EXPORTED_TARGETS})
    if(TARGET rtt-boost_date_time_msgs-ros-transport-mqueue)
      add_dependencies(rtt-boost_date_time_msgs-ros-transport-mqueue ${boost_date_time_msgs_EXPORTED_TARGETS})
    endif()
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
  DEPENDS_TARGETS rtt_roscomm boost_date_time_typekit rtt_std_msgs
)
