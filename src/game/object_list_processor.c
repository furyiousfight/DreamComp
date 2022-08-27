#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "engine/behavior_script.h"
#include "engine/graph_node.h"
#include "engine/surface_collision.h"
#include "engine/surface_load.h"
#include "engine/math_util.h"
#include "interaction.h"
#include "level_update.h"
#include "mario.h"
#include "memory.h"
#include "object_collision.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "platform_displacement.h"
#include "spawn_object.h"
#include "puppyprint.h"
#include "puppylights.h"
#include "profiling.h"
#include "actors/fountain/header.h"
#include "levels/bob/header.h"
#include "levels/wf/header.h"
#include "game_init.h"
#include "actors/Battle/header.h"
#include "actors/Battle_Actions/header.h"
#include "text_strings.h"
#include "actors/DRExplosion/header.h"
#include "actors/determination/geo_header.h"
extern rpg_initializer;
s32 PlatformMoves;
extern u8 explosion_segment[];
extern u8 lightpath_segment[];
extern u8 buy1_segment[];
extern u8 ad_segment[];
extern u8 buy2_segment[];
extern u8 look_segment[];
extern u8 deals_segment[];
extern u8 fight_segment[];
extern u8 act_segment[];
extern u8 magic_segment[];
extern u8 defend_segment[];
extern u8 spare_segment[];
extern u8 item_segment[];
extern menu_pos;
s32 vertical_menu;
s32 vertical_option;
s32 vertical_option_max = 2;
extern selection_pos;
u32 battle_id;
u32 dodge_section;
extern void dma_read(u8 *dest, u8 *srcStart, u8 *srcEnd);
u32 frame2;
u32 third_speed2;
u32 frame3;
u32 third_speed3;
u32 frame4;
u32 third_speed4;
u32 frame5;
u32 third_speed5;
u32 frame6;
u32 third_speed6;
u32 frame7;
u32 third_speed7;
u32 RPG_mode;
u32 battle_option = 0;
u32 frame8;
u32 frame9;
u32 frame10;
u32 frame11;
u32 frame12;
u32 frame13;
u32 framedelay = 10;
u32 MarioMaxHp;
s32 MarioCurrHp = 90;
u32 BowserMaxHp;
s32 BowserCurrHp = 110;
u32 LuigiMaxHp;
s32 LuigiCurrHp = 70;
extern HealthRatioMario;
extern HealthRatioBowser;
extern HealthRatioLuigi;
u32 MarioHealthTextOffset;
u32 LuigiHealthTextOffset;
u32 BowserHealthTextOffset;
u32 MenuPhase;
extern current_turn;
extern battle_pos;
s32 battle_timer =0;
u32 init_timer;
extern TPRatio;
s32 CurrTP;
extern TPOffset;
u32 enemy_1;
u32 enemy_2;
s32 enemy_1_health;
s32 enemy_1_max_health;
s32 enemy_2_health;
s32 enemy_2_max_health;
u32 enemy_1_health_ratio = 38;
u32 enemy_2_health_ratio;
u32 enemy_1_spare;
u32 enemy_2_spare;
extern u8 Enemy1Text[];
extern mario_enemy_selected;
extern mario_action_selected;
extern mario_action_type;
extern bowser_enemy_selected;
extern bowser_action_selected;
extern bowser_action_type;
extern luigi_enemy_selected;
extern luigi_action_selected;
extern luigi_action_type;
u32 enemy_selected;
extern menu_phase;
s32 MarioOWX;
s32 MarioOWY;
s32 MarioOWZ;
s32 Mario_OW_Pos;
extern Enemy1Ratio;
extern Enemy2Ratio;
extern rpg_init_timer;
u32 mario_base_damage = 30;
u32 luigi_base_damage = 20;
u32 bowser_base_damage = 45;
f32 mario_multiplier = 1;
f32 luigi_multiplier = 1;
f32 bowser_multiplier = 1;
f32 attack_phase;
u32 mario_tot_damage;
u32 bowser_tot_damage;
u32 luigi_tot_damage;
extern enemy_1_init_explosion;
extern enemy_2_init_explosion;
extern enemy_1_mercy;
extern enemy_2_mercy;
u32 SpareRatio;
extern DamageFadeOut;
extern Enemy1MercyRatio;
extern Enemy2MercyRatio;
u32 checked;
extern SquishDamageTimer;
extern Battle_Won;
u32 rpg_denitializer;
u32 HealthCycleTimer;
extern u8 determination_segment[];
u32 frame14;
u32 third_speed14;
extern LastLevel;
extern LastArea;
extern LastBonfire;
extern DeterminationTimer;
u32 death_timer;
u32 death_timer_init;
u32 attack_rotation;
/**
 * Flags controlling what debug info is displayed.
 */
s32 gDebugInfoFlags;

/**
 * The number of times per frame find_floor found no floor beneath an
 * object, and therefore either returned a dynamic floor or NULL.
 */
s32 gNumFindFloorMisses;

/**
 * An unused debug counter with the label "WALL".
 */
s32 gUnknownWallCount;

/**
 * Roughly the number of objects that have been processed this frame so far.
 * A bug in update_terrain_objects makes this count inaccurate.
 */
u32 gObjectCounter;

/**
 * The number of times find_floor, find_ceil, and find_wall_collisions have been called respectively.
 */
struct NumTimesCalled gNumCalls;

/**
 * An array of debug controls that could be used to tweak in-game parameters.
 * The only used rows are [4] and [5] (effectinfo and enemyinfo).
 */
s16 gDebugInfo[16][8];
s16 gDebugInfoOverwrite[16][8];

/**
 * A set of flags to control which objects are updated on a given frame.
 * This is used during dialog and cutscenes to freeze most objects in place.
 */
u32 gTimeStopState;

/**
 * The pool that objects are allocated from.
 */
struct Object gObjectPool[OBJECT_POOL_CAPACITY];

/**
 * A special object whose purpose is to act as a parent for macro objects.
 */
struct Object gMacroObjectDefaultParent;

/**
 * A pointer to gObjectListArray.
 * Given an object list index idx, gObjectLists[idx] is the head of a doubly
 * linked list of all currently spawned objects in the list.
 */
struct ObjectNode *gObjectLists;

/**
 * A singly linked list of available slots in the object pool.
 */
struct ObjectNode gFreeObjectList;

/**
 * The object representing Mario.
 */
struct Object *gMarioObject;

/**
 * An object variable that may have been used to represent the planned
 * second player. This is speculation, based on its position and its usage in
 * shadow.c.
 */
// struct Object *gLuigiObject;

/**
 * The object whose behavior script is currently being updated.
 * This object is used frequently in object behavior code, and so is often
 * aliased as "o".
 */
struct Object *gCurrentObject;

/**
 * The next object behavior command to be executed.
 */
const BehaviorScript *gCurBhvCommand;

/**
 * The number of objects that were processed last frame, which may miss some
 * objects that were spawned last frame and all objects that were spawned this
 * frame. It also includes objects that were unloaded last frame.
 * Besides this, a bug in update_terrain_objects makes this count inaccurate.
 */
s16 gPrevFrameObjectCount;

/**
 * The total number of surface nodes allocated (a node is allocated for each
 * spatial partition cell that a surface intersects).
 */
s32 gSurfaceNodesAllocated;

/**
 * The total number of surfaces allocated.
 */
s32 gSurfacesAllocated;

/**
 * The number of nodes that have been created for surfaces.
 */
s32 gNumStaticSurfaceNodes;

/**
 * The number of surfaces in the pool.
 */
s32 gNumStaticSurfaces;

/**
 * A pool used by chain chomp and wiggler to allocate their body parts.
 */
struct MemoryPool *gObjectMemoryPool;

s16 gCollisionFlags = COLLISION_FLAGS_NONE;
TerrainData *gEnvironmentRegions;
s32 gEnvironmentLevels[20];
RoomData gDoorAdjacentRooms[60][2];
s16 gMarioCurrentRoom;
s16 gTHIWaterDrained;
s16 gTTCSpeedSetting;
s16 gMarioShotFromCannon;
s16 gCCMEnteredSlide;
s16 gNumRoomedObjectsInMarioRoom;
s16 gNumRoomedObjectsNotInMarioRoom;
s16 gWDWWaterLevelChanging;
s16 gMarioOnMerryGoRound;

/**
 * Nodes used to represent the doubly linked object lists.
 */
struct ObjectNode gObjectListArray[16];

/**
 * The order that object lists are processed in a frame.
 */
s8 sObjectListUpdateOrder[] = { OBJ_LIST_SPAWNER,
                                OBJ_LIST_SURFACE,
                                OBJ_LIST_POLELIKE,
                                OBJ_LIST_PLAYER,
                                OBJ_LIST_PUSHABLE,
                                OBJ_LIST_GENACTOR,
                                OBJ_LIST_DESTRUCTIVE,
                                OBJ_LIST_LEVEL,
                                OBJ_LIST_DEFAULT,
                                OBJ_LIST_UNIMPORTANT,
                                -1 };

/**
 * Info needed to spawn particles and keep track of which have been spawned for
 * an object.
 */
struct ParticleProperties {
    u32 particleFlag;
    u32 activeParticleFlag;
    ModelID16 model;
    const BehaviorScript *behavior;
};

/**
 * A table mapping particle flags to various properties use when spawning a particle.
 */
struct ParticleProperties sParticleTypes[] = {
    { PARTICLE_DUST,                 ACTIVE_PARTICLE_DUST,                 MODEL_MIST,                 bhvMistParticleSpawner },
    { PARTICLE_VERTICAL_STAR,        ACTIVE_PARTICLE_V_STAR,               MODEL_NONE,                 bhvVertStarParticleSpawner },
    { PARTICLE_HORIZONTAL_STAR,      ACTIVE_PARTICLE_H_STAR,               MODEL_NONE,                 bhvHorStarParticleSpawner },
    { PARTICLE_SPARKLES,             ACTIVE_PARTICLE_SPARKLES,             MODEL_SPARKLES,             bhvSparkleParticleSpawner },
    { PARTICLE_BUBBLE,               ACTIVE_PARTICLE_BUBBLE,               MODEL_BUBBLE,               bhvBubbleParticleSpawner },
    { PARTICLE_WATER_SPLASH,         ACTIVE_PARTICLE_WATER_SPLASH,         MODEL_WATER_SPLASH,         bhvWaterSplash },
    { PARTICLE_IDLE_WATER_WAVE,      ACTIVE_PARTICLE_IDLE_WATER_WAVE,      MODEL_IDLE_WATER_WAVE,      bhvIdleWaterWave },
    { PARTICLE_PLUNGE_BUBBLE,        ACTIVE_PARTICLE_PLUNGE_BUBBLE,        MODEL_WHITE_PARTICLE_SMALL, bhvPlungeBubble },
    { PARTICLE_WAVE_TRAIL,           ACTIVE_PARTICLE_WAVE_TRAIL,           MODEL_WAVE_TRAIL,           bhvWaveTrail },
    { PARTICLE_FIRE,                 ACTIVE_PARTICLE_FIRE,                 MODEL_RED_FLAME,            bhvFireParticleSpawner },
    { PARTICLE_SHALLOW_WATER_WAVE,   ACTIVE_PARTICLE_SHALLOW_WATER_WAVE,   MODEL_NONE,                 bhvShallowWaterWave },
    { PARTICLE_SHALLOW_WATER_SPLASH, ACTIVE_PARTICLE_SHALLOW_WATER_SPLASH, MODEL_NONE,                 bhvShallowWaterSplash },
    { PARTICLE_LEAF,                 ACTIVE_PARTICLE_LEAF,                 MODEL_NONE,                 bhvLeafParticleSpawner },
    { PARTICLE_SNOW,                 ACTIVE_PARTICLE_SNOW,                 MODEL_NONE,                 bhvSnowParticleSpawner },
    { PARTICLE_BREATH,               ACTIVE_PARTICLE_BREATH,               MODEL_NONE,                 bhvBreathParticleSpawner },
    { PARTICLE_DIRT,                 ACTIVE_PARTICLE_DIRT,                 MODEL_NONE,                 bhvDirtParticleSpawner },
    { PARTICLE_MIST_CIRCLE,          ACTIVE_PARTICLE_MIST_CIRCLE,          MODEL_NONE,                 bhvMistCircParticleSpawner },
    { PARTICLE_TRIANGLE,             ACTIVE_PARTICLE_TRIANGLE,             MODEL_NONE,                 bhvTriangleParticleSpawner },
    { PARTICLE_NONE, ACTIVE_PARTICLE_NONE, MODEL_NONE, NULL },
};

/**
 * Copy position, velocity, and angle variables from MarioState to the Mario
 * object.
 */
void copy_mario_state_to_object(void) {
    s32 i = 0;
    // L is real
    if (gCurrentObject != gMarioObject) {
        i++;
    }

    gCurrentObject->oVelX = gMarioStates[i].vel[0];
    gCurrentObject->oVelY = gMarioStates[i].vel[1];
    gCurrentObject->oVelZ = gMarioStates[i].vel[2];

    gCurrentObject->oPosX = gMarioStates[i].pos[0];
    gCurrentObject->oPosY = gMarioStates[i].pos[1];
    gCurrentObject->oPosZ = gMarioStates[i].pos[2];

    gCurrentObject->oMoveAnglePitch = gCurrentObject->header.gfx.angle[0];
    gCurrentObject->oMoveAngleYaw = gCurrentObject->header.gfx.angle[1];
    gCurrentObject->oMoveAngleRoll = gCurrentObject->header.gfx.angle[2];

    gCurrentObject->oFaceAnglePitch = gCurrentObject->header.gfx.angle[0];
    gCurrentObject->oFaceAngleYaw = gCurrentObject->header.gfx.angle[1];
    gCurrentObject->oFaceAngleRoll = gCurrentObject->header.gfx.angle[2];

    gCurrentObject->oAngleVelPitch = gMarioStates[i].angleVel[0];
    gCurrentObject->oAngleVelYaw = gMarioStates[i].angleVel[1];
    gCurrentObject->oAngleVelRoll = gMarioStates[i].angleVel[2];
}

/**
 * Spawn a particle at gCurrentObject's location.
 */
void spawn_particle(u32 activeParticleFlag, ModelID16 model, const BehaviorScript *behavior) {
    if (!(gCurrentObject->oActiveParticleFlags & activeParticleFlag)) {
        struct Object *particle;
        gCurrentObject->oActiveParticleFlags |= activeParticleFlag;
        particle = spawn_object_at_origin(gCurrentObject, 0, model, behavior);
        obj_copy_pos_and_angle(particle, gCurrentObject);
    }
}

/**
 * Mario's primary behavior update function.
 */
void bhv_mario_update(void) {
    u32 particleFlags = 0;
    s32 i;
    if (current_turn != 4){
    attack_rotation++;
    }
    if (attack_rotation > 9) {
        attack_rotation = 0;
    }
    print_text_fmt_int(10, 10, "attack_rotation = %d", attack_rotation);
    /*
    if (battle_timer == 200) {
        spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_BULLET_BILL, bhvBulletBill, 28880, 2587, -31402, 0, 0, 0);
    }
    if (battle_timer == 195) {
        spawn_object_abs_with_rot(gCurrentObject, 0, MODEL_BULLET_BILL, bhvBulletBill, 27398, 2804, -31402, 0, 0, 0);
    } */

    battle_timer--;
    
    if (battle_timer < 0) {
        battle_timer = 0;
    }
    DeterminationTimer--;
    if (DeterminationTimer < 0) {
        DeterminationTimer = 0;
    }
    MarioMaxHp = 90;

if (dodge_section == 0){
HealthCycleTimer++;
if (HealthCycleTimer > 2) {
    HealthCycleTimer = 0;
}
}
/*
print_text_fmt_int(0,0,"LastLevel: %d", LastLevel);
print_text_fmt_int(0,15,"LastArea: %d", LastArea);
print_text_fmt_int(0,30,"LastBonfire: %d", LastBonfire);

print_text_fmt_int(0, 80, "gCurrLevelNum: %d", gCurrLevelNum);
print_text_fmt_int(0, 95, "gCurrAreaIndex: %d", gCurrAreaIndex);
*/
//print_text_fmt_int(0, 110, "death_timer: %d", death_timer);
if (death_timer_init == 1){
death_timer++;
}
if (MarioCurrHp <= 0 && BowserCurrHp <= 0 && LuigiCurrHp <= 0) {
    if(death_timer_init == 0){
        death_timer_init = 1;
    }
        if (death_timer_init == 1){
        level_trigger_warp(gMarioState, WARP_OP_BONFIRE);
        if (death_timer == 29) {
        MarioCurrHp = MarioMaxHp;
        BowserCurrHp = BowserMaxHp;
        LuigiCurrHp = LuigiMaxHp;
            RPG_mode = 0;
            death_timer_init = 0;
            death_timer = 0;
        }
        }
    }



//print_text_fmt_int(0, 180, "HealthCycleTimer: %d", HealthCycleTimer);
    if (CurrTP < 9){
        TPOffset = 6;
    }
    if ((CurrTP < 99) && (CurrTP > 9)){
        TPOffset = 3;
    }
    if (CurrTP >= 100){
        TPOffset = 0;
        CurrTP = 100;
    }
    if (MarioCurrHp < 10){
        MarioHealthTextOffset = 6;
    }
    if (MarioCurrHp > 10){
        MarioHealthTextOffset = 0;
    }
    if (LuigiCurrHp < 10){
        LuigiHealthTextOffset = 6;
    }
    if (LuigiCurrHp > 10){
        LuigiHealthTextOffset = 0;
    }
    if (BowserCurrHp < 100){
        BowserHealthTextOffset = 6;
    }
    if (BowserCurrHp < 10){
        BowserHealthTextOffset = 12;
    }
    if (BowserCurrHp > 100){
        BowserHealthTextOffset = 0;
    }

    if (MarioCurrHp < 0) {
        MarioCurrHp = 0;
    }
        if(MarioCurrHp > MarioMaxHp){
        MarioCurrHp = MarioMaxHp;
    }
    //print_text_fmt_int(80,80, "Hp: %d", MarioCurrHp);
    BowserMaxHp = 110;

   
    if (BowserCurrHp < 0) {
        BowserCurrHp = 0;
    }
        if(BowserCurrHp > BowserMaxHp){
        BowserCurrHp = BowserMaxHp;
    }
    LuigiMaxHp = 70;

 
    if (LuigiCurrHp < 0) {
        LuigiCurrHp = 0;
    }
        if(LuigiCurrHp > LuigiMaxHp){
        LuigiCurrHp = LuigiMaxHp;
    }
     if (current_turn == -1){
        current_turn = 0;
    }
    if ((current_turn != 4) && Battle_Won == 0){
        battle_pos = 0;
        attack_phase = 0;
    }
         if (((enemy_1_health > 1) && enemy_2_health > 1) | RPG_mode == 0){
        Battle_Won = 0;
    }
    if (((enemy_1_health <= 0) && enemy_2_health <= 0) && RPG_mode == 1){
        Battle_Won = 1;
    }
    //print_text_fmt_int(20,20, "Battle_Won %d", Battle_Won);
    if ((Battle_Won == 1) && current_turn == 4){
        current_turn = 1;
        battle_timer = 0;
    }
    if ((current_turn != 4) && Battle_Won == 1){
        battle_pos = -107;
        attack_phase = 0;
        rpg_denitializer = 1;
    }
    if (current_turn == 1){
        battle_pos = 107;
    }
    if (current_turn == 2){
        battle_pos = 214;
    }
    if ((current_turn > 2) && init_timer == 0){
        current_turn++;



        vertical_menu = 0;
        vertical_option = 1;

        MenuPhase = 0;
    }
    if ((current_turn > 3) && init_timer == 0){
        current_turn == 0;
        dodge_section = 1;
        battle_timer = 210;
        init_timer = 1;
        vertical_menu = 0;
        vertical_option = 1;
        framedelay = 0;
        MenuPhase = 0;
        CurrTP += 15;
    }
    if (dodge_section == 0){
        menu_pos = 0;
        init_timer = 0;
    }
    if (dodge_section == 1){
        menu_pos = -58;
        
    } 
    if ((battle_timer == 0) && dodge_section == 1){
        mario_enemy_selected = 0;
        mario_action_selected = 0;
        mario_action_type = 0;
        bowser_enemy_selected = 0;
        bowser_action_selected = 0;
        bowser_action_type = 0;
        luigi_enemy_selected = 0;
        luigi_action_selected = 0;
        luigi_action_type = 0;
        dodge_section = 0;
        current_turn = 0;
    }

    //print_text_fmt_int(20,60, "mario enemy selected %d", mario_enemy_selected);
    //print_text_fmt_int(20,80, "mario action selected %d", mario_action_selected);
    //print_text_fmt_int(20,100, "mario action type %d", mario_action_type);

    //print_text_fmt_int(20,60, "bowser enemy selected %d", bowser_enemy_selected);
    //print_text_fmt_int(20,80, "bowser action selected %d", bowser_action_selected);
    //print_text_fmt_int(20,100, "bowser action type %d", bowser_action_type);

    //print_text_fmt_int(20,60, "luigi enemy selected %d", luigi_enemy_selected);
    //print_text_fmt_int(20,80, "luigi action selected %d", luigi_action_selected);
    //print_text_fmt_int(20,100, "luigi action type %d", luigi_action_type);

    //print_text_fmt_int(20,100, "enemy selected %d", enemy_selected);
    //print_text_fmt_int(20,140, "current turn %d", current_turn);
    //print_text_fmt_int(20,160, "menu phase %d", menu_phase);

    //print_text_fmt_int(80,100, "dodge_section: %d", dodge_section);
    //print_text_fmt_int(80,120, "battle_timer: %d", battle_timer);

//print_text_fmt_int(80,140, "enemy 1 mercy: %d", enemy_1_mercy);

    if (battle_id == 1){
    enemy_1 = 1; //goomba
    enemy_2 = 1; //goomba
    }
    if (battle_id == 2){
    enemy_1 = 2; //goomba
    enemy_2 = 2; //koopa
    }
    if (enemy_1 == 1){
    Enemy1Ratio = enemy_1_health / 2.105;
    }
    if (enemy_2 == 1){
    Enemy2Ratio = enemy_2_health / 2.105;
    }
    if (enemy_1 == 2){
    Enemy1Ratio = enemy_1_health / 3.157;
    }
    if (enemy_2 == 2){
    Enemy2Ratio = enemy_2_health / 3.157;
    }


    enemy_1_spare = enemy_1_mercy / 2.563;
    enemy_2_spare = enemy_2_mercy / 2.563;
    HealthRatioMario = MarioCurrHp / 2.307;
    HealthRatioBowser = BowserCurrHp / 2.894;
    HealthRatioLuigi = LuigiCurrHp / 1.842;
    TPRatio = CurrTP / 1.06;
    
    if (vertical_option <= 1){
        vertical_option = 1;
    }
    if (vertical_option == 1){
    selection_pos = 26;
    }
    if (vertical_option == 2){
    selection_pos = 13;
    }
    if (vertical_option == 3){
    selection_pos = 0;
    }
    if (vertical_option >= vertical_option_max){
        vertical_option = vertical_option_max;
    }
    if (battle_option == 5) {
        battle_option = 4;
    }
    if (battle_option == -1) {
        battle_option = 0;
    }

if (MarioCurrHp <= 0 && current_turn == 0){
battle_option = 0;
                menu_phase = 0;
        mario_action_type = 5;
        current_turn++;
    
}
if (BowserCurrHp <= 0 && current_turn == 1){
battle_option = 0;
                menu_phase = 0;
                bowser_action_type=5;
        current_turn++;
    
}
if (LuigiCurrHp <= 0 && current_turn == 2){
               battle_option = 0;
                menu_phase = 0;
        luigi_action_type=5;
        current_turn++;
    
}


/*
print_text_fmt_int(20,20, "X %d", MarioOWX);
print_text_fmt_int(20,40, "Y %d", MarioOWY);
print_text_fmt_int(20,60, "Z %d", MarioOWZ);
*/

    u8 *texture_location_in_ram2 = segmented_to_virtual(&wf_dl_lit_up_path_base_rgba16);

    dma_read(texture_location_in_ram2,(frame2*2048)+lightpath_segment,(frame2*2048)+lightpath_segment+2048);
        third_speed2++;
        if (third_speed2 >= 3){
            frame2++;
            third_speed2 = 0;
            if (frame2 > 2) {
        frame2 = 0;
        }
        }

    u8 *texture_location_in_ram3 = segmented_to_virtual(&wf_dl_BUY_base_rgba16);


    dma_read(texture_location_in_ram3,(frame3*4800)+buy1_segment,(frame3*4800)+buy1_segment+4800);
        third_speed3++;
        if (third_speed3 >= 4){
            frame3++;
            third_speed3 = 0;
            if (frame3 > 1) {
        frame3 = 0;
        }
        }

    u8 *texture_location_in_ram4 = segmented_to_virtual(&wf_dl_AD_base_rgba16);


    dma_read(texture_location_in_ram4,(frame4*4800)+ad_segment,(frame4*4800)+ad_segment+4800);
        third_speed4++;
        if (third_speed4 >= 4){
            frame4++;
            third_speed4 = 0;
            if (frame4 > 1) {
        frame4 = 0;
        }
        }

           u8 *texture_location_in_ram5 = segmented_to_virtual(&wf_dl_BUY2_base_rgba16);


    dma_read(texture_location_in_ram5,(frame5*4800)+buy2_segment,(frame5*4800)+buy2_segment+4800);
        third_speed5++;
        if (third_speed5 >= 4){
            frame5++;
            third_speed5 = 0;
            if (frame5 > 1) {
        frame5 = 0;
        }
        }

           u8 *texture_location_in_ram6 = segmented_to_virtual(&wf_dl_LOOK_base_rgba16);


    dma_read(texture_location_in_ram6,(frame6*4800)+look_segment,(frame6*4800)+look_segment+4800);
        third_speed6++;
        if (third_speed6 >= 4){
            frame6++;
            third_speed6 = 0;
            if (frame6 > 1) {
        frame6 = 0;
        }
        }

           u8 *texture_location_in_ram7 = segmented_to_virtual(&wf_dl_DEALS_base_rgba16);


    dma_read(texture_location_in_ram7,(frame7*4800)+deals_segment,(frame7*4800)+deals_segment+4800);
        third_speed7++;
        if (third_speed7 >= 4){
            frame7++;
            third_speed7 = 0;
            if (frame7 > 1) {
        frame7 = 0;
        }
        }

        u8 *texture_location_in_ram8 = segmented_to_virtual(&Battle_Actions_attack_base_rgba16);


    dma_read(texture_location_in_ram8,(frame8*2048)+fight_segment,(frame8*2048)+fight_segment+2048);
        if (battle_option == 0){
            frame8 = 1;
        } else {
            frame8 = 0;
        }
        
            u8 *texture_location_in_ram9 = segmented_to_virtual(&Battle_Actions_act_base_rgba16);


    dma_read(texture_location_in_ram9,(frame9*2048)+act_segment,(frame9*2048)+act_segment+2048);
    if (current_turn == 0){
        if (battle_option == 1){
            frame9 = 1;
        } else {
            frame9 = 0;
        }
    }
    if (current_turn != 0){
        if (battle_option == 1){
            frame9 = 3;
        } else {
            frame9 = 2;
        }
    }

        u8 *texture_location_in_ram10 = segmented_to_virtual(&Battle_Actions_item_base_rgba16);


    dma_read(texture_location_in_ram10,(frame10*2048)+item_segment,(frame10*2048)+item_segment+2048);
        if (battle_option == 2){
            frame10 = 1;
        } else {
            frame10 = 0;
        }

         u8 *texture_location_in_ram11 = segmented_to_virtual(&Battle_Actions_spare_base_rgba16);


    dma_read(texture_location_in_ram11,(frame11*2048)+spare_segment,(frame11*2048)+spare_segment+2048);
        if (battle_option == 3){
            frame11 = 1;
        } else {
            frame11 = 0;
        }

         u8 *texture_location_in_ram12 = segmented_to_virtual(&Battle_Actions_defend_base_rgba16);


    dma_read(texture_location_in_ram12,(frame12*2048)+defend_segment,(frame12*2048)+defend_segment+2048);
        if (battle_option == 4){
            frame12 = 1;
        } else {
            frame12 = 0;
        }
             
        u8 *texture_location_in_ram13 = segmented_to_virtual(&DRExplosion_explosion_44x44_rgba16);


    dma_read(texture_location_in_ram13,(frame13*3872)+explosion_segment,(frame13*3872)+explosion_segment+3872);
        if ((enemy_1_init_explosion == 1) | enemy_2_init_explosion == 1){
            frame13++;
            if (frame13 >= 16) {
        frame13 = 16;
        }
        }

             u8 *texture_location_in_ram14 = segmented_to_virtual(&determination_determination_base_rgba16);


    dma_read(texture_location_in_ram14,(frame14*800)+determination_segment,(frame14*800)+determination_segment+800);
third_speed14++;
        if (third_speed14 >= 3){
            frame14++;
            third_speed14 = 0;
            if (frame14 > 5) {
        frame14 = 0;
        }
        }
  
        //if (gPlayer1Controller->buttonPressed & R_TRIG){
        //RPG_mode = 0;
        //}

     //if ((gPlayer1Controller->buttonDown & L_TRIG) && RPG_mode == 1){
        //CurrTP++;
        //}


    if (gPlayer1Controller->buttonPressed & L_TRIG){
        BowserCurrHp = 0;
    }
    if (gPlayer1Controller->buttonPressed & R_TRIG){
        MarioCurrHp = 0;
    }
    if (gPlayer1Controller->buttonPressed & Z_TRIG){
        LuigiCurrHp = 0;
    }
    
//print_text_fmt_int(10,0, "enemy_2_health: %d", enemy_2_health);
//print_text_fmt_int(10,15, "enemy_1_health: %d", enemy_1_health);
//print_text_fmt_int(10,30, "rpg_initializer: %d", rpg_initializer);
//print_text_fmt_int(10,45, "rpg_init_timer: %d", rpg_init_timer);

mario_tot_damage = mario_base_damage * mario_multiplier;
 if(bowser_action_selected == 1){
bowser_tot_damage = (bowser_base_damage * bowser_multiplier) * 2;
 }
if(bowser_action_selected == 0){
bowser_tot_damage = bowser_base_damage * bowser_multiplier;
 }
luigi_tot_damage = luigi_base_damage * luigi_multiplier;

if (rpg_initializer == 1){
if (enemy_1 == 1){
        enemy_1_health = 80;
        enemy_1_max_health = 80;
    }
if (enemy_2 == 1){
        enemy_2_health = 80;
        enemy_2_max_health = 80;
    }
if (enemy_1 == 2){
        enemy_1_health = 120;
        enemy_1_max_health = 120;
    }
if (enemy_2 == 2){
        enemy_2_health = 120;
        enemy_2_max_health = 120;
    }
}
if (current_turn == 4){

       DamageFadeOut-=5;
    if (DamageFadeOut <= 0){
        DamageFadeOut = 0;
    }
} else {
    DamageFadeOut = 255;
}
if (current_turn == 4 && attack_phase == 0){
if (mario_enemy_selected == 1){
    if (mario_action_type == 1){
        enemy_1_health -= mario_tot_damage;
    }
}

if (bowser_action_type == 1){
    if (bowser_enemy_selected == 1){
        enemy_1_health -= bowser_tot_damage;
    }
    if (bowser_enemy_selected == 2){
        enemy_2_health -= bowser_tot_damage;
    }
}
if (bowser_action_type == 2){
    if (bowser_action_selected == 1){
        if (bowser_enemy_selected == 1){
            enemy_1_health -= bowser_tot_damage;
    }
        if (bowser_enemy_selected == 2){
            enemy_2_health -= bowser_tot_damage;
        }
    }
    if (bowser_action_selected == 2){
    enemy_1_health -= bowser_tot_damage;
    enemy_2_health -= bowser_tot_damage;
    }
}
if (luigi_enemy_selected == 1){
    if (luigi_action_type == 1){
        enemy_1_health -= luigi_tot_damage;
    }
}
if (mario_enemy_selected == 2){
    if (mario_action_type == 1){
        enemy_2_health -= mario_tot_damage;
    }
}

if (luigi_enemy_selected == 2){
    if (luigi_action_type == 1){
        enemy_2_health -= luigi_tot_damage;
    }
}





if (luigi_enemy_selected == 1){
    if (luigi_action_type == 2){
        if (luigi_action_selected == 1){
            enemy_1_mercy += 25;
        }

    }
}
if (luigi_enemy_selected == 2){
    if (luigi_action_type == 2){
        if (luigi_action_selected == 1){
            enemy_2_mercy += 25;
        }

    }
}
if ((luigi_enemy_selected == 2) | luigi_enemy_selected == 1){
    if (luigi_action_type == 2){
        if (luigi_action_selected == 2){
            MarioCurrHp += 50;
            BowserCurrHp += 50;
            LuigiCurrHp += 50;
        }

    }
}

if (mario_action_selected == 2){
    if (mario_action_type == 2){
                                if (mario_enemy_selected == 1){
                            enemy_1_mercy += 25;
                        }
                        if (mario_enemy_selected == 2){
                            enemy_2_mercy += 25;
                        }
    }
}
if (mario_action_type == 4){
    if (mario_enemy_selected == 1){
        enemy_1_mercy += 10;
        if (enemy_1_mercy >= 100){
            enemy_1_health = 0;
        }
    }
    if (mario_enemy_selected == 2){
        enemy_2_mercy += 10;
        if (enemy_2_mercy >= 100){
            enemy_2_health = 0;
        }
    }
}
    if (bowser_action_type == 4){
        if (bowser_enemy_selected == 2){
            enemy_2_mercy += 10;
            if (enemy_2_mercy >= 100){
                enemy_2_health = 0;
            }
        }
        if (bowser_enemy_selected == 1){
            enemy_1_mercy += 10;
            if (enemy_1_mercy >= 100){
                enemy_1_health = 0;
            }
        }
    }

    if (luigi_action_type == 4){
        if (luigi_enemy_selected == 2){
            enemy_2_mercy += 10;
            if (enemy_2_mercy >= 100){
                enemy_2_health = 0;
            }
        }
        if (luigi_enemy_selected == 1){
            enemy_1_mercy += 10;
            if (enemy_1_mercy >= 100){
                enemy_1_health = 0;
            }
        }
    }
    if (mario_action_type == 3){
        if(mario_enemy_selected == 3){
            MarioCurrHp += 25;
        }
        if(mario_enemy_selected == 4){
            BowserCurrHp += 25;
        }
        if(mario_enemy_selected == 5){
            LuigiCurrHp += 25;
        }
    }
    if (bowser_action_type == 3){
        if(bowser_enemy_selected == 3){
            MarioCurrHp += 25;
        }
        if(bowser_enemy_selected == 4){
            BowserCurrHp += 25;
        }
        if(bowser_enemy_selected == 5){
            LuigiCurrHp += 25;
        }
    }
    if (luigi_action_type == 3){
        if(luigi_enemy_selected == 3){
            MarioCurrHp += 25;
        }
        if(luigi_enemy_selected == 4){
            BowserCurrHp += 25;
        }
        if(luigi_enemy_selected == 5){
            LuigiCurrHp += 25;
        }
    }
attack_phase = 1;
}



    //print_text_fmt_int(80, 80, "RPG_mode = %d", RPG_mode);
    //print_text_fmt_int(80, 65, "battle_option = %d", battle_option);
    //print_text_fmt_int(80, 40, "framedelay = %d", framedelay);

/*
 u8 *texture_location_in_ram = segmented_to_virtual(&fountain_file_select_dma_base_rgba16);


    dma_read(texture_location_in_ram,(frame*44800)+fountain_segment,(frame*44800)+fountain_segment+44800);
        third_speed++;
        if (third_speed >= 3){
            frame++;
            third_speed = 0;
            if (frame > 4) {
        frame = 0;
        }
        }
        
}
*/

    particleFlags = execute_mario_action(gCurrentObject);
    gCurrentObject->oMarioParticleFlags = particleFlags;

    // Mario code updates MarioState's versions of position etc, so we need
    // to sync it with the Mario object
    copy_mario_state_to_object();

    i = 0;
    while (sParticleTypes[i].particleFlag != 0) {
        if (particleFlags & sParticleTypes[i].particleFlag) {
            spawn_particle(sParticleTypes[i].activeParticleFlag, sParticleTypes[i].model,
                           sParticleTypes[i].behavior);
        }

        i++;
    }
}

/**
 * Update every object that occurs after firstObj in the given object list,
 * including firstObj itself. Return the number of objects that were updated.
 */
s32 update_objects_starting_at(struct ObjectNode *objList, struct ObjectNode *firstObj) {
    s32 count = 0;

    while (objList != firstObj) {
        gCurrentObject = (struct Object *) firstObj;

        gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_HAS_ANIMATION;
        cur_obj_update();

        firstObj = firstObj->next;
        count++;
    }

    return count;
}

/**
 * Update objects in objList starting with firstObj while time stop is active.
 * This means that only certain select objects will be updated, such as Mario,
 * doors, unimportant objects, and the object that initiated time stop.
 * The exact set of objects that are updated depends on which flags are set
 * in gTimeStopState.
 * Return the total number of objects in the list (including those that weren't
 * updated)
 */
s32 update_objects_during_time_stop(struct ObjectNode *objList, struct ObjectNode *firstObj) {
    s32 count = 0;
    s32 unfrozen;

    while (objList != firstObj) {
        gCurrentObject = (struct Object *) firstObj;

        unfrozen = FALSE;

        // Selectively unfreeze certain objects
        if (!(gTimeStopState & TIME_STOP_ALL_OBJECTS)) {
            if (gCurrentObject == gMarioObject && !(gTimeStopState & TIME_STOP_MARIO_AND_DOORS)) {
                unfrozen = TRUE;
            }

            if ((gCurrentObject->oInteractType & (INTERACT_DOOR | INTERACT_WARP_DOOR))
                && !(gTimeStopState & TIME_STOP_MARIO_AND_DOORS)) {
                unfrozen = TRUE;
            }

            if (gCurrentObject->activeFlags
                & (ACTIVE_FLAG_UNIMPORTANT | ACTIVE_FLAG_INITIATED_TIME_STOP)) {
                unfrozen = TRUE;
            }
        }

        // Only update if unfrozen
        if (unfrozen) {
            gCurrentObject->header.gfx.node.flags |= GRAPH_RENDER_HAS_ANIMATION;
            cur_obj_update();
        } else {
            gCurrentObject->header.gfx.node.flags &= ~GRAPH_RENDER_HAS_ANIMATION;
        }

        firstObj = firstObj->next;
        count++;
    }

    return count;
}

/**
 * Update every object in the given list. Return the total number of objects in
 * the list.
 */
s32 update_objects_in_list(struct ObjectNode *objList) {
    s32 count;
    struct ObjectNode *firstObj = objList->next;

    if (!(gTimeStopState & TIME_STOP_ACTIVE)) {
        count = update_objects_starting_at(objList, firstObj);
    } else {
        count = update_objects_during_time_stop(objList, firstObj);
    }

    return count;
}

/**
 * Unload any objects in the list that have been deactivated.
 */
s32 unload_deactivated_objects_in_list(struct ObjectNode *objList) {
    struct ObjectNode *obj = objList->next;

    while (objList != obj) {
        gCurrentObject = (struct Object *) obj;

        obj = obj->next;

        if ((gCurrentObject->activeFlags & ACTIVE_FLAG_ACTIVE) != ACTIVE_FLAG_ACTIVE) {
#ifdef PUPPYLIGHTS
            if (gCurrentObject->oLightID != 0xFFFF)
                obj_disable_light(gCurrentObject);
#endif
            // Prevent object from respawning after exiting and re-entering the
            // area
            if (!(gCurrentObject->oFlags & OBJ_FLAG_PERSISTENT_RESPAWN)) {
                set_object_respawn_info_bits(gCurrentObject, RESPAWN_INFO_DONT_RESPAWN);
            }

            unload_object(gCurrentObject);
        }
    }

    return 0;
}

/**
 * OR the object's respawn info with bits << 8. If bits = 0xFF, this prevents
 * the object from respawning after leaving and re-entering the area.
 * For macro objects, respawnInfo points to the 16 bit entry in the macro object
 * list. For other objects, it points to the 32 bit behaviorArg in the
 * SpawnInfo.
 */
void set_object_respawn_info_bits(struct Object *obj, u8 bits) {
    u32 *info32;
    u16 *info16;

    switch (obj->respawnInfoType) {
        case RESPAWN_INFO_TYPE_NORMAL:
            info32 = (u32 *) obj->respawnInfo;
            *info32 |= bits << 8;
            break;

        case RESPAWN_INFO_TYPE_MACRO_OBJECT:
            info16 = (u16 *) obj->respawnInfo;
            *info16 |= bits << 8;
            break;
    }
}

/**
 * Unload all objects whose activeAreaIndex is areaIndex.
 */
void unload_objects_from_area(UNUSED s32 unused, s32 areaIndex) {
    struct Object *obj;
    struct ObjectNode *node;
    struct ObjectNode *list;
    s32 i;
    gObjectLists = gObjectListArray;

    for (i = 0; i < NUM_OBJ_LISTS; i++) {
        list = gObjectLists + i;
        node = list->next;

        while (node != list) {
            obj = (struct Object *) node;
            node = node->next;

            if (obj->header.gfx.activeAreaIndex == areaIndex) {
                unload_object(obj);
            }
        }
    }
}

/**
 * Spawn objects given a list of SpawnInfos. Called when loading an area.
 */
void spawn_objects_from_info(UNUSED s32 unused, struct SpawnInfo *spawnInfo) {
    gObjectLists = gObjectListArray;
    gTimeStopState = 0;

    gWDWWaterLevelChanging = FALSE;
    gMarioOnMerryGoRound = FALSE;

    clear_mario_platform();

    if (gCurrAreaIndex == 2) {
        gCCMEnteredSlide |= 1;
    }

    while (spawnInfo != NULL) {
        struct Object *object;
        const BehaviorScript *script;

        script = segmented_to_virtual(spawnInfo->behaviorScript);

        // If the object was previously killed/collected, don't respawn it
        if ((spawnInfo->behaviorArg & (RESPAWN_INFO_DONT_RESPAWN << 8))
            != (RESPAWN_INFO_DONT_RESPAWN << 8)) {
            object = create_object(script);

            // Behavior parameters are often treated as four separate bytes, but
            // are stored as an s32.
            object->oBehParams = spawnInfo->behaviorArg;
            // The second byte of the behavior parameters is copied over to a special field
            // as it is the most frequently used by objects.
            object->oBehParams2ndByte = GET_BPARAM2(spawnInfo->behaviorArg);

            object->behavior = script;
            object->unused1 = 0;

            // Record death/collection in the SpawnInfo
            object->respawnInfoType = RESPAWN_INFO_TYPE_NORMAL;
            object->respawnInfo = &spawnInfo->behaviorArg;

            // Usually this checks if bparam4 is 1 to decide if this is mario
            // This change allows any object to use that param
            if (object->behavior == segmented_to_virtual(bhvMario)) {
                gMarioObject = object;
                geo_make_first_child(&object->header.gfx.node);
            }

            geo_obj_init_spawninfo(&object->header.gfx, spawnInfo);

            vec3s_to_vec3f(&object->oPosVec, spawnInfo->startPos);

            vec3s_to_vec3i(&object->oFaceAngleVec, spawnInfo->startAngle);

            vec3s_to_vec3i(&object->oMoveAngleVec, spawnInfo->startAngle);

            object->oFloorHeight = find_floor(object->oPosX, object->oPosY, object->oPosZ, &object->oFloor);
        }

        spawnInfo = spawnInfo->next;
    }
}

/**
 * Clear objects, dynamic surfaces, and some miscellaneous level data used by objects.
 */
void clear_objects(void) {
    s32 i;

    gTHIWaterDrained = 0;
    gTimeStopState = 0;
    gMarioObject = NULL;
    gMarioCurrentRoom = 0;

    for (i = 0; i < 60; i++) {
        gDoorAdjacentRooms[i][0] = 0;
        gDoorAdjacentRooms[i][1] = 0;
    }

    debug_unknown_level_select_check();

    init_free_object_list();
    clear_object_lists(gObjectListArray);

    for (i = 0; i < OBJECT_POOL_CAPACITY; i++) {
        gObjectPool[i].activeFlags = ACTIVE_FLAG_DEACTIVATED;
        geo_reset_object_node(&gObjectPool[i].header.gfx);
    }

    gObjectMemoryPool = mem_pool_init(OBJECT_MEMORY_POOL, MEMORY_POOL_LEFT);
    gObjectLists = gObjectListArray;

    clear_dynamic_surfaces();
}

/**
 * Update spawner and surface objects.
 */
void update_terrain_objects(void) {
    gObjectCounter = update_objects_in_list(&gObjectLists[OBJ_LIST_SPAWNER]);
    profiler_update(PROFILER_TIME_SPAWNER);

    gObjectCounter += update_objects_in_list(&gObjectLists[OBJ_LIST_SURFACE]);
    profiler_update(PROFILER_TIME_DYNAMIC);
}

/**
 * Update all other object lists besides spawner and surface objects, using
 * the order specified by sObjectListUpdateOrder.
 */
void update_non_terrain_objects(void) {
    s32 listIndex;

    s32 i = 2;
    while ((listIndex = sObjectListUpdateOrder[i]) != -1) {
        if (listIndex == OBJ_LIST_PLAYER) {
            profiler_update(PROFILER_TIME_BEHAVIOR_BEFORE_MARIO);
        }
        gObjectCounter += update_objects_in_list(&gObjectLists[listIndex]);
        if (listIndex == OBJ_LIST_PLAYER) {
            profiler_update(PROFILER_TIME_MARIO);
        }
        i++;
    }
}

/**
 * Unload deactivated objects in any object list.
 */
void unload_deactivated_objects(void) {
    s32 listIndex;

    s32 i = 0;
    while ((listIndex = sObjectListUpdateOrder[i]) != -1) {
        unload_deactivated_objects_in_list(&gObjectLists[listIndex]);
        i++;
    }

    // TIME_STOP_UNKNOWN_0 was most likely intended to be used to track whether
    // any objects had been deactivated
    gTimeStopState &= ~TIME_STOP_UNKNOWN_0;
}

/**
 * Unused profiling function.
 */
UNUSED static u16 unused_get_elapsed_time(u64 *cycleCounts, s32 index) {
    u16 time;
    f64 cycles;

    cycles = cycleCounts[index] - cycleCounts[index - 1];
    if (cycles < 0) {
        cycles = 0;
    }

    time = (u16)(((u64) cycles * 1000000 / osClockRate) / 16667.0 * 1000.0);
    if (time > 999) {
        time = 999;
    }

    return time;
}

/**
 * Update all objects. This includes script execution, object collision detection,
 * and object surface management.
 */
void update_objects(UNUSED s32 unused) {

    gTimeStopState &= ~TIME_STOP_MARIO_OPENED_DOOR;

    gNumRoomedObjectsInMarioRoom = 0;
    gNumRoomedObjectsNotInMarioRoom = 0;
    gCollisionFlags &= ~COLLISION_FLAG_CAMERA;

    reset_debug_objectinfo();
    stub_debug_control();

    gObjectLists = gObjectListArray;

    // If time stop is not active, unload object surfaces
    clear_dynamic_surfaces();

    // Update spawners and objects with surfaces
    update_terrain_objects();

    // If Mario was touching a moving platform at the end of last frame, apply
    // displacement now
    //! If the platform object unloaded and a different object took its place,
    //  displacement could be applied incorrectly
    apply_mario_platform_displacement();

    // Detect which objects are intersecting
    detect_object_collisions();

    // Update all other objects that haven't been updated yet
    update_non_terrain_objects();

    // Unload any objects that have been deactivated
    unload_deactivated_objects();

    // Check if Mario is on a platform object and save this object
    update_mario_platform();

    try_print_debug_mario_object_info();

    // If time stop was enabled this frame, activate it now so that it will
    // take effect next frame
    if (gTimeStopState & TIME_STOP_ENABLED) {
        gTimeStopState |= TIME_STOP_ACTIVE;
    } else {
        gTimeStopState &= ~TIME_STOP_ACTIVE;
    }

    gPrevFrameObjectCount = gObjectCounter;
    
    profiler_update(PROFILER_TIME_BEHAVIOR_AFTER_MARIO);
}
