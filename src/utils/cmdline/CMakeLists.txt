
set(LIBRARY_NAME cmdline)
# Set SOURCES variable
set(HEADER_ONLY 1)

# Set HEADERS_PUBLIC variable (public headers, included in the library)
set(HEADERS_PUBLIC
  cmdline.h
)
# Set HEADERS_PRIVATE variable, if needed.
# (these private headers won't be included in the library)
# set(HEADERS_PRIVATE
#     foo_private.h
# )

include(${PROJECT_SOURCE_DIR}/cmake/LibraryConfig.cmake)

