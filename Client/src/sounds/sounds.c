#include "client.h"

// void mx_initialize(t_fmod *sf) {
//     sf->result = FMOD_System_Create(&(sf->fmod_sys));
//     if (sf->result != FMOD_OK) {
//         printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
//         exit(-1);
//     }
//     sf->result = FMOD_System_Init(sf->fmod_sys, 2, FMOD_INIT_NORMAL, NULL);
//     if (sf->result != FMOD_OK) {
//         printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
//         exit(-1);
//     }
//     FMOD_Channel_SetVolume(sf->channel, 0.0f);
//     sf->result = FMOD_Sound_Release(sf->sound);
// }

// void mx_load(t_fmod *sf) {
//     sf->result = FMOD_System_CreateStream(sf->fmod_sys, "./Resources/sounds/message.mp3",
//         FMOD_MPEGSEARCH, 0, &(sf->sound));
//     if (sf->result != FMOD_OK) {
//         printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
//         exit(-1);
//     }
// }

// void mx_play(t_fmod *sf) {
//     sf->result = FMOD_System_PlaySound(sf->fmod_sys, FMOD_CHANNEL_FREE, 
//         sf->sound, sf->pause, &(sf->channel));
//     if (sf->result != FMOD_OK) {
//         printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
//         exit(-1);
//     }
//     FMOD_Channel_SetMode(sf->channel,FMOD_LOOP_OFF);
//     FMOD_Channel_IsPlaying(sf->channel, NULL);
//     sleep(2);
//     exit(0);
// }
