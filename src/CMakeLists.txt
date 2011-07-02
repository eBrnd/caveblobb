# -*- mode: cmake; -*-

file(GLOB_RECURSE h_files "*.hpp,*.h")
file(GLOB_RECURSE cpp_files "*.cpp")
file(GLOB_RECURSE c_files "*.c")
set(caveblobb_src "${h_files}" "${cpp_files}" "${c_files}")

include_directories(
  ${CMAKE_SOURCE_DIR} 
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR} 
  ${SDL_INCLUDE_DIR}
  ${SDLGFX_INCLUDE_DIR}
  ${SDLTTF_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)
add_executable(caveblobb ${caveblobb_src})

# Link the executable 
target_link_libraries(caveblobb 
  ${SDL_LIBRARY}
  ${SDLGFX_LIBRARY}
  ${SDLTTF_LIBRARY}
  ${SDLIMAGE_LIBRARY}
)

# add programs to the install target 
INSTALL(PROGRAMS 
  ${CMAKE_CURRENT_BINARY_DIR}/caveblobb
  DESTINATION bin)

