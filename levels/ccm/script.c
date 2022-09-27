#include <ultra64.h>
#include "sm64.h"
#include "behavior_data.h"
#include "model_ids.h"
#include "seq_ids.h"
#include "dialog_ids.h"
#include "segment_symbols.h"
#include "level_commands.h"

#include "game/level_update.h"

#include "levels/scripts.h"

#include "actors/common0.h"
#include "actors/common1.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/ccm/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_ccm_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _ccm_segment_7SegmentRomStart, _ccm_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _snow_yay0SegmentRomStart, _snow_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0B, _effect_yay0SegmentRomStart, _effect_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _ccm_skybox_yay0SegmentRomStart, _ccm_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group7_yay0SegmentRomStart, _group7_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group7_geoSegmentRomStart, _group7_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group16_yay0SegmentRomStart, _group16_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group16_geoSegmentRomStart, _group16_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _ccm_segment_7SegmentRomStart, _ccm_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_8), 
	JUMP_LINK(script_func_global_17), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, ccm_geo_00042C), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04, ccm_geo_00045C), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05, ccm_geo_000494), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06, ccm_geo_0004BC), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07, ccm_geo_0004E4), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_CABIN_DOOR, cabin_door_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_SNOW_TREE, snow_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_ROPEWAY_LIFT, ccm_geo_0003D0), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_SNOWMAN_BASE, ccm_geo_0003F0), 
	LOAD_MODEL_FROM_GEO(MODEL_CCM_SNOWMAN_HEAD, ccm_geo_00040C), 
	LOAD_MODEL_FROM_GEO(MODEL_TWOSER, twoser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BATTLEBOX, battlebox_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BATTLE_MARIO, battle_mario_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_DETERMINATION, determination_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_SNUFIT, snufit_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_THWOMP_CAR, thwomp_car_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_WHOMP_CAR, whomp_car_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOUNDS, bounds_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_DARK_TWOSER, dark_twoser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_DUMPSTER, dumpster_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BATTLE_DARK_TWOSER, battle_dark_twoser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_GULII, gulii_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, ccm_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0B, LEVEL_WF, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x0C, LEVEL_CCM, 0x01, 0x0C, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_DETERMINATION, -158, 1228, -6870, 0, 0, 0, 0x0C000000, bhvBonfire),
		OBJECT(MODEL_DARK_TWOSER, -322, 52, 5225, 0, 131, 0, 0x4c000000, bhvIntroTalkBowser),
		OBJECT(MODEL_GULII, 489, 52, 6832, 0, -90, 0, 0x53000000, bhvIntroTalkLuigi),
		OBJECT(MODEL_NONE, 1503, 52, 6310, 0, -90, 0, 0x150B0000, bhvWarp),
		OBJECT(MODEL_NONE, 1503, 52, 6506, 0, -90, 0, 0x150B0000, bhvWarp),
		OBJECT(MODEL_NONE, 1503, 52, 6717, 0, -90, 0, 0x150B0000, bhvWarp),
		OBJECT(MODEL_NONE, 1503, 52, 6913, 0, -90, 0, 0x150B0000, bhvWarp),
		OBJECT(MODEL_NONE, 1503, 52, 7141, 0, -90, 0, 0x150B0000, bhvWarp),
		OBJECT(MODEL_NONE, 1503, 52, 7337, 0, -90, 0, 0x150B0000, bhvWarp),
		OBJECT(MODEL_WOODEN_SIGNPOST, 681, 1681, 7928, 0, -180, 0, 0x001E0000, bhvMessagePanel),
		OBJECT(MODEL_BOUNDS, 601, 2277, -7014, 0, 0, 0, 0x0C000000, bhvOutOfBounds),
		OBJECT(MODEL_NONE, -1, 4882, -6705, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 0, -1, 4879, -6705),
		OBJECT(MODEL_NONE, -1, 1228, -6705, 0, 0, 0, 0x000C0000, bhvSpinAirborneWarp),
		TERRAIN(ccm_area_1_collision),
		MACRO_OBJECTS(ccm_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_STREAMED_CREEPYLANDSCAPE),
		TERRAIN_TYPE(TERRAIN_GRASS),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, -1, 4879, -6705),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
