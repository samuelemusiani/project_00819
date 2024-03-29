#include "audio.hpp"
#include "../logs/logs.hpp"

Audio::Audio() {
  ma_result result;
  result = ma_engine_init(nullptr, &this->_engine);

  if (result != MA_SUCCESS) {
    deb::debug("Could not inizialize the Audio engine");
    this->_is_engine_inizilized = false;
  } else
    this->_is_engine_inizilized = true;

  result = ma_engine_set_volume(&this->_engine, 0.5);
  if (result != MA_SUCCESS)
    deb::debug("Could not set engine audio volume");
}

Audio::~Audio() {
  // This should be uncommented but cause a seg fault, so we leave it like this
  // if (this->_is_engine_inizilized)
  //   ma_engine_uninit(&this->_engine);
}

void Audio::play_music(nostd::string s) {
  this->_need_to_stop_music = false;
  this->_music_thread = std::thread(&Audio::_play_music, this, std::move(s));
}

void Audio::_play_music(nostd::string s) {
  ma_result result;
  ma_sound music;

  result = ma_sound_init_from_file(&_engine, s.c_str(), 0, NULL, NULL, &music);

  if (result != MA_SUCCESS) {
    deb::debug("Could not init the sound from file. This may be due to the "
               "file not be present");
    deb::debug("Could not load: " + s);

    return;
  }

  ma_sound_set_looping(&music, MA_TRUE);
  result = ma_sound_start(&music);

  if (result != MA_SUCCESS) {
    deb::debug("Could not play the sound required");

    return;
  }

  while (!this->_need_to_stop_music) {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }

  ma_sound_stop(&music);
}

void Audio::stop_music() {
  this->_need_to_stop_music = true;
  deb::debug("Waiting for music thread to stop");
  this->_music_thread.join();
  deb::debug("Music thread stopped");
}

void Audio::set_volume(int level) {
  level = std::max(level, 0);
  level = std::min(level, 20);

  ma_result result;
  result = ma_engine_set_volume(&this->_engine, level / 20.0);

  if (result != MA_SUCCESS) {
    deb::debug("Could not change volume level");
  }
}
