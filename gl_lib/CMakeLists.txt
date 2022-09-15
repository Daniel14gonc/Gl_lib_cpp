add_library(gl_lib SHARED
	gl.h
	gl.cpp
	render.h
	render.cpp
	obj.h
	obj.cpp
	vector3.h
	vector3.cpp
	texture.h
	texture.cpp
	matrix.hpp
	vector4.h
	vector4.cpp
	simplex.h
	simplex.cpp
)

target_include_directories(gl_lib PUBLIC
	${CMAKE_CURRENT_LIST_DIR}
)