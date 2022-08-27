// rotating_platform.inc.c
extern battle_timer;
#include "levels/wf/header.h"
#include "levels/wdw/header.h"
extern RPG_mode;
extern enemy_1;
extern enemy_2;
extern enemy_1_health;
extern enemy_2_health;
extern battle_id;
extern rpg_initializer;
extern rpg_init_timer;
extern current_turn;
extern mario_action_type;
extern bowser_action_type;
extern luigi_action_type;
extern MarioCurrHp;
extern BowserCurrHp;
extern LuigiCurrHp;
#include "actors/battle_mario/anim_header.h"
struct WFRotatingPlatformData {
    s16 unused;
    s16 scale;
    const Collision *collisionData;
    s16 collisionDistance;
};

static struct ObjectHitbox sThwompHitbox = {
    /* interactType:      */ INTERACT_SHOCK,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 72,
    /* height:            */ 50,
    /* hurtboxRadius:     */ 42,
    /* hurtboxHeight:     */ 40,
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
        //cur_obj_init_animation_and_extend_if_at_end
        obj_set_model(gCurrentObject, MODEL_BATTLE_MARIO);
        if (current_turn == 4){
            if (MarioCurrHp > 0){
                if ((mario_action_type == 1) && battle_timer > 121)  {
                cur_obj_init_animation(2);
                } 
                if ((mario_action_type == 1) && battle_timer < 121)  {
                cur_obj_init_animation(0);
                } 
                if ((mario_action_type == 2) | (mario_action_type == 3) | (mario_action_type == 4) && battle_timer > 122)  {
                cur_obj_init_animation(3);
                } 
                if ((mario_action_type == 2) | (mario_action_type == 3) | (mario_action_type == 4) && battle_timer < 122)  {
                cur_obj_init_animation(0);
                } 
            }
            
        } else if (MarioCurrHp <= 0){
                cur_obj_init_animation(1);
            } else {
        cur_obj_init_animation(0);
        }

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

void bhv_thwomp_car_init(void){
    obj_set_hitbox(o, &sThwompHitbox);
}

void bhv_thwomp_car(void){
    if (o->oBehParams2ndByte == 0){
        if (o->oPosZ >= 3400){
        o->oPosZ -= 3200;

    }
        o->oPosZ += 70.0f;
    }
    if (o->oBehParams2ndByte == 1){
        if (o->oPosZ <= 200){
        o->oPosZ += 3200;

    }
        o->oPosZ -= 70.0f;
    }
if (obj_check_if_collided_with_object(o, gMarioObject)){
        battle_id = GET_BPARAM1(o->oBehParams);
        
        rpg_initializer = 1;
        

        
    }
    
    
    if (GET_BPARAM1(o->oBehParams) == battle_id){
                if (rpg_init_timer >= 15){

        obj_mark_for_deletion(o);

            }
        }
}

void bhv_field_bowser(void){
if (RPG_mode == 0){
cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
        if (o->oDistanceToMario > 300.0f) {
            cur_obj_set_vel_from_mario_vel(10,1);
                } else {
        o->oForwardVel -=3;
        if (o->oForwardVel <= 0){
            o->oForwardVel = 0;
        }
    

    }
}
}

void bhv_field_luigi(void){
if (RPG_mode == 0){
cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
        if (o->oDistanceToMario > 600.0f) {
            cur_obj_set_vel_from_mario_vel(10,1);
            
    } else {
        o->oForwardVel -=3;
        if (o->oForwardVel <= 0){
            o->oForwardVel = 0;
        }
    }
}
}



