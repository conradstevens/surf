#include "snow_scene.h"
#include "snow_flake.h"


SnowScene::SnowScene() : Scene(){
    SnowFlake::load();
    for(int i = 0; i < 60; i++) {
        spawn_random_snow();
    }
}

void SnowScene::spawn_random_snow() {

    float pos_x = 2.0f * ((float) rand() / RAND_MAX) - 1;
    float x_dir = 0.2f * ((float) rand() / RAND_MAX);
    float rotation = 3.1415f * 0.05f * ((float) rand() / RAND_MAX) - 0.5f * (3.1415f * 0.05f);
    float speed = 0.0007f * ((float) rand() / RAND_MAX) + 0.0002;
    float scale = 1.5f * ((float) rand() / RAND_MAX) + 0.5f;

    auto* snow_flake = new SnowFlake{scale, {x_dir, -1.0f}, speed, rotation};
    addEntity(snow_flake, pos_x, 1.1f);
}

void SnowScene::step(float time_step) {
    time_accrued += time_step;

    if (time_accrued >= 10.0f) { // spawn 10 a second
        spawn_random_snow();
        time_accrued = 0.0f;
    }
}
