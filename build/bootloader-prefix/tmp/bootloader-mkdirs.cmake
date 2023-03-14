# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Daniel/esp/esp-idf/components/bootloader/subproject"
  "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader"
  "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader-prefix"
  "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader-prefix/tmp"
  "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader-prefix/src"
  "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Daniel/VSCode/ESP_IDF/react-brain/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
