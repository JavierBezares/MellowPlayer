set(LIB_NAME "${PROJECT_NAME}.Application")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Settings/schema.json.in ${CMAKE_CURRENT_SOURCE_DIR}/Settings/schema.json)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} application.qrc)
target_link_libraries(${LIB_NAME} Qt5::Core Qt5::Gui)
