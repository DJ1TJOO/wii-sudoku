
#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include <asndlib.h>
#include <mp3player.h>

void playSound(int sound);

void pauseSound();
void resumeSound();

void stopSound();
void setVolumeSound(int volume);
void playNextSound();

void setLoopSound(int l);
void setOneSound(int r);

void processSound();

#endif