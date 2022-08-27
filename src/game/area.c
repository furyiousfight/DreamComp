#include <PR/ultratypes.h>

#include "config.h"
#include "area.h"
#include "sm64.h"
#include "gfx_dimensions.h"
#include "behavior_data.h"
#include "game_init.h"
#include "object_list_processor.h"
#include "engine/surface_load.h"
#include "ingame_menu.h"
#include "screen_transition.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "print.h"
#include "hud.h"
#include "audio/external.h"
#include "area.h"
#include "rendering_graph_node.h"
#include "level_update.h"
#include "engine/geo_layout.h"
#include "save_file.h"
#include "level_table.h"
#include "dialog_ids.h"
#include "puppyprint.h"
#include "debug_box.h"
#include "engine/colors.h"
#include "profiling.h"
#include "text_strings.h"
extern RPG_mode;
extern MarioMaxHp;
extern MarioCurrHp;
extern BowserMaxHp;
extern BowserCurrHp;
extern LuigiMaxHp;
extern LuigiCurrHp;
extern menu_pos;
extern CurrTP;
char ValueText[10];
extern battle_option;
u32 selection;
u32 selection_pos = 26;
extern MarioHealthTextOffset;
extern LuigiHealthTextOffset;
extern BowserHealthTextOffset;
extern vertical_menu;
extern vertical_option;
extern menu_phase;
u32 TPOffset;
extern enemy_1;
extern enemy_2;
extern mario_enemy_selected;
extern bowser_enemy_selected;
extern luigi_enemy_selected;
extern enemy_selected;
extern current_turn;
extern mario_action_type;
extern bowser_action_type;
extern luigi_action_type;
extern mario_tot_damage;
extern bowser_tot_damage;
extern luigi_tot_damage;
u32 Enemy1Dead = 255;
u32 Enemy2Dead = 255;
extern enemy_1_health;
extern enemy_2_health;
s32 DamageFadeOut = 255;
extern bowser_action_selected;
extern checked;
extern enemy_1;
extern enemy_2;

struct SpawnInfo gPlayerSpawnInfos[1];
struct GraphNode *gGraphNodePointers[MODEL_ID_COUNT];
struct Area gAreaData[AREA_COUNT];
extern DeterminationTimer;
extern WithinBonfireRadius;

struct WarpTransition gWarpTransition;
u8 TextStar[] = { TEXT_STAR };
u8 TextMinus[] = { TEXT_MINUS};
u8 PressB[] = { PRESS_B_DETERMINATION };
u8 Determined[] = { YOU_FEEL_DETERMINED };
u8 Test1[] = { TEXT_HUD_TEST_1 };
u8 Test2[] = { TEXT_HUD_TEST_2 };
u8 Test3[] = { TEXT_HUD_TEST_3 };
u8 Test4[] = { TEXT_HUD_TEST_LONG };
u8 Goomba[] = { TEXT_HUD_GOOMBA };
u8 GoombaCheck2[] = { TEXT_HUD_GOOMBA_CHECK_2 };
u8 GoombaCheck3[] = { TEXT_HUD_GOOMBA_CHECK_3 };
u8 Koopa[] = { TEXT_HUD_KOOPA };
u8 KoopaCheck2[] = { TEXT_HUD_KOOPA_CHECK_2 };
u8 KoopaCheck3[] = { TEXT_HUD_KOOPA_CHECK_3 };

u8 Check[] = { TEXT_HUD_CHECK };

u8 GoombaAct2[] = { TEXT_HUD_GOOMBA_ACT_2 };
u8 GoombaAct3[] = { TEXT_HUD_GOOMBA_ACT_3 };

u8 KoopaAct2[] = { TEXT_HUD_KOOPA_ACT_2 };
u8 KoopaAct3[] = { TEXT_HUD_KOOPA_ACT_3 };

u8 TextMario[] = { TEXT_HUD_MARIO };
u8 TextLuigi[] = { TEXT_HUD_LUIGI };
u8 TextBowser[] = { TEXT_HUD_BOWSER };

u8 Restors[] = { TEXT_HUD_RESTORES };
u8 HPRestored[] = { TEXT_HUD_HP_RESTORED };

u8 UnlimitedBreadsticks[] = { TEXT_HUD_UNLIMITED_BREADSTICKS };

u8 Pacify[] = { TEXT_HUD_PACIFY };
u8 PacifySkill1[] = { TEXT_HUD_PACIFY_SKILL1 };
u8 PacifySkill2[] = { TEXT_HUD_PACIFY_SKILL2 };
u8 PacifyTP[] = { TEXT_HUD_PACIFY_TP };

u8 Heal_Prayer[] = { TEXT_HUD_HEAL_PRAYER };
u8 HealPrayerSkill1[] = { TEXT_HUD_HEAL_PRAYER_SKILL1 };
u8 HealPrayerSkill2[] = { TEXT_HUD_HEAL_PRAYER_SKILL2 };
u8 HealPrayerTP[] = { TEXT_HUD_HEAL_PRAYER_TP };

u8 RudeBuster[] = { TEXT_HUD_RUDE_BUSTER };
u8 RudeBusterSkill1[] = { TEXT_HUD_RUDE_BUSTER_SKILL1 };
u8 RudeBusterSkill2[] = { TEXT_HUD_RUDE_BUSTER_SKILL2 };
u8 RudeBusterTP[] = { TEXT_HUD_RUDE_BUSTER_TP };

u8 DuoBuster[] = { TEXT_HUD_DUO_BUSTER };
u8 DuoBusterSkill1[] = { TEXT_HUD_DUO_BUSTER_SKILL1 };
u8 DuoBusterSkill2[] = { TEXT_HUD_DUO_BUSTER_SKILL2 };
u8 DuoBusterTP[] = { TEXT_HUD_DUO_BUSTER_TP };

u8 Enemy1Text[];
s16 gCurrCourseNum;
s16 gCurrActNum;
s16 gCurrAreaIndex;
s16 gSavedCourseNum;
s16 gMenuOptSelectIndex;
s16 gSaveOptSelectIndex;

struct SpawnInfo *gMarioSpawnInfo = &gPlayerSpawnInfos[0];
struct GraphNode **gLoadedGraphNodes = gGraphNodePointers;
struct Area *gAreas = gAreaData;
struct Area *gCurrentArea = NULL;
struct CreditsEntry *gCurrCreditsEntry = NULL;

Vp *gViewportOverride = NULL;
Vp *gViewportClip = NULL;
s16 gWarpTransDelay = 0;
RGBA16FILL gFBSetColor = 0;
RGBA16FILL gWarpTransFBSetColor = 0;
Color gWarpTransRed= 0;
Color gWarpTransGreen = 0;
Color gWarpTransBlue = 0;
s16 gCurrSaveFileNum = 1;
s16 gCurrLevelNum = LEVEL_MIN;

/*
 * The following two tables are used in get_mario_spawn_type() to determine spawn type
 * from warp behavior.
 * When looping through sWarpBhvSpawnTable, if the behavior function in the table matches
 * the spawn behavior executed, the index of that behavior is used with sSpawnTypeFromWarpBhv
*/

const BehaviorScript *sWarpBhvSpawnTable[] = {
    bhvDoorWarp,                bhvStar,                   bhvExitPodiumWarp,          bhvWarp,
    bhvWarpPipe,                bhvFadingWarp,             bhvInstantActiveWarp,       bhvAirborneWarp,
    bhvHardAirKnockBackWarp,    bhvSpinAirborneCircleWarp, bhvDeathWarp,               bhvSpinAirborneWarp,
    bhvFlyingWarp,              bhvSwimmingWarp,           bhvPaintingStarCollectWarp, bhvPaintingDeathWarp,
    bhvAirborneStarCollectWarp, bhvAirborneDeathWarp,      bhvLaunchStarCollectWarp,   bhvLaunchDeathWarp,
};

u8 sSpawnTypeFromWarpBhv[] = {
    MARIO_SPAWN_DOOR_WARP,             MARIO_SPAWN_IDLE,                 MARIO_SPAWN_PIPE,                  MARIO_SPAWN_PIPE,
    MARIO_SPAWN_PIPE,                  MARIO_SPAWN_TELEPORT,             MARIO_SPAWN_INSTANT_ACTIVE,        MARIO_SPAWN_AIRBORNE,
    MARIO_SPAWN_HARD_AIR_KNOCKBACK,    MARIO_SPAWN_SPIN_AIRBORNE_CIRCLE, MARIO_SPAWN_DEATH,                 MARIO_SPAWN_SPIN_AIRBORNE,
    MARIO_SPAWN_FLYING,                MARIO_SPAWN_SWIMMING,             MARIO_SPAWN_PAINTING_STAR_COLLECT, MARIO_SPAWN_PAINTING_DEATH,
    MARIO_SPAWN_AIRBORNE_STAR_COLLECT, MARIO_SPAWN_AIRBORNE_DEATH,       MARIO_SPAWN_LAUNCH_STAR_COLLECT,   MARIO_SPAWN_LAUNCH_DEATH,
};

Vp gViewport = { {
    { 640, 480, 511, 0 },
    { 640, 480, 511, 0 },
} };

#if MULTILANG
const char *gNoControllerMsg[] = {
    "NO CONTROLLER",
    "MANETTE DEBRANCHEE",
    "CONTROLLER FEHLT",
};
#endif

void override_viewport_and_clip(Vp *vpOverride, Vp *vpClip, Color red, Color green, Color blue) {
    RGBA16 color = ((red >> 3) << IDX_RGBA16_R) | ((green >> 3) << IDX_RGBA16_G) | ((blue >> 3) << IDX_RGBA16_B) | MSK_RGBA16_A;

    gFBSetColor = (color << 16) | color;
    gViewportOverride = vpOverride;
    gViewportClip = vpClip;
}

void set_warp_transition_rgb(Color red, Color green, Color blue) {
    RGBA16 warpTransitionRGBA16 = ((red >> 3) << IDX_RGBA16_R) | ((green >> 3) << IDX_RGBA16_G) | ((blue >> 3) << IDX_RGBA16_B) | MSK_RGBA16_A;

    gWarpTransFBSetColor = (warpTransitionRGBA16 << 16) | warpTransitionRGBA16;
    gWarpTransRed = red;
    gWarpTransGreen = green;
    gWarpTransBlue = blue;
}

void print_intro_text(void) {
#if MULTILANG
    s32 language = eu_get_language();
#endif
    if ((gGlobalTimer & 31) < 20) {
        if (gControllerBits == 0) {
#if MULTILANG
            print_text_centered(SCREEN_CENTER_X, 20, gNoControllerMsg[language]);
#else
            print_text_centered(SCREEN_CENTER_X, 20, "NO CONTROLLER");
#endif
        } else {
#ifdef VERSION_EU
            print_text(20, 20, "START");
#else
            print_text_centered(60, 38, "PRESS");
            print_text_centered(60, 20, "START");
#endif
        }
    }
}

u32 get_mario_spawn_type(struct Object *obj) {
    s32 i;
    const BehaviorScript *behavior = virtual_to_segmented(SEGMENT_BEHAVIOR_DATA, obj->behavior);

    for (i = 0; i < 20; i++) {
        if (sWarpBhvSpawnTable[i] == behavior) {
            return sSpawnTypeFromWarpBhv[i];
        }
    }
    return MARIO_SPAWN_NONE;
}

struct ObjectWarpNode *area_get_warp_node(u8 id) {
    struct ObjectWarpNode *node = NULL;

    for (node = gCurrentArea->warpNodes; node != NULL; node = node->next) {
        if (node->node.id == id) {
            break;
        }
    }
    return node;
}

struct ObjectWarpNode *area_get_warp_node_from_params(struct Object *obj) {
    return area_get_warp_node(GET_BPARAM2(obj->oBehParams));
}

void load_obj_warp_nodes(void) {
    struct ObjectWarpNode *warpNode;
    struct Object *children = (struct Object *) gObjParentGraphNode.children;

    do {
        struct Object *obj = children;

        if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && get_mario_spawn_type(obj) != 0) {
            warpNode = area_get_warp_node_from_params(obj);
            if (warpNode != NULL) {
                warpNode->object = obj;
            }
        }
    } while ((children = (struct Object *) children->header.gfx.node.next)
             != (struct Object *) gObjParentGraphNode.children);
}

void clear_areas(void) {
    s32 i;

    gCurrentArea = NULL;
    gWarpTransition.isActive = FALSE;
    gWarpTransition.pauseRendering = FALSE;
    gMarioSpawnInfo->areaIndex = -1;

    for (i = 0; i < AREA_COUNT; i++) {
        gAreaData[i].index = i;
        gAreaData[i].flags = AREA_FLAG_UNLOAD;
        gAreaData[i].terrainType = TERRAIN_GRASS;
        gAreaData[i].graphNode = NULL;
        gAreaData[i].terrainData = NULL;
        gAreaData[i].surfaceRooms = NULL;
        gAreaData[i].macroObjects = NULL;
        gAreaData[i].warpNodes = NULL;
        gAreaData[i].paintingWarpNodes = NULL;
        gAreaData[i].instantWarps = NULL;
        gAreaData[i].objectSpawnInfos = NULL;
        gAreaData[i].camera = NULL;
        gAreaData[i].unused = NULL;
        gAreaData[i].whirlpools[0] = NULL;
        gAreaData[i].whirlpools[1] = NULL;
        gAreaData[i].dialog[0] = DIALOG_NONE;
        gAreaData[i].dialog[1] = DIALOG_NONE;
        gAreaData[i].musicParam = 0;
        gAreaData[i].musicParam2 = 0;
    }
}

void clear_area_graph_nodes(void) {
    s32 i;

    if (gCurrentArea != NULL) {
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_UNLOAD);
#endif
        gCurrentArea = NULL;
        gWarpTransition.isActive = FALSE;
    }

    for (i = 0; i < AREA_COUNT; i++) {
        if (gAreaData[i].graphNode != NULL) {
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
            geo_call_global_function_nodes(&gAreaData[i].graphNode->node, GEO_CONTEXT_AREA_INIT);
#endif
            gAreaData[i].graphNode = NULL;
        }
    }
}

void load_area(s32 index) {
    if (gCurrentArea == NULL && gAreaData[index].graphNode != NULL) {
        gCurrentArea = &gAreaData[index];
        gCurrAreaIndex = gCurrentArea->index;

        if (gCurrentArea->terrainData != NULL) {
            load_area_terrain(index, gCurrentArea->terrainData, gCurrentArea->surfaceRooms,
                              gCurrentArea->macroObjects);
        }

        if (gCurrentArea->objectSpawnInfos != NULL) {
            spawn_objects_from_info(0, gCurrentArea->objectSpawnInfos);
        }

        load_obj_warp_nodes();
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_LOAD);
#endif
    }
}

void unload_area(void) {
    if (gCurrentArea != NULL) {
        unload_objects_from_area(0, gCurrentArea->index);
#ifndef DISABLE_GRAPH_NODE_TYPE_FUNCTIONAL
        geo_call_global_function_nodes(&gCurrentArea->graphNode->node, GEO_CONTEXT_AREA_UNLOAD);
#endif

        gCurrentArea->flags = AREA_FLAG_UNLOAD;
        gCurrentArea = NULL;
        gWarpTransition.isActive = FALSE;
    }
}

void load_mario_area(void) {
    stop_sounds_in_continuous_banks();
    load_area(gMarioSpawnInfo->areaIndex);

    if (gCurrentArea->index == gMarioSpawnInfo->areaIndex) {
        gCurrentArea->flags |= AREA_FLAG_LOAD;
        spawn_objects_from_info(0, gMarioSpawnInfo);
    }

    if (gAreaSkyboxStart[gCurrAreaIndex - 1]) {
        load_segment_decompress(SEGMENT_SKYBOX, gAreaSkyboxStart[gCurrAreaIndex - 1], gAreaSkyboxEnd[gCurrAreaIndex - 1]);
    }
}

void unload_mario_area(void) {
    if ((gCurrentArea != NULL) && (gCurrentArea->flags & AREA_FLAG_LOAD)) {
        unload_objects_from_area(0, gMarioSpawnInfo->activeAreaIndex);

        gCurrentArea->flags &= ~AREA_FLAG_LOAD;
        if (gCurrentArea->flags == AREA_FLAG_UNLOAD) {
            unload_area();
        }
    }
}

void change_area(s32 index) {
    s32 areaFlags = gCurrentArea->flags;

    if (gCurrAreaIndex != index) {
        unload_area();
        load_area(index);

        gCurrentArea->flags = areaFlags;
        gMarioObject->oActiveParticleFlags = ACTIVE_PARTICLE_NONE;
    }

    if (areaFlags & AREA_FLAG_LOAD) {
        gMarioObject->header.gfx.areaIndex = index, gMarioSpawnInfo->areaIndex = index;
    }
}

void area_update_objects(void) {
    gAreaUpdateCounter++;
    update_objects(0);
}

/*
 * Sets up the information needed to play a warp transition, including the
 * transition type, time in frames, and the RGB color that will fill the screen.
 */
void play_transition(s16 transType, s16 time, Color red, Color green, Color blue) {
#ifndef L3DEX2_ALONE
    gWarpTransition.isActive = TRUE;
    gWarpTransition.type = transType;
    gWarpTransition.time = time;
    gWarpTransition.pauseRendering = FALSE;

    // The lowest bit of transType determines if the transition is fading in or out.
    if (transType & WARP_TRANSITION_FADE_INTO) {
        set_warp_transition_rgb(red, green, blue);
    } else {
        red = gWarpTransRed, green = gWarpTransGreen, blue = gWarpTransBlue;
    }

    if (transType < WARP_TRANSITION_TYPE_STAR) { // if transition is WARP_TRANSITION_TYPE_COLOR
        gWarpTransition.data.red = red;
        gWarpTransition.data.green = green;
        gWarpTransition.data.blue = blue;
    } else { // if transition is textured
        gWarpTransition.data.red = red;
        gWarpTransition.data.green = green;
        gWarpTransition.data.blue = blue;

        // Both the start and end textured transition are always located in the middle of the screen.
        // If you really wanted to, you could place the start at one corner and the end at
        // the opposite corner. This will make the transition image look like it is moving
        // across the screen.
        gWarpTransition.data.startTexX = SCREEN_CENTER_X;
        gWarpTransition.data.startTexY = SCREEN_CENTER_Y;
        gWarpTransition.data.endTexX = SCREEN_CENTER_X;
        gWarpTransition.data.endTexY = SCREEN_CENTER_Y;

        gWarpTransition.data.texTimer = 0;

        if (transType & WARP_TRANSITION_FADE_INTO) { // Is the image fading in?
            gWarpTransition.data.startTexRadius = GFX_DIMENSIONS_FULL_RADIUS;
            if (transType >= WARP_TRANSITION_FADES_INTO_LARGE) {
                gWarpTransition.data.endTexRadius = 16;
            } else {
                gWarpTransition.data.endTexRadius = 0;
            }
        } else { // The image is fading out. (Reverses start & end circles)
            if (transType >= WARP_TRANSITION_FADES_FROM_LARGE) {
                gWarpTransition.data.startTexRadius = 16;
            } else {
                gWarpTransition.data.startTexRadius = 0;
            }
            gWarpTransition.data.endTexRadius = GFX_DIMENSIONS_FULL_RADIUS;
        }
    }
#endif
}

/*
 * Sets up the information needed to play a warp transition, including the
 * transition type, time in frames, and the RGB color that will fill the screen.
 * The transition will play only after a number of frames specified by 'delay'
 */
void play_transition_after_delay(s16 transType, s16 time, u8 red, u8 green, u8 blue, s16 delay) {
    gWarpTransDelay = delay; // Number of frames to delay playing the transition.
    play_transition(transType, time, red, green, blue);
}

void render_game(void) {
    if (gCurrentArea != NULL && !gWarpTransition.pauseRendering) {
        if (gCurrentArea->graphNode) {
            geo_process_root(gCurrentArea->graphNode, gViewportOverride, gViewportClip, gFBSetColor);
        }

        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&gViewport));

        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                      SCREEN_HEIGHT - gBorderHeight);
        
        render_hud();
        if ((WithinBonfireRadius == 1) && DeterminationTimer == 0) {
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            print_generic_string(121,39,PressB);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(120,40,PressB);
            WithinBonfireRadius=0;

        }
        if ((WithinBonfireRadius == 1) && DeterminationTimer > 0) {
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 0, 0, 0, 255);
            print_generic_string(81,39,Determined);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
            print_generic_string(80,40,Determined);
            WithinBonfireRadius=0;
        }
        if (RPG_mode ==1){
            gSPDisplayList(gDisplayListHead++, dl_ia_text_begin);
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            int_to_str(CurrTP,ValueText);
            print_generic_string(TPOffset,169,ValueText);
            
    if (MarioCurrHp > 0) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        int_to_str(MarioCurrHp,ValueText);
        print_generic_string(64+MarioHealthTextOffset,65+menu_pos,ValueText);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
        int_to_str(0,ValueText);
        print_generic_string(64+MarioHealthTextOffset,65+menu_pos,ValueText);
        }
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        int_to_str(MarioMaxHp,ValueText);
        print_generic_string(90,65+menu_pos,ValueText);
     if (BowserCurrHp > 0) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        int_to_str(BowserCurrHp,ValueText);
        print_generic_string(165+BowserHealthTextOffset,65+menu_pos,ValueText);
     } else {
        gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
        int_to_str(0,ValueText);
        print_generic_string(165+BowserHealthTextOffset,65+menu_pos,ValueText);
     }
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        int_to_str(BowserMaxHp,ValueText);
        print_generic_string(192,65+menu_pos,ValueText);
    if (LuigiCurrHp > 0) {
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        int_to_str(LuigiCurrHp,ValueText);
        print_generic_string(280+LuigiHealthTextOffset,65+menu_pos,ValueText);
    } else {
        gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
        int_to_str(0,ValueText);
        print_generic_string(280+LuigiHealthTextOffset,65+menu_pos,ValueText);
    }
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        int_to_str(LuigiMaxHp,ValueText);
        print_generic_string(302,65+menu_pos,ValueText);
        if (menu_phase == 0){
            if (checked == 0){
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(10,selection_pos+menu_pos, TextStar);
        print_generic_string(25,26+menu_pos,Test1);
        print_generic_string(25,13+menu_pos,Test2);
        print_generic_string(25,0+menu_pos,Test3);
            }
            if (((checked == 1) && enemy_1 == 1) | ((checked == 2) && enemy_2 == 1)){
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
        print_generic_string(10,selection_pos+menu_pos, TextStar);
        print_generic_string(25,26+menu_pos,Goomba);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(25,13+menu_pos,GoombaCheck2);
        print_generic_string(25,0+menu_pos,GoombaCheck3);
            }
            if (((checked == 1) && enemy_1 == 2) | ((checked == 2) && enemy_2 == 2)){
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
        print_generic_string(10,selection_pos+menu_pos, TextStar);
        print_generic_string(25,26+menu_pos,Koopa);
        gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
        print_generic_string(25,13+menu_pos,KoopaCheck2);
        print_generic_string(25,0+menu_pos,KoopaCheck3);
            }
        }
        if (menu_phase == 1){ //menu_phase 1, selecting the enemy
            if (vertical_option == 1){
                if (enemy_1_health > 0){
                    if (enemy_1 == 1){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                print_generic_string(25,26+menu_pos,Goomba);
                    }
                    if (enemy_1 == 2){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                print_generic_string(25,26+menu_pos,Koopa);
                }
            }
            if (enemy_1_health <= 0){
                    if (enemy_1 == 1){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(10,selection_pos, TextStar);
                print_generic_string(25,26+menu_pos,Goomba);
                    }
                    if (enemy_1 == 2){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(10,selection_pos, TextStar);
                print_generic_string(25,26+menu_pos,Koopa);
                }
            }
            if (enemy_2_health > 0){
                if (enemy_2 == 1){
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(25,13+menu_pos,Goomba);
                }
                if (enemy_2 == 2){
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
            print_generic_string(25,13+menu_pos,Koopa);
                }
            }
            if (enemy_2_health <= 0){
                if (enemy_2 == 1){
            gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
            print_generic_string(25,13+menu_pos,Goomba);
                }
                if (enemy_2 == 2){
            gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
            print_generic_string(25,13+menu_pos,Koopa);
                }
            }
            
            }
            if (vertical_option == 2){
                
            if (enemy_1_health > 0){
                    if (enemy_1 == 1){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,Goomba);
                    }
                    if (enemy_1 == 2){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,Koopa);
                }
            }
            if (enemy_1_health <= 0){
                    if (enemy_1 == 1){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(25,26+menu_pos,Goomba);
                    }
                    if (enemy_1 == 2){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(25,26+menu_pos,Koopa);
                }
            }
            if (enemy_2_health > 0){
                if (enemy_2 == 1){
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
            print_generic_string(10,selection_pos, TextStar);
            print_generic_string(25,13+menu_pos,Goomba);
                }
                if (enemy_2 == 2){
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
            print_generic_string(10,selection_pos, TextStar);
            print_generic_string(25,13+menu_pos,Koopa);
                }
            }
            if (enemy_2_health <= 0){
                if (enemy_2 == 1){
            gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
            print_generic_string(10,selection_pos, TextStar);
            print_generic_string(25,13+menu_pos,Goomba);
                }
                if (enemy_2 == 2){
            gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
            print_generic_string(10,selection_pos, TextStar);
            print_generic_string(25,13+menu_pos,Koopa);
                }
            }
            }
            }
        
        if (menu_phase == 2){ //menu_phase 2, selecting item
            if (vertical_option == 1){
            gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
            print_generic_string(10,selection_pos, TextStar);
            print_generic_string(25,26+menu_pos,UnlimitedBreadsticks);
            gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
            print_generic_string(275,26+menu_pos,Restors);
            print_generic_string(275,13+menu_pos,HPRestored);
            }

        }
        if (menu_phase == 3){ //menu_phase 3, selecting party members
            if (vertical_option == 1){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,26+menu_pos,TextMario);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,13+menu_pos,TextBowser);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,0+menu_pos,TextLuigi);
                }
            
            if (vertical_option == 2){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,TextMario);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,13+menu_pos,TextBowser);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,0+menu_pos,TextLuigi);

            }
            if (vertical_option == 3){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,TextMario);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,13+menu_pos,TextBowser);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,0+menu_pos,TextLuigi);

            }
        }
                if (menu_phase == 4){ //menu_phase 4, selecting act
            if (current_turn == 1){
                    if (vertical_option == 1){
                        if (CurrTP >= 40){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,26+menu_pos,RudeBuster);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,13+menu_pos,DuoBuster);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(220,26+menu_pos,RudeBusterSkill1);
                print_generic_string(230,13+menu_pos,RudeBusterSkill2);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(245,0+menu_pos,RudeBusterTP);
                        }
                        if (CurrTP < 40){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(25,26+menu_pos,RudeBuster);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,13+menu_pos,DuoBuster);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(220,26+menu_pos,RudeBusterSkill1);
                print_generic_string(230,13+menu_pos,RudeBusterSkill2);
                gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
                print_generic_string(245,0+menu_pos,RudeBusterTP);
                        }
                }
            if (vertical_option == 2){
                if (CurrTP >= 50){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,RudeBuster);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,13+menu_pos,DuoBuster);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(220,26+menu_pos,DuoBusterSkill1);
                print_generic_string(230,13+menu_pos,DuoBusterSkill2);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(245,0+menu_pos,DuoBusterTP);
                        }
                        if (CurrTP < 50){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,RudeBuster);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(25,13+menu_pos,DuoBuster);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(220,26+menu_pos,DuoBusterSkill1);
                print_generic_string(230,13+menu_pos,DuoBusterSkill2);
                gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
                print_generic_string(245,0+menu_pos,DuoBusterTP);
                        }
                    }
                } 
                if (current_turn == 2){
                    if (vertical_option == 1){
                        if (CurrTP >= 20){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,26+menu_pos,Pacify);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,13+menu_pos,Heal_Prayer);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(220,26+menu_pos,PacifySkill1);
                print_generic_string(220,13+menu_pos,PacifySkill2);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(245,0+menu_pos,PacifyTP);
                        }
                        if (CurrTP < 20){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(25,26+menu_pos,Pacify);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,13+menu_pos,Heal_Prayer);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(220,26+menu_pos,PacifySkill1);
                print_generic_string(220,13+menu_pos,PacifySkill2);
                gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
                print_generic_string(245,0+menu_pos,PacifyTP);
                        }
                }
            if (vertical_option == 2){
                if (CurrTP >= 35){
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,Pacify);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(25,13+menu_pos,Heal_Prayer);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(228,26+menu_pos,HealPrayerSkill1);
                print_generic_string(243,13+menu_pos,HealPrayerSkill2);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                print_generic_string(245,0+menu_pos,HealPrayerTP);
                        }
                    if (CurrTP < 35){
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(10,selection_pos, TextStar);
                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                print_generic_string(25,26+menu_pos,Pacify);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(25,13+menu_pos,Heal_Prayer);
                gDPSetEnvColor(gDisplayListHead++, 117, 117, 117, 255);
                print_generic_string(228,26+menu_pos,HealPrayerSkill1);
                print_generic_string(243,13+menu_pos,HealPrayerSkill2);
                gDPSetEnvColor(gDisplayListHead++, 132, 0, 0, 255);
                print_generic_string(245,0+menu_pos,HealPrayerTP);
                        }
            }

                } 
                if (current_turn == 0){
                    if (enemy_1 == 1){
                        if (enemy_selected == 1){
                            if (vertical_option == 1){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,26+menu_pos,Check);

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255); 
                                print_generic_string(25,13+menu_pos,GoombaAct2);
                                print_generic_string(25,0+menu_pos,GoombaAct3);
            
                                }
                            if (vertical_option == 2){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,13+menu_pos,GoombaAct2);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,0+menu_pos,GoombaAct3);
                                }
                            if (vertical_option == 3){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,0+menu_pos,GoombaAct3);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,13+menu_pos,GoombaAct2);
                                }
                            }
                        }
                    if (enemy_2 == 1){
                        if (enemy_selected == 2){
                            if (vertical_option == 1){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,26+menu_pos,Check);

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255); 
                                print_generic_string(25,13+menu_pos,GoombaAct2);
                                print_generic_string(25,0+menu_pos,GoombaAct3);
            
                                }
                            if (vertical_option == 2){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,13+menu_pos,GoombaAct2);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,0+menu_pos,GoombaAct3);
                                }
                            if (vertical_option == 3){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,0+menu_pos,GoombaAct3);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,13+menu_pos,GoombaAct2);
                                }
                            }
                        } // enemy 2
                        if (enemy_1 == 2){
                        if (enemy_selected == 1){
                            if (vertical_option == 1){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,26+menu_pos,Check);

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255); 
                                print_generic_string(25,13+menu_pos,KoopaAct2);
                                print_generic_string(25,0+menu_pos,KoopaAct3);
            
                                }
                            if (vertical_option == 2){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,13+menu_pos,KoopaAct2);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,0+menu_pos,KoopaAct3);
                                }
                            if (vertical_option == 3){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,0+menu_pos,KoopaAct3);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,13+menu_pos,KoopaAct2);
                                }
                            }
                        }
                    if (enemy_2 == 2){
                        if (enemy_selected == 2){
                            if (vertical_option == 1){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,26+menu_pos,Check);

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255); 
                                print_generic_string(25,13+menu_pos,KoopaAct2);
                                print_generic_string(25,0+menu_pos,KoopaAct3);
            
                                }
                            if (vertical_option == 2){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,13+menu_pos,KoopaAct2);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,0+menu_pos,KoopaAct3);
                                }
                            if (vertical_option == 3){
                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 0, 255);
                                print_generic_string(10,selection_pos, TextStar);
                                print_generic_string(25,0+menu_pos,KoopaAct3);
                                

                                gDPSetEnvColor(gDisplayListHead++, 255, 255, 255, 255);
                                print_generic_string(25,26+menu_pos,Check);
                                print_generic_string(25,13+menu_pos,KoopaAct2);
                                }
                            }
                        } // end of enemy 2
                }
                    }
                    if (current_turn == 4){
                        if (mario_enemy_selected == 1){
                            if (mario_action_type == 1){
                                gDPSetEnvColor(gDisplayListHead++, 0, 255, 255, DamageFadeOut);
                                print_generic_string(185,180,TextMinus);
                                int_to_str(mario_tot_damage,ValueText);
                                print_generic_string(190,180,ValueText);
                            }
                        }
                        
                        if (bowser_enemy_selected == 1){
                            if((bowser_action_type == 1) | (bowser_action_type == 2)){
                                gDPSetEnvColor(gDisplayListHead++, 255, 0, 255, DamageFadeOut);
                                print_generic_string(191,167,TextMinus);
                                int_to_str(bowser_tot_damage,ValueText);
                                print_generic_string(196,167,ValueText);
                            }
                
                        }
                        if (luigi_enemy_selected == 1){
                            if (luigi_action_type == 1){
                                gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, DamageFadeOut);
                                 print_generic_string(196,154,TextMinus);
                                int_to_str(luigi_tot_damage,ValueText);
                                print_generic_string(201,154,ValueText);
                            }
                        } // enemy 2 selected
                        if (mario_enemy_selected == 2){
                            if (mario_action_type == 1){
                                gDPSetEnvColor(gDisplayListHead++, 0, 255, 255, DamageFadeOut);
                                print_generic_string(185,180,TextMinus);
                                int_to_str(mario_tot_damage,ValueText);
                                print_generic_string(190,180,ValueText);
                            }
                        }
                        
                        if (bowser_enemy_selected == 2){
                            if((bowser_action_type == 1) | (bowser_action_type == 2)){
                                gDPSetEnvColor(gDisplayListHead++, 255, 0, 255, DamageFadeOut);
                                print_generic_string(191,167,TextMinus);
                                int_to_str(bowser_tot_damage,ValueText);
                                print_generic_string(196,167,ValueText);
                            }
                
                        }
                        if (luigi_enemy_selected == 2){
                            if (luigi_action_type == 1){
                                gDPSetEnvColor(gDisplayListHead++, 0, 255, 0, DamageFadeOut);
                                 print_generic_string(196,154,TextMinus);
                                int_to_str(luigi_tot_damage,ValueText);
                                print_generic_string(201,154,ValueText);
                            }
                        }

                        }
        }
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        render_text_labels();
        do_cutscene_handler();
        print_displaying_credits_entry();
        gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                      SCREEN_HEIGHT - gBorderHeight);
        gMenuOptSelectIndex = render_menus_and_dialogs();

        if (gMenuOptSelectIndex != 0) {
            gSaveOptSelectIndex = gMenuOptSelectIndex;
        }

        if (gViewportClip != NULL) {
            make_viewport_clip_rect(gViewportClip);
        } else
            gDPSetScissor(gDisplayListHead++, G_SC_NON_INTERLACE, 0, gBorderHeight, SCREEN_WIDTH,
                          SCREEN_HEIGHT - gBorderHeight);

        if (gWarpTransition.isActive) {
            if (gWarpTransDelay == 0) {
                gWarpTransition.isActive = !render_screen_transition(0, gWarpTransition.type, gWarpTransition.time,
                                                                     &gWarpTransition.data);
                if (!gWarpTransition.isActive) {
                    if (gWarpTransition.type & WARP_TRANSITION_FADE_INTO) {
                        gWarpTransition.pauseRendering = TRUE;
                    } else {
                        set_warp_transition_rgb(0, 0, 0);
                    }
                }
            } else {
                gWarpTransDelay--;
            }
        }
    } else {
        render_text_labels();
        if (gViewportClip != NULL) {
            clear_viewport(gViewportClip, gWarpTransFBSetColor);
        } else {
            clear_framebuffer(gWarpTransFBSetColor);
        }
    }

    gViewportOverride = NULL;
    gViewportClip     = NULL;
    
    profiler_update(PROFILER_TIME_GFX);
    profiler_print_times();
#if PUPPYPRINT_DEBUG
    puppyprint_render_profiler();
#endif
}
