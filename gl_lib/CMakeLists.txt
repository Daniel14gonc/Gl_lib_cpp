add_library(gl_lib SHARED
	gl.h
	gl.cpp
	render.h
	render.cpp
)

target_include_directories(gl_lib PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)