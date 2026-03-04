# 1. Versi minimum CMake yang dibutuhkan
cmake_minimum_required(VERSION 3.16...3.30)

# 2. Nama Proyek
project(SimulasiGeant4)

# 3. Menemukan paket Geant4 di sistem
# Kita membutuhkan 'ui_all' dan 'vis_all' untuk antarmuka grafis
find_package(Geant4 REQUIRED ui_all vis_all)

# 4. Menyertakan header dari Geant4 dan folder include lokal
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# 5. Mencari semua file sumber di folder src/ secara otomatis
file(GLOB SOURCES src/*.cc *.cc)

# 6. Menentukan file utama (main) dan menggabungkannya dengan sumber lain
add_executable(gamma_mu ${SOURCES})

# 7. Menghubungkan eksekusi dengan library Geant4
target_link_libraries(gamma_mu ${Geant4_LIBRARIES})

# 8. Menyalin file macro ke direktori build
file(GLOB MACRO_FILES macros/*.mac)
foreach(_script ${MACRO_FILES})
  configure_file(${_script} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
endforeach()
