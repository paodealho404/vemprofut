#include "soundboard.h"
#include <SFML/Audio.h>
#include <stdio.h>

#define SOUND_VOLUME 20
#define GOAL_SOUND_VOLUME 40

static struct {
    sfMusic *background_music;
    sfMusic *goal_music;
    sfMusic *initial_music;
    sfMusic *tafarel_music;
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

    self.initial_music = sfMusic_createFromFile("../../../asset/initial.wav");
    if (!self.initial_music) {
        fprintf(stderr, "Failed to load sound file: %s\n", "../../../asset/initial.wav");
        return -1;
    }

    self.tafarel_music = sfMusic_createFromFile("../../../asset/tafarel.wav");
    if (!self.tafarel_music) {
        fprintf(stderr, "Failed to load sound file: %s\n", "../../../asset/tafarel.wav");
        return -1;
    }

    sfMusic_setVolume(self.initial_music, GOAL_SOUND_VOLUME);
    sfMusic_setLoop(self.initial_music, sfFalse);

    sfMusic_setVolume(self.tafarel_music, GOAL_SOUND_VOLUME-5);
    sfMusic_setLoop(self.tafarel_music, sfFalse);

    return 0;
}

void play_initial_music(void) {
    sfMusic_play(self.initial_music);
}

void play_background_music(void) {
    sfMusic_play(self.background_music);
}

void play_goal_sound(void) {
    sfTime t = {0};
    sfMusic_setPlayingOffset(self.goal_music, t);
    sfMusic_play(self.goal_music);
}

void play_tafarel_sound(void) {
    sfTime t = {0};
    sfMusic_setPlayingOffset(self.tafarel_music, t);
    sfMusic_play(self.tafarel_music);
}

void destroy_sound_board(void) {
    sfMusic_destroy(self.background_music);
    sfMusic_destroy(self.goal_music);
    sfMusic_destroy(self.initial_music);
    sfMusic_destroy(self.tafarel_music);
}