#include <iostream>
#include "dshowcapture-wrapper.h"

int main()
{
    TVideoDevice* videoDevices = nullptr;
    TAudioDevice* audioDevices = nullptr;
    int videoCount = 0;
    int audioCount = 0;
    videoDevices = GetVideoInputDevices(&videoCount);
    for (auto i = 0; i < videoCount; i++) {
        printf("%s(%d)\r\n", videoDevices[i].name, videoDevices[i].capsCount);
        for (auto j = 0; j < videoDevices[i].capsCount; j++) {
            printf("\t%d,%d,%d,%d,%d\r\n", 
                videoDevices[i].caps[j].format,
                videoDevices[i].caps[j].minCX,
                videoDevices[i].caps[j].minCY,
                videoDevices[i].caps[j].maxCX,
                videoDevices[i].caps[j].maxCY
            );
        }
    }
    audioDevices = GetAudioInputDevices(&audioCount);
    for (auto i = 0; i < audioCount; i++) {
        printf("%s(%d)\r\n", audioDevices[i].name, audioDevices[i].capsCount);
        for (auto j = 0; j < audioDevices[i].capsCount; j++) {
            printf("\t%d,%d,%d,%d,%d\r\n",
                audioDevices[i].caps[j].format,
                audioDevices[i].caps[j].minChannels,
                audioDevices[i].caps[j].maxChannels,
                audioDevices[i].caps[j].minSampleRate,
                audioDevices[i].caps[j].maxSampleRate
            );
        }
    }
}
