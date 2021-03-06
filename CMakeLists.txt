cmake_minimum_required(VERSION 2.6)

project(kdreams)

# --- bin2c ---

add_executable(bin2c "tools/bin2c.cpp")

# --- auto-generated header and source files from game assets ---

set(static_list
	static/AUDIODCT.KDR static/AUDIODCT audiodict
	static/AUDIOHHD.KDR static/AUDIOHHD audiohead
	static/CONTEXT.KDR static/CONTEXT context
	static/EGADICT.KDR static/EGADICT EGAdict
	static/EGAHEAD.KDR static/EGAHEAD EGAhead
	static/GAMETEXT.KDR static/GAMETEXT gametext
	static/MAPDICT.KDR static/MAPDICT mapdict
	static/MAPHEAD.KDR static/MAPHEAD maphead
	static/STORY.KDR static/STORY story)

list(LENGTH static_list static_count)
math(EXPR static_count "${static_count} / 3 - 1")

foreach(val RANGE ${static_count})
	math(EXPR source_index "${val} * 3 + 0")
	math(EXPR prefix_index "${val} * 3 + 1")
	math(EXPR symbol_index "${val} * 3 + 2")

	list(GET static_list ${source_index} source)
	list(GET static_list ${prefix_index} prefix)
	list(GET static_list ${symbol_index} symbol)
	message(STATUS "adding bin2c build step: ${source} ${prefix} ${symbol}")

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/${prefix}.c ${CMAKE_CURRENT_SOURCE_DIR}/${prefix}.h
		COMMAND bin2c ${source} ${prefix} ${symbol}
		DEPENDS bin2c ${source}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endforeach()

# --- kdreams ---

set(source
	static/AUDIODCT.c
	static/AUDIOHHD.c
	static/CONTEXT.c
	static/EGADICT.c
	static/EGAHEAD.c
	static/GAMETEXT.c
	static/MAPDICT.c
	static/MAPHEAD.c
	static/STORY.c
	opl/opl.c
	gelib.c
	id_ca.c
	id_in.c
	id_rf_routines.c
	id_rf.c
	id_sd.c
	id_us_routines.c
	id_us.c
	id_vw_routines.c
	id_vw.c
	jam_io.c
	kd_act1.c
	kd_act2.c
	kd_demo.c
	kd_keen.c
	kd_main.c
	kd_play.c
	lzhuf.c
	shifttable.c
	soft.c
	stubs.c
	syscode.c)

if (WIN32)
	list(APPEND source syscode_xinput.c)
endif (WIN32)

file(GLOB_RECURSE header "*.h")

source_group("sources" FILES ${source})
source_group("headers" FILES ${header})

add_executable(kdreams ${source} ${header})

include(FindPkgConfig)
find_package(OpenGL REQUIRED)

if (WIN32)
	set(SDL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/win32/include/SDL)
	set(SDL_LIBRARY ${PROJECT_SOURCE_DIR}/win32/lib/SDL.lib ${PROJECT_SOURCE_DIR}/win32/lib/SDLmain.lib ${PROJECT_SOURCE_DIR}/win32/lib/Xinput9_1_0.lib)
	target_compile_definitions(kdreams PRIVATE _CRT_SECURE_NO_DEPRECATE)
else (WIN32)
	find_package(SDL REQUIRED)
endif (WIN32)

target_include_directories(kdreams PRIVATE "${PROJECT_SOURCE_DIR}")
target_include_directories(kdreams PRIVATE ${SDL_INCLUDE_DIR})

target_link_libraries(kdreams ${OPENGL_LIBRARIES})
target_link_libraries(kdreams ${SDL_LIBRARY})

if (UNIX)
    target_link_libraries(kdreams m)
endif (UNIX)

if (WIN32)
	set_target_properties(kdreams PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/game")

	add_custom_command(TARGET kdreams POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${CMAKE_SOURCE_DIR}/win32/dll/SDL.dll"
			$<TARGET_FILE_DIR:kdreams>)
	add_custom_command(TARGET kdreams POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
			"${CMAKE_SOURCE_DIR}/win32/dll/XInput9_1_0.dll"
			$<TARGET_FILE_DIR:kdreams>)
endif (WIN32)