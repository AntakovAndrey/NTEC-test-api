cmake_minimum_required(VERSION 3.5)

project(MyProject CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(oatpp 1.2.1 REQUIRED)
find_package(oatpp-swagger 1.2.1 REQUIRED)
find_package(oatpp-postgresql 1.2.1 REQUIRED)

add_executable(MyProject
        src/PhoneBookController.hpp
        src/PhoneBookController.cpp
        src/SwaggerController.hpp
        src/SwaggerController.cpp
        src/AppComponent.hpp
        src/DTOs.hpp
        src/main.cpp)

target_link_libraries(MyProject
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
        PUBLIC oatpp::oatpp-postgresql)

if (NOT WIN32)
    target_link_libraries(MyProject PRIVATE pthread)
endif ()
