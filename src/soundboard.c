#include "soundboard.h"
#include <SFML/Audio.h>
#include <stdio.h>

#define SOUND_VOLUME 20
#define GOAL_SOUND_VOLUME 40

static struct {
    sfMusic *background_music;
    sfMusic *goal_music;
} self = {};

int init_sound_board(void) {
    self.background_music = sfMusic_createFromFile("../../../asset/background.wav");
    if (!self.background_music) {
        fprintf(stderr, "Failed to load sound file: %s\n", "../../../asset/background.wav");
        return -1;
    }

    sfMusic_setVolume(self.background_music, SOUND_VOLUME);
    sfMusic_setLoop(self.background_music, sfTrue);
    sfMusic_play(self.background_music);

    self.goal_music = sfMusic_createFromFile("../../../asset/goal.wav");
    if (!self.goal_music) {
        fprintf(stderr, "Failed to load sound file: %s\n", "../../../asset/goal.wav");
        return -1;
    }

    sfMusic_setVolume(self.goal_music, GOAL_SOUND_VOLUME);
    sfMusic_setLoop(self.goal_music, sfFalse);

    return 0;
}


void play_background_music(void) {
    sfMusic_play(self.background_music);
}

void play_goal_sound(void) {
    sfTime t = {0};
    sfMusic_setPlayingOffset(self.goal_music, t);
    sfMusic_play(self.goal_music);
}


void destroy_sound_board(void) {
    sfMusic_destroy(self.background_music);
    sfMusic_destroy(self.goal_music);
}