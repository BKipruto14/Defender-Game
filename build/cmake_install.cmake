# Install script for directory: C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/elen3009-project")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/msys64/mingw64/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/_deps/doctest-build/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/_deps/sfml-build/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-audio-d-2.dll"
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-graphics-d-2.dll"
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-window-d-2.dll"
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-system-d-2.dll"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE FILES
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-audio-d-2.dll"
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-graphics-d-2.dll"
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-window-d-2.dll"
    "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/bin/sfml-system-d-2.dll"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/bradl/OneDrive/Desktop/Project Final/2023-project-2172968-Kipruto-2253526-Sekeleni/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
