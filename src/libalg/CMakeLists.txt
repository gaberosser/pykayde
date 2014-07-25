SET(lib_LIBALG	alglibinternal.cpp
		alglibmisc.cpp
		ap.cpp)
ADD_LIBRARY(alglib SHARED ${lib_LIBALG} )
