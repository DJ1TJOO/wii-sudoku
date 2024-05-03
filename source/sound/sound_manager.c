#include "sound_manager.h"

#include "creativeminds_mp3.h"
#include "dreams_mp3.h"
#include "elevate_mp3.h"
#include "hey_mp3.h"
#include "inspire_mp3.h"
#include "paperback_mp3.h"
#include "unbreakableresolve_mp3.h"

static int loopFlag = 0;
static int oneFlag = 0;
static int lastSound = 0;

static int numSounds = 7;

void playSound(int sound)
{
    if (sound > (numSounds - 1))
        return;

    lastSound = sound;

    if (sound == 0)
    {
        MP3Player_PlayBuffer(creativeminds_mp3, creativeminds_mp3_size, NULL);
    }
    else if (sound == 1)
    {
        MP3Player_PlayBuffer(dreams_mp3, dreams_mp3_size, NULL);
    }
    else if (sound == 2)
    {
        MP3Player_PlayBuffer(elevate_mp3, elevate_mp3_size, NULL);
    }
    else if (sound == 3)
    {
        MP3Player_PlayBuffer(hey_mp3, hey_mp3_size, NULL);
    }
    else if (sound == 4)
    {
        MP3Player_PlayBuffer(inspire_mp3, inspire_mp3_size, NULL);
    }
    else if (sound == 5)
    {
        MP3Player_PlayBuffer(paperback_mp3, paperback_mp3_size, NULL);
    }
    else if (sound == 6)
    {
        MP3Player_PlayBuffer(unbreakableresolve_mp3, unbreakableresolve_mp3_size, NULL);
    }
}

void playNextSound()
{
    playSound((lastSound + 1) % numSounds);
}

void pauseSound()
{
    ASND_Pause(1);
}

void resumeSound()
{
    ASND_Pause(0);
}

void stopSound()
{
    MP3Player_Stop();
}

void setVolumeSound(int volume)
{
    MP3Player_Volume(volume);
}

void setLoopSound(int l)
{
    loopFlag = l;
}

void setOneSound(int r)
{
    oneFlag = r;
}

void processSound()
{

    // @TODO: later random sounds
    // if (loopFlag == 0 || MP3Player_IsPlaying() == 1)
    //     return;

    // if (oneFlag == 1)
    // {
    //     playNextSound();
    // }
    // else
    // {
    //     playSound(0);
    // }
}