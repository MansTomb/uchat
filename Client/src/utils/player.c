#include "client.h"

static void initialize(t_fmod *sf) {
    sf->result = FMOD_System_Create(&(sf->fmod_sys));
    if (sf->result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
    }
    sf->result = FMOD_System_Init(sf->fmod_sys, 2, FMOD_INIT_NORMAL, NULL);
    if (sf->result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
    }
    FMOD_Channel_SetVolume(sf->channel, 0.0f);
    sf->result = FMOD_Sound_Release(sf->sound);
}

static void load(t_fmod *sf) {
    sf->result = FMOD_System_CreateStream(sf->fmod_sys, "./Resources/sounds/message.mp3",
        FMOD_MPEGSEARCH, 0, &(sf->sound));
    if (sf->result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
    }
}

static void play(t_fmod *sf) {
    sf->result = FMOD_System_PlaySound(sf->fmod_sys, FMOD_CHANNEL_FREE, 
        sf->sound, sf->pause, &(sf->channel));
    if (sf->result != FMOD_OK) {
        printf("FMOD error! (%d) %s\n", sf->result, FMOD_ErrorString(sf->result));
    }
    FMOD_Channel_SetMode(sf->channel,FMOD_LOOP_OFF);
    FMOD_Channel_IsPlaying(sf->channel, NULL);
}

void mx_start_snotify(void) {
    t_fmod sf;

    sf.sound = NULL;
    sf.fmod_sys = NULL;
    sf.channel = NULL;
    sf.pause = 0;
    initialize(&sf);
    load(&sf);
    play(&sf);
}
