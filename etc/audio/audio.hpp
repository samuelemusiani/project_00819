#ifndef ETC_AUDIO_AUDIO
#define ETC_AUDIO_AUDIO

#include "../nostd/string.hpp"

#include <thread>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

class Audio {
private:
  ma_engine _engine;
  bool _is_engine_inizilized;

  std::thread _music_thread;
  bool _need_to_stop_music = false;

  void _play_music(nostd::string s);

public:
  Audio();
  ~Audio();

  void play_music(nostd::string path);
  void stop_music();

  void set_volume(int level);
  // bool play_fx(nostd::string s);
  // bool stop();
};

#endif
