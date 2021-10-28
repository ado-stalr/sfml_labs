add_executable(svetofor main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(svetofor PUBLIC cxx_std_17)
target_compile_definitions(svetofor PRIVATE SFML_STATIC)

target_link_libraries(svetofor ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})