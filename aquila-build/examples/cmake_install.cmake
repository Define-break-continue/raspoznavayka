# Install script for directory: /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/examples

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/utility_functions/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/frame_iteration/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/wave_info/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/wave_iteration/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/window_plot/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/window_usage/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/text_plot/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/sine_generator/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/square_generator/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/triangle_generator/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/generators/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/am_modulation/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_comparison/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_simple_spectrum/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/fft_filter/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/spectrogram/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/mfcc_calculation/cmake_install.cmake")
  INCLUDE("/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/examples/dtw_path_recovery/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

