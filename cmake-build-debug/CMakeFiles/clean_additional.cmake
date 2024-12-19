# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/VoronoiDiscretFB_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/VoronoiDiscretFB_autogen.dir/ParseCache.txt"
  "VoronoiDiscretFB_autogen"
  )
endif()
