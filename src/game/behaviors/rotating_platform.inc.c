// rotating_platform.inc.c
extern battle_timer;
#include "levels/wf/header.h"
#include "levels/wdw/header.h"
extern RPG_mode;
extern enemy_1;
extern enemy_2;
extern enemy_1_health;
extern enemy_2_health;
struct WFRotatingPlatformData {
    s16 unused;
    s16 scale;
    const Collision *collisionData;
    s16 collisionDistance;
};

struct WFRotatingPlatformData sWFRotatingPlatformData[] = {
    { 0, 100, wf_seg7_collision_rotating_platform, 2000 },
    { 0, 150, wdw_seg7_collision_rotating_platform, 1000 }
};

void bhv_wf_rotating_wooden_platform_loop(void) {
    if (o->oAction == 0) {
        o->oAngleVelYaw = 0;
        if (o->oTimer > 60) {
            o->oAction++;
        }
    } else {
        o->oAngleVelYaw = 0x100;
        if (o->oTimer > 126) {
            o->oAction = ROTATING_PLATFORM_ACT_STOPPED;
        }
        cur_obj_play_sound_1(SOUND_ENV_ELEVATOR2);
    }
    cur_obj_rotate_face_angle_using_vel();
}

void bhv_rotating_platform_loop(void) {
    s8 speed = GET_BPARAM1(o->oBehParams);
    if (o->oTimer == 0) {
        obj_set_collision_data(o, sWFRotatingPlatformData[o->oBehParams2ndByte].collisionData);
        o->oCollisionDistance = sWFRotatingPlatformData[o->oBehParams2ndByte].collisionDistance;
        cur_obj_scale(sWFRotatingPlatformData[o->oBehParams2ndByte].scale * 0.01f);
    }
    o->oAngleVelYaw = speed << 4;
    o->oFaceAngleYaw += o->oAngleVelYaw;
}

void bhv_battle_box(void) {
    if (battle_timer == 0) {
        obj_set_model(gCurrentObject, MODEL_NONE);
    } else {
        obj_set_model(gCurrentObject, MODEL_BATTLEBOX);
    }

}

void bhv_battle_mario(void) {
    if (RPG_mode == 1){
        obj_set_model(gCurrentObject, MODEL_MARIO);
    } else {
        obj_set_model(gCurrentObject, MODEL_NONE);
    }
}

void bhv_battle_bowser(void) {
    if (RPG_mode == 1){
        obj_set_model(gCurrentObject, MODEL_TWOSER);
    } else {
        obj_set_model(gCurrentObject, MODEL_NONE);
    }
}

void bhv_battle_goomba(void) {
    if (RPG_mode == 1){
        if (((o->oBehParams2ndByte == 1) && enemy_1 == 1) | ((o->oBehParams2ndByte == 2) && enemy_2 == 1)){
            obj_set_model(gCurrentObject, MODEL_GOOMBA);
            if ((o->oBehParams2ndByte == 1) && enemy_1_health <= 0){
                obj_set_model(gCurrentObject, MODEL_NONE);
            }
            if ((o->oBehParams2ndByte == 2) && enemy_2_health <= 0){
                obj_set_model(gCurrentObject, MODEL_NONE);
            }
        }

         else {
            obj_set_model(gCurrentObject, MODEL_NONE);
        }
    }
}

void bhv_battle_koopa(void) {
    if (RPG_mode == 1){
        if (((o->oBehParams2ndByte == 1) && enemy_1 == 2) | ((o->oBehParams2ndByte == 2) && enemy_2 == 2)){
            obj_set_model(gCurrentObject, MODEL_KOOPA_WITH_SHELL);
        }
         else {
            obj_set_model(gCurrentObject, MODEL_NONE);
        }
    }
}




