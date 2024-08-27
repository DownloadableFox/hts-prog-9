cmake_minimum_required(VERSION 3.5.0)
project(hts-prog-9 VERSION 0.1.0 LANGUAGES C CXX)

# link to open ssl library
find_package(OpenSSL REQUIRED)

add_executable(hts-prog-9 main.cpp sudoku.cpp crypto.cpp blowfish.cpp)

target_link_libraries(hts-prog-9 OpenSSL::SSL OpenSSL::Crypto)
