if(NOT EXISTS ${PROJECT_SOURCE_DIR}/etc/audio/miniaudio/miniaudio.c)
  message(
    FATAL_ERROR
      "La libreria miniaudio non è stata trovata\n \
  In particolare non sono presenti i file:\n \
  ${PROJECT_SOURCE_DIR}/etc/audio/miniaudio/miniaudio.c\n \
  ${PROJECT_SOURCE_DIR}/etc/audio/miniaudio/miniaudio.h\n\n\
  Questo è probabilmente dovuto a un errato clone della repository git:\n \
  la librareia miniaudio è un submodule quindi va inizilizzata con \n \
  il seguente comando\n \
  \$ git submodule init && git submodule update
      ")

endif()

add_library(lib_audio miniaudio/miniaudio.h miniaudio/miniaudio.c audio.hpp
                      audio.cpp)
