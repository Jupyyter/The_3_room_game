#include "sldlib.hpp"

Sound::Sound(std::string name) : usedch(-1){
    this->innersound = Mix_LoadWAV(name.c_str());//loads a wav file
    if (this->innersound == NULL) {//checks for errors
        std::cout << "Load sound error: " << Mix_GetError();
    }
}

/* work in progress
void Sound::PlayAsync(){
    int channel = Mix_GroupAvailable(-1);//gets an available channel
    Mix_Volume(channel, volume);//set volume of channel
    Mix_VolumeChunk(this->innersound, volume);//set volume of chunk
    Mix_PlayChannel(channel, this->innersound, 0);  // play sound once
}
*/

void Sound::PlaySync(){
    uint16_t channelsplaying = Mix_Playing(-1);//gets the number of channels playing
    if(channelsplaying == 0){//checks if there are no channels playing
        usedch = Mix_GroupAvailable(-1);//gets an available channel
        Mix_PlayChannel(usedch, this->innersound, 0);  // play sound once
    }
}

void Sound::SetVolume(int v){
    Mix_Volume(usedch, v);//set volume of channel
    Mix_VolumeChunk(this->innersound, v);//set volume of chunk
}
