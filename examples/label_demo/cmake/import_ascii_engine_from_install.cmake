if(NOT DEFINED ASCII_ENGINE_INSTALL_ROOT)
   message(FATAL_ERROR "Set ASCII_ENGINE_INSTALL_ROOT to your install tree (e.g. ../../build/install)")
endif()

set(_inc_dir "${ASCII_ENGINE_INSTALL_ROOT}/include")

if(NOT EXISTS "${_inc_dir}/ascii_engine")
   message(FATAL_ERROR "Missing installed headers: ${_inc_dir}/ascii_engine. Is ascii_engine installed?")
endif()

if(WIN32)
   set(_dll_file "${ASCII_ENGINE_INSTALL_ROOT}/bin/ascii_engine.dll")
   set(_implib_file "${ASCII_ENGINE_INSTALL_ROOT}/lib/ascii_engine.lib")

   if(NOT EXISTS "${_dll_file}")
      message(FATAL_ERROR "Missing DLL: ${_dll_file}. Is ascii_engine installed?")
   endif()
   if(NOT EXISTS "${_implib_file}")
      message(FATAL_ERROR "Missing import library: ${_implib_file}. Is ascii_engine installed?")
   endif()

   add_library(ascii_engine::ascii_engine SHARED IMPORTED GLOBAL)
   set_target_properties(ascii_engine::ascii_engine PROPERTIES
      IMPORTED_LOCATION "${_dll_file}"
      IMPORTED_IMPLIB "${_implib_file}"
      INTERFACE_INCLUDE_DIRECTORIES "${_inc_dir}"
   )
else()
   set(_lib_file "${ASCII_ENGINE_INSTALL_ROOT}/lib/libascii_engine.so")

   if(NOT EXISTS "${_lib_file}")
      message(FATAL_ERROR "Missing shared library: ${_lib_file}. Is ascii_engine installed?")
   endif()

   add_library(ascii_engine::ascii_engine SHARED IMPORTED GLOBAL)
   set_target_properties(ascii_engine::ascii_engine PROPERTIES
      IMPORTED_LOCATION "${_lib_file}"
      INTERFACE_INCLUDE_DIRECTORIES "${_inc_dir}"
   )
endif()
