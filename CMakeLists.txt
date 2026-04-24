cmake_minimum_required(VERSION 3.15)
project(DataTransmission)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Mówimy CMake'owi, ¿eby u¿y³ biblioteki z Twojego lokalnego folderu na dysku
add_subdirectory(matplotplusplus)

# 2. Zbieramy wszystkie Twoje kody Ÿród³owe z folderu src
file(GLOB_RECURSE SOURCES "src/*.cpp")
set(KISS_FFT "third_party/kiss_fft/kiss_fft.c")

# 3. Tworzymy Twój program
add_executable(wykres ${SOURCES} ${KISS_FFT})

# 4. Wskazujemy, gdzie s¹ foldery z nag³ówkami (.h)
target_include_directories(wykres PRIVATE include third_party)

# 5. £¹czymy program z Twoim lokalnym matplotem
target_link_libraries(wykres PRIVATE matplot)