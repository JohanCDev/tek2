set(INCROOT ${PROJECT_SOURCE_DIR}/include/)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src//lib/ikea/)

set(SRC
    ${INCROOT}ikea.h
    ${SRCROOT}ikea.c
)
set(LIBNAME ikea)

add_library(${LIBNAME} STATIC ${SRC})

target_include_directories(ikea PUBLIC ${INCROOT})