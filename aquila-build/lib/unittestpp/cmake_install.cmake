# Install script for directory: /home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-build/lib/unittestpp/libUnitTest++.a")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++" TYPE FILE FILES
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestMacros.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/XmlTestReporter.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestSuite.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestDetails.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/HelperMacros.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/ExecuteTest.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/Test.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/ReportAssert.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/ExceptionMacros.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TimeHelpers.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/UnitTestPP.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestReporterStdout.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/UnitTest++.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TimeConstraint.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestRunner.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/DeferredTestReporter.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/CurrentTest.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/ReportAssertImpl.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/MemoryOutStream.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestResults.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestList.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/CheckMacros.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/CompositeTestReporter.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/Config.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/TestReporter.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/DeferredTestResult.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/Checks.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/AssertException.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/UnitTest++/Posix" TYPE FILE FILES
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/Posix/TimeHelpers.h"
    "/home/ivan/Documents/Raspoznavaika/raspoznavayka/aquila-src/lib/unittestpp/UnitTest++/Posix/SignalTranslator.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

