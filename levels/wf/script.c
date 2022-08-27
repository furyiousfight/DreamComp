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
#include "actors/group0.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/wf/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_wf_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _wf_segment_7SegmentRomStart, _wf_segment_7SegmentRomEnd), 
	LOAD_YAY0(0x0A, _cloud_floor_skybox_yay0SegmentRomStart, _cloud_floor_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _grass_yay0SegmentRomStart, _grass_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group1_yay0SegmentRomStart, _group1_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group1_geoSegmentRomStart, _group1_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _wf_segment_7SegmentRomStart, _wf_segment_7SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_2), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_03, wf_geo_0007E0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_04, wf_geo_000820), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_05, wf_geo_000860), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_06, wf_geo_000878), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_07, wf_geo_000890), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_08, wf_geo_0008A8), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_09, wf_geo_0008E8), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0A, wf_geo_000900), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0C, wf_geo_000940), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_GIANT_POLE, wf_geo_000AE0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0E, wf_geo_000958), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_0F, wf_geo_0009A0), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_ROTATING_PLATFORM, wf_geo_0009B8), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_11, wf_geo_0009D0), 
	LOAD_MODEL_FROM_GEO(MODEL_LEVEL_GEOMETRY_12, wf_geo_0009E8), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_SMALL_BOMP, wf_geo_000A00), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_LARGE_BOMP, wf_geo_000A40), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_ROTATING_WOODEN_PLATFORM, wf_geo_000A58), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_SLIDING_PLATFORM, wf_geo_000A98), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TUMBLING_BRIDGE_PART, wf_geo_000AB0), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TUMBLING_BRIDGE, wf_geo_000AC8), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_TRAPEZOID_PLATORM, wf_geo_000AF8), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_SQUARE_PLATORM, wf_geo_000B10), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_SQUARE_PLATORM_UNUSED, wf_geo_000B38), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_SQUARE_PLATORM_ELEVATOR, wf_geo_000B60), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_BREAKABLE_WALL_RIGHT, wf_geo_000B78), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_BREAKABLE_WALL_LEFT, wf_geo_000B90), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_KICKABLE_BOARD, wf_geo_000BA8), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_TOWER_DOOR, wf_geo_000BE0), 
	LOAD_MODEL_FROM_GEO(MODEL_WF_KICKABLE_BOARD_FELLED, wf_geo_000BC8), 
	LOAD_MODEL_FROM_GEO(MODEL_TWOSER, twoser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BATTLEBOX, battlebox_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BATTLE_MARIO, battle_mario_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_DETERMINATION, determination_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, wf_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0x12, LEVEL_WF, 0x01, 0x12, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 28140, 4197, -24462, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 28140, 4197, -31524, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_GOOMBA, 1001, 100, 633, 0, 0, 0, 0x01000000, bhvGoomba),
		OBJECT(MODEL_NONE, 30512, 3443, -31116, 0, -45, 0, 0x00020000, bhvBattleGoomba),
		OBJECT(MODEL_DETERMINATION, -166, 100, 23, 0, 0, 0, 0x000A0000, bhvBonfire),
		OBJECT(MODEL_NONE, 29588, 4822, -31116, 0, -45, 0, 0x00010000, bhvBattleKoopa),
		OBJECT(MODEL_TWOSER, 26699, 4359, -31116, 0, 90, 0, 0x00000000, bhvBattleBowser),
		OBJECT(MODEL_TWOSER, 26254, 6049, -31116, 0, 90, 0, 0x00000000, bhvBattleMario),
		OBJECT(MODEL_NONE, 28140, 2560, -31382, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 28140, 3097, -31781, 0, 0, 0, 0x00000000, bhvBlueFish),
		OBJECT(MODEL_BATTLEBOX, 28139, 3223, -31616, 0, 0, 0, 0x00000000, bhvBattleBox),
		OBJECT(MODEL_NONE, 29588, 4822, -31116, 0, -45, 0, 0x00010000, bhvBattleGoomba),
		OBJECT(MODEL_NONE, 30512, 3443, -31116, 0, -45, 0, 0x00020000, bhvBattleKoopa),
		OBJECT(MODEL_GOOMBA, -1271, 100, 671, 0, 0, 0, 0x02000000, bhvGoomba),
		OBJECT(MODEL_BLUE_FLAME, 3119, 1340, -142, 0, 0, 0, 0x00000000, bhvSnufit),
		OBJECT(MODEL_NONE, 28689, 2822, -31382, 0, 0, 0, 0x00000000, bhvSnufit),
		OBJECT(MODEL_THWOMP, 2295, 100, 1155, 0, 0, 0, 0x01000000, bhvThwompCar),
		OBJECT(MODEL_NONE, 2295, 100, -1800, 0, 0, 0, 0x01000000, bhvBoo),
		OBJECT(MODEL_NONE, 2295, 100, 3103, 0, 0, 0, 0x01000000, bhvBoo),
		OBJECT(MODEL_THWOMP, 2751, 100, 1598, 0, 180, 0, 0x01010000, bhvThwompCar),
		OBJECT(MODEL_THWOMP, 1808, 100, 725, 0, 180, 0, 0x01010000, bhvThwompCar),
		OBJECT(MODEL_THWOMP, 3181, 100, 1996, 0, 0, 0, 0x01000000, bhvThwompCar),
		OBJECT(MODEL_THWOMP, 4080, 100, 2965, 0, 0, 0, 0x01000000, bhvThwompCar),
		OBJECT(MODEL_THWOMP, 3592, 100, 2484, 0, 180, 0, 0x01010000, bhvThwompCar),
		OBJECT(MODEL_TWOSER, -23, 100, 1323, 0, 0, 0, 0x00000000, bhvFieldBowser),
		OBJECT(MODEL_TWOSER, 344, 100, 1323, 0, 0, 0, 0x00000000, bhvFieldLuigi),
		OBJECT(MODEL_TWOSER, 26254, 3609, -31116, 0, 90, 0, 0x00000000, bhvBattleMario),
		OBJECT(MODEL_DETERMINATION, -1183, 100, 1321, 0, 0, 0, 0x12000000, bhvBonfire),
		OBJECT(MODEL_NONE, 0, 122, 0, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 0, 0, 151, -33),
		OBJECT(MODEL_NONE, -1458, 255, 1335, 0, 0, 0, 0x00120000, bhvSpinAirborneWarp),
		TERRAIN(wf_area_1_collision),
		MACRO_OBJECTS(wf_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_STREAMED_CITY),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 151, -33),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
