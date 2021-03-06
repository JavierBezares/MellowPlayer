set(CMAKE_AUTOMOC OFF)
add_definitions(-DBUILD_QXT_CORE -DBUILD_QXT_GUI -DQXT_STATIC)
include_directories(../3rdparty)

file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/lib/*.hpp)
set(SOURCE_FILES main.cpp DI.hpp)
if(WIN32)
    set(SOURCE_FILES ${SOURCE_FILES} MellowPlayer.rc)
    configure_file(../scripts/packaging/windows/setup_templ.iss ${CMAKE_BINARY_DIR}/setup.iss)
endif()

# Translation files
file(GLOB_RECURSE TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/languages/*.ts)
set_source_files_properties(${TS_FILES} PROPERTIES OUTPUT_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/languages)
if (UPDATE_TRANSLATIONS)
    message(STATUS "Update translations")
    # update source only, pushing to transifex will update all other languages
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}/lib languages/MellowPlayer_en.ts OPTIONS -noobsolete)
    file(GLOB_RECURSE QM_FILES ${CMAKE_CURRENT_SOURCE_DIR}/languages/*.qm)
else()
    qt5_add_translation(QM_FILES ${TS_FILES})
endif()
qt5_add_resources(RSCS languages/languages.qrc)
add_custom_target(gen_qrc DEPENDS ${RSCS} ${QM_FILES} ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES} ${TS_FILES})

# generate languages.qrc
file(WRITE languages/languages.qrc "<!DOCTYPE RCC>\n")
file(APPEND languages/languages.qrc "<RCC version=\"1.0\">\n")
file(APPEND languages/languages.qrc "    <qresource prefix=\"/MellowPlayer/Translations\">\n")
foreach(FILE ${QM_FILES})
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/languages/" "" RELATIVE_PATH ${FILE})
    file(APPEND languages/languages.qrc "        <file>${RELATIVE_PATH}</file>\n")
endforeach()
file(APPEND languages/languages.qrc "    </qresource>\n")
file(APPEND languages/languages.qrc "</RCC>\n")

add_executable(${PROJECT_NAME} MACOSX_BUNDLE WIN32 ${SOURCE_FILES} ${QM_FILES} ${RSCS})
target_link_libraries(${PROJECT_NAME}
                      ${PROJECT_NAME}.Application ${PROJECT_NAME}.Presentation ${PROJECT_NAME}.Infrastructure
                      Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
                      Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets)
if (APPLE)
    add_framework(Carbon ${PROJECT_NAME})
    add_framework(Cocoa ${PROJECT_NAME})
elseif(UNIX)
    find_package(X11)
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES} Qt5::DBus)
    if (STATIC_LIBSTDCPP)
        message(STATUS "Linking statically to libgcc and libstdc++")
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    endif()
    if(USE_LIBNOTIFY)
        target_link_libraries(${PROJECT_NAME} ${LIBNOTIFY_LIBRARIES})
    endif()
endif()

# add a console based executable for easier debugging
if (WIN32)
    add_executable(${PROJECT_NAME}.Console MACOSX_BUNDLE ${SOURCE_FILES})
    target_link_libraries(${PROJECT_NAME}.Console
                          ${PROJECT_NAME}.Application ${PROJECT_NAME}.Presentation ${PROJECT_NAME}.Infrastructure
                          Qt5::Concurrent Qt5::Core Qt5::Gui Qt5::Network Qt5::Qml Qt5::Quick Qt5::QuickControls2
                          Qt5::Sql Qt5::Svg Qt5::WebEngine Qt5::WebEngineWidgets Qt5::Widgets)
endif()

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION MacOS
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/static)
