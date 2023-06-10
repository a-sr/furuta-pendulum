# Add the behavior implementation to the sources for the LF executable
target_sources(${LF_MAIN_TARGET} PRIVATE visualization.c)

# Include the sources from facil.io
include_directories("libdump/include")
file(GLOB FACIL_SRC_FILES "libdump/src/*.c")
target_sources(${LF_MAIN_TARGET} PRIVATE ${FACIL_SRC_FILES})
