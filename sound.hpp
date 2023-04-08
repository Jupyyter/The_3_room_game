#pragma once

class Sound{
    public:
    Sound(std::string name);
    //void PlayAsync();//async doesn't wait for the last sound that was played to finish in order to play the next (work in progress)
    void PlaySync();//sync waits for the last sound that was played to finish before playing the next
    void SetVolume(int volume);//the volume is a number between 0  and 128

    private:
    Mix_Chunk* innersound;
    int usedch;
};