cmake_minimum_required(VERSION 2.6)

project(kdreams)

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

file(GLOB_RECURSE header "*.h")

source_group("sources" FILES ${source})
source_group("headers" FILES ${header})

add_executable(kdreams ${source} ${header})

include(FindPkgConfig)
find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)

target_include_directories(kdreams PRIVATE "${PROJECT_SOURCE_DIR}")
target_include_directories(kdreams PRIVATE ${SDL_INCLUDE_DIR})

target_link_libraries(kdreams ${OPENGL_LIBRARIES})
target_link_libraries(kdreams ${SDL_LIBRARY})

