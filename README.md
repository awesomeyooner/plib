# plib
A collection of C++ header files for helper functions.

# Usage

Put this folder within `/lib`

The folder directory should look something like this

```cpp
|-- project/
|	|-- build // this will be created automatically by cmake
|	|-- include/
|	|-- src/
|	|	|-- main.cpp
|	|-- test/
|	|	|-- test.cpp
|   |-- lib/
|   |   |-- plib/ // this library
|	|-- CMakeLists.txt
```


```cmake
# CMakeLists.txt

# Add this library as a subdirectory
add_subdirectory(lib/plib)

# Link the dependencies / libraries
target_link_libraries( ${MAIN_EXEC} 
  ${THIS_PACKAGE_INCLUDE_DEPENDS} 
  plib
)

# Optional, link this with the test exec
target_link_libraries(${TEST_EXEC} 
  GTest::gtest_main
  ${THIS_PACKAGE_INCLUDE_DEPENDS} 
  plib
)
```