cmake_minimum_required (VERSION 2.8.11)
project( PROJEKT )


file(GLOB SOURCES
	*.h
	*.cpp
	*.hpp
    )
add_executable( projekt ${SOURCES})
