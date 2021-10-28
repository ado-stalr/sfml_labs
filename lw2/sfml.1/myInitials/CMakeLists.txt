add_executable(myInitials main.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(Freetype)
find_package(JPEG)
find_package(SFML 2 COMPONENTS window graphics system)

target_compile_features(myInitials PUBLIC cxx_std_17)
target_compile_definitions(myInitials PRIVATE SFML_STATIC)

target_link_libraries(myInitials ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})