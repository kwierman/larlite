file(GLOB HEADERS .  *.h)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)
list(REMOVE_ITEM HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/LinkDef.h)
file(GLOB SOURCES . *.cxx )

ROOT_GENERATE_DICTIONARY(BASE_DICT ${HEADERS} LINKDEF LinkDef.h)

add_library(LarLiteBase SHARED ${SOURCES} BASE_DICT.cxx )
target_link_libraries(LarLiteBase ${ROOT_LIBRARIES})
install(TARGETS LarLiteBase DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)

file(GLOB applications bin/*.cc)
foreach(_app ${applications})
	get_filename_component (name_without_extension ${_app} NAME_WE)
	add_executable(${name_without_extension} ${_app} )
	target_link_libraries(${name_without_extension} LarLiteBase )
	install(TARGETS ${name_without_extension} DESTINATION bin)
endforeach()
