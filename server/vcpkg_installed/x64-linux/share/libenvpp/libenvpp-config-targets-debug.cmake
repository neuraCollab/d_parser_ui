#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "libenvpp::libenvpp" for configuration "Debug"
set_property(TARGET libenvpp::libenvpp APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libenvpp::libenvpp PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/debug/lib/libenvpp.a"
  )

list(APPEND _cmake_import_check_targets libenvpp::libenvpp )
list(APPEND _cmake_import_check_files_for_libenvpp::libenvpp "${_IMPORT_PREFIX}/debug/lib/libenvpp.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
