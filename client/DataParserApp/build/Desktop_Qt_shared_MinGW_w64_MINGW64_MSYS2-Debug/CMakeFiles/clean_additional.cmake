# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\DataPsrser_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\DataPsrser_autogen.dir\\ParseCache.txt"
  "DataPsrser_autogen"
  )
endif()
