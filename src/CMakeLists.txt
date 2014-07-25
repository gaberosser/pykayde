# custom macro with most of the redundant code for making a python example module
macro( addPythonExe _name _srccpp )
  ADD_EXECUTABLE(${_name} ${_srccpp})
  
  # make the pyd library link against boost_numpy python and boost
  TARGET_LINK_LIBRARIES(${_name} boost_numpy)
  
  # put the example target into a VS solution folder named example (should
  # be a no-op for Linux)
  SET_PROPERTY(TARGET ${_name} PROPERTY FOLDER "example")
endmacro()

macro( addPythonMod _name _srccpp )
  PYTHON_ADD_MODULE(${_name} ${_srccpp})
  
  # make the pyd library link against boost_numpy python and boost
  TARGET_LINK_LIBRARIES(${_name} boost_numpy)
  
  # put the example target into a VS solution folder named example (should
  # be a no-op for Linux)
  SET_PROPERTY(TARGET ${_name} PROPERTY FOLDER "example")
endmacro()

#addPythonMod(Mvn mvn.cpp)
#PYTHON_ADD_MODULE(Mvn mvn.cpp)
#TARGET_LINK_LIBRARIES(Mvn ${Boost_LIBRARIES})
addPythonMod(CppVector cppvector.cpp)
PYTHON_ADD_MODULE(Kde kde.cpp)
TARGET_LINK_LIBRARIES(Kde alglib ${Boost_LIBRARIES})
PYTHON_ADD_MODULE(KdeWrapper kde_wrapper.cpp)
TARGET_LINK_LIBRARIES(KdeWrapper ${Boost_LIBRARIES} boost_numpy)

ADD_SUBDIRECTORY(libalg)
