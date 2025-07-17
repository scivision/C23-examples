set(j "{}")

foreach(s IN LISTS stds)

get_property(has_features DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${s} PROPERTY BUILDSYSTEM_TARGETS)

list(LENGTH ${s}features Nf)

math(EXPR N "${Nf} - 1")
string(JSON j SET ${j} ${s} "{}")

foreach(i RANGE ${N})
  list(GET ${s}features ${i} feature)
  if(feature IN_LIST has_features)
    set(hasf true)
  else()
    set(hasf false)
  endif()

  string(JSON j SET ${j} ${s} ${feature} ${hasf})
endforeach()

endforeach()

string(JSON j SET ${j} compiler "{}")
string(JSON j SET ${j} compiler vendor \"${CMAKE_C_COMPILER_ID}\")
string(JSON j SET ${j} compiler version \"${CMAKE_C_COMPILER_VERSION}\")
string(JSON j SET ${j} compiler flags \"${CMAKE_C_FLAGS}\")

string(JSON j SET ${j} platform "{}")
string(JSON j SET ${j} platform system \"${CMAKE_SYSTEM_NAME}\")
string(JSON j SET ${j} platform system_version \"${CMAKE_SYSTEM_VERSION}\")
string(JSON j SET ${j} platform target_arch \"${CMAKE_SYSTEM_PROCESSOR}\")
string(JSON j SET ${j} platform sysroot \"${CMAKE_OSX_SYSROOT}\")

if(NOT DEFINED stdc_version)

  message(CHECK_START "Checking C standard library version")
  # Intel, IntelLLVM and NVHPC on Linux use GNU libc
  try_run(stdc_run _stdc_build_ok
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/libc_version.c
    RUN_OUTPUT_STDOUT_VARIABLE _stdc_version
  )

  if(NOT stdc_run EQUAL 0)
    message(CHECK_FAIL "Could not determine libc version ${stdc_build_ok} ${stdc_run} ${_stdc_version}")
  else()
    string(STRIP "${_stdc_version}" _stdc_version)
    set(stdc_version "${_stdc_version}" CACHE STRING "C standard library version")
    message(CHECK_PASS "${stdc_version}")
  endif()

endif()

string(JSON j SET ${j} compiler stdc \"${stdc_version}\")

set(feature_file ${CMAKE_CURRENT_BINARY_DIR}/features.json)

file(WRITE ${feature_file} ${j})

message(STATUS "See ${feature_file} for features enabled by standard")
