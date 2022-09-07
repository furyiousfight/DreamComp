// rotating_platform.inc.c
extern battle_timer;
#include "levels/wf/header.h"
#include "levels/wdw/header.h"
#include "src/game/camera.h"
extern rpg_denitializer;
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
s32 intro_increment = 0;
extern intro_timer;
s32 BowserXPos;
s32 BowserYPos;
s32 BowserZPos;
u32 fawful_cutscene;
u32 fawful_cutscene_timer;
extern mario_action_selected;
s32 FawfulX;
s32 FawfulY;
s32 FawfulZ;
extern death_timer;
s32 fawful_battle_won;
extern fawful_battle;

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
    /* radius:            */ 160,
    /* height:            */ 330,
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
                if ((mario_action_type == 1) && battle_timer > (210 - 29))  {
                cur_obj_init_animation(2);
                } 
                if ((mario_action_type == 1) && battle_timer < (210 - 29))  {
                cur_obj_init_animation(0);
                } 
                if ((mario_action_type == 2) | (mario_action_type == 3) | (mario_action_type == 4) && battle_timer > (210 - 28))  {
                cur_obj_init_animation(3);
                } 
                if ((mario_action_type == 2) | (mario_action_type == 3) | (mario_action_type == 4) && battle_timer < (210 - 28))  {
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
        obj_set_model(gCurrentObject, MODEL_BATTLE_DARK_TWOSER);
        if (current_turn == 4){
            if (BowserCurrHp > 0){
                if ((mario_action_type == 2 && mario_action_selected == 3) && battle_timer > (210 - 44))  {
                cur_obj_init_animation(4);
                } 
                if ((mario_action_type == 2 && mario_action_selected == 3) && battle_timer < (210 - 44))  {
                cur_obj_init_animation(0);
                } 
                if ((bowser_action_type == 1) && battle_timer > (210 - 29))  {
                cur_obj_init_animation(2);
                } 
                if ((bowser_action_type == 1) && battle_timer < (210 - 29))  {
                cur_obj_init_animation(0);
                } 
                if ((bowser_action_type == 3) | (bowser_action_type == 4) && battle_timer > (210 - 44))  {
                cur_obj_init_animation(4);
                } 
                if ((bowser_action_type == 3) | (bowser_action_type == 4) && battle_timer < (210 - 44))  {
                cur_obj_init_animation(0);
                } 
                if ((bowser_action_type == 2) && battle_timer > (210 - 64))  {
                cur_obj_init_animation(3);
                } 
                if ((bowser_action_type == 2) && battle_timer < (210 - 64))  {
                cur_obj_init_animation(0);
                } 
                
                
            }
            
        } else if (BowserCurrHp <= 0){
                cur_obj_init_animation(1);
            } else {
        cur_obj_init_animation(0);
        }

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

void bhv_battle_thwomp(void) {
        if (RPG_mode == 1){
        if (((o->oBehParams2ndByte == 1) && enemy_1 == 3) | ((o->oBehParams2ndByte == 2) && enemy_2 == 3)){
            obj_set_model(gCurrentObject, MODEL_THWOMP_CAR);
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

void bhv_thwomp_car_init(void){
    obj_set_hitbox(o, &sThwompHitbox);
}

void bhv_thwomp_car(void){
    if (o->oBehParams2ndByte == 0){
        if (o->oPosZ >= 3103){
        o->oPosZ -= 4903;

    }
        o->oPosZ += 70.0f;
    }
    if (o->oBehParams2ndByte == 1){
        if (o->oPosZ <= -1800){
        o->oPosZ += 4903;

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

void bhv_whomp_car(void){
    if (o->oBehParams2ndByte == 0){
        if (o->oPosZ >= 7219){
        o->oPosZ -= 8619;

    }
        o->oPosZ += 90.0f;
    }
    if (o->oBehParams2ndByte == 1){
        if (o->oPosZ <= -1400){
        o->oPosZ += 8619;

    }
        o->oPosZ -= 90.0f;
    }
if (obj_check_if_collided_with_object(o, gMarioObject)){
gMarioState->action = ACT_DEATH_ON_BACK;
        

        
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
o->oPosY = gMarioState->floorHeight;
        if (o->oDistanceToMario > 300.0f) {
            cur_obj_set_vel_from_mario_vel(10,1);
            cur_obj_init_animation(2);
                } else {
        o->oForwardVel -=3;
        if (o->oForwardVel <= 0){
            o->oForwardVel = 0;
            cur_obj_init_animation(1);
        }
    

    }
}
if (RPG_mode == 1){
    o->oForwardVel = 0;
}
}

void bhv_field_luigi(void){
if (RPG_mode == 0){
cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);

cur_obj_update_floor_height_and_get_floor();

    o->oPosY = gMarioState->floorHeight;


        if (o->oDistanceToMario > 600.0f) {
            cur_obj_set_vel_from_mario_vel(10,1);
            cur_obj_init_animation(2);
            
    } else {
        o->oForwardVel -=3;
        if (o->oForwardVel <= 0){
            o->oForwardVel = 0;
            cur_obj_init_animation(1);
        }
    }
}
if (RPG_mode == 1){
    o->oForwardVel = 0;
}
}


void bhv_intro_bowser(void){
    BowserXPos = o->oPosX;
    BowserYPos = o->oPosY;
    BowserZPos = o->oPosZ;
    o->oFloor = cur_obj_update_floor_height_and_get_floor();
    if (RPG_mode == 0){
        if (o->oForwardVel == 0) {
        cur_obj_init_animation(1);
    }
    if (intro_increment == 0){
cur_obj_rotate_yaw_toward(16383, 0x600);
    }
if ((o->oFaceAngleYaw == 16383) && intro_increment == 0){
    cur_obj_init_animation(2);
    o->oForwardVel = 10;
    intro_increment = 1;
}
if ((BowserXPos > 1200) && intro_increment == 1){
    o->oForwardVel = 0;
    cur_obj_rotate_yaw_toward(32767, 0x600);

}
if (o->oFaceAngleYaw == 32767){
    intro_increment = 2;
}
if (intro_increment == 2){
    cur_obj_init_animation(2);
    o->oForwardVel = 10;
    intro_increment = 3;
        }
        if ((BowserZPos < -1300) && intro_increment == 3){
    mark_obj_for_deletion(o);
    intro_increment = 4;

}
}

}
    
void bhv_library_door(void){
if (intro_increment == 3){
    mark_obj_for_deletion(o);
    obj_explode_and_spawn_coins(100, 0);
play_sound(SOUND_GENERAL_BREAK_BOX, gGlobalSoundSource);
}
}

void bhv_out_of_bounds(void){
    if (o->oDistanceToMario < 2040){
o->oOpacity = 255 - o->oDistanceToMario/8;
    } else {
        o->oOpacity = 0;
    }
}

void bhv_dumpster_loop(void){
        if (death_timer > 1) {

        
        cur_obj_init_animation_with_accel_and_sound(1, 2);
    }
    if(gMarioState->floor->type == SURFACE_DIALOG && gMarioState->floor->force == 0001 && fawful_cutscene == 0 && fawful_battle_won == 0){
cur_obj_init_animation_with_accel_and_sound(0, 2);

    
    play_sound(SOUND_OBJ_UKIKI_CHATTER_LONG, gGlobalSoundSource);
    fawful_cutscene = 1;

    }
        if (fawful_cutscene == 1 && fawful_cutscene_timer > 3 && fawful_battle_won == 0){
spawn_object_abs_with_rot(o, 0, MODEL_TWOSER, bhvFieldFawful, 19905, 337, 1696, 0, 0, 0);
fawful_cutscene = 2;
    }
}



void bhv_field_fawful(void){
    if (death_timer > 1) {
        obj_mark_for_deletion(o);
    }
        if (fawful_battle_won == 1) {
        obj_mark_for_deletion(o);
    }
FawfulX = o->oPosX;
FawfulY = o->oPosY;
FawfulZ = o->oPosZ;

//o->oPosY = o->oFloorHeight;

    if (o->oForwardVel == 0 ){
        cur_obj_init_animation(1);
    }

if (fawful_cutscene == 2 && fawful_cutscene_timer > 10 && fawful_battle_won == 0){


    
    fawful_cutscene_timer = 0;
    fawful_cutscene = 3;
}
if (fawful_cutscene == 3 && fawful_cutscene_timer > 10 && fawful_battle_won == 0){




    set_mario_animation(gMarioState, MARIO_ANIM_IDLE_HEAD_LEFT);

    fawful_cutscene_timer = 0;
    fawful_cutscene = 4;
}
if (fawful_cutscene == 4 && fawful_battle_won == 0){

    cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x600);
    if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_FRONT,
        DIALOG_FLAG_TEXT_DEFAULT, CUTSCENE_DIALOG, DIALOG_021)) {
            rpg_initializer = 1;
            battle_id = 100;

            fawful_cutscene = 5;

        }


    }
}



