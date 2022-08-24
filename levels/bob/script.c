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

#include "actors/common1.h"
#include "actors/common0.h"

/* Fast64 begin persistent block [includes] */
/* Fast64 end persistent block [includes] */

#include "make_const_nonconst.h"
#include "levels/bob/header.h"

/* Fast64 begin persistent block [scripts] */
/* Fast64 end persistent block [scripts] */

const LevelScript level_bob_entry[] = {
	INIT_LEVEL(),
	LOAD_YAY0(0x07, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_YAY0_TEXTURE(0x09, _generic_yay0SegmentRomStart, _generic_yay0SegmentRomEnd), 
	LOAD_YAY0(0x0A, _water_skybox_yay0SegmentRomStart, _water_skybox_yay0SegmentRomEnd), 
	LOAD_YAY0(0x05, _group3_yay0SegmentRomStart, _group3_yay0SegmentRomEnd), 
	LOAD_RAW(0x0C, _group3_geoSegmentRomStart, _group3_geoSegmentRomEnd), 
	LOAD_YAY0(0x06, _group14_yay0SegmentRomStart, _group14_yay0SegmentRomEnd), 
	LOAD_RAW(0x0D, _group14_geoSegmentRomStart, _group14_geoSegmentRomEnd), 
	LOAD_YAY0(0x08, _common0_yay0SegmentRomStart, _common0_yay0SegmentRomEnd), 
	LOAD_RAW(0x0F, _common0_geoSegmentRomStart, _common0_geoSegmentRomEnd), 
	LOAD_MIO0(0x7, _bob_segment_7SegmentRomStart, _bob_segment_7SegmentRomEnd), 
	LOAD_MIO0(0xa, _water_skybox_mio0SegmentRomStart, _water_skybox_mio0SegmentRomEnd), 
	ALLOC_LEVEL_POOL(),
	MARIO(MODEL_MARIO, 0x00000001, bhvMario), 
	JUMP_LINK(script_func_global_1), 
	JUMP_LINK(script_func_global_4), 
	JUMP_LINK(script_func_global_15), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BUBBLY_TREE, bubbly_tree_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_CHAIN_CHOMP_GATE, bob_geo_000440), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_SEESAW_PLATFORM, bob_geo_000458), 
	LOAD_MODEL_FROM_GEO(MODEL_BOB_BARS_GRILLS, bob_geo_000470), 
	LOAD_MODEL_FROM_GEO(MODEL_TWOSER, twoser_geo), 
	LOAD_MODEL_FROM_GEO(MODEL_BATTLEBOX, battlebox_geo), 

	/* Fast64 begin persistent block [level commands] */
	/* Fast64 end persistent block [level commands] */

	AREA(1, bob_area_1),
		WARP_NODE(0x0A, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF0, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		WARP_NODE(0xF1, LEVEL_BOB, 0x01, 0x0A, WARP_NO_CHECKPOINT),
		OBJECT(MODEL_NONE, 0, 4197, 6778, 0, 0, 0, 0x00000000, bhvOneCoin),
		OBJECT(MODEL_NONE, 0, 4197, -284, 0, 0, 0, 0x00000000, bhv1Up),
		OBJECT(MODEL_GOOMBA, 1001, 100, 633, 0, 0, 0, 0x01000000, bhvGoomba),
		OBJECT(MODEL_NONE, 2372, 3443, 124, 0, -45, 0, 0x00020000, bhvBattleGoomba),
		OBJECT(MODEL_TWOSER, -1598, 4590, 124, 0, 44, 0, 0x00000000, bhvBattleBowser),
		OBJECT(MODEL_NONE, 1448, 4822, 124, 0, -45, 0, 0x00010000, bhvBattleKoopa),
		OBJECT(MODEL_TWOSER, -1962, 3483, 124, 0, 44, 0, 0x00000000, bhvBattleBowser),
		OBJECT(MODEL_TWOSER, -2074, 5783, 124, 0, 44, 0, 0x00000000, bhvBattleBowser),
		OBJECT(MODEL_NONE, 0, 2560, -284, 0, 0, 0, 0x00000000, bhvRedCoin),
		OBJECT(MODEL_NONE, 0, 2560, -541, 0, 0, 0, 0x00000000, bhvBlueFish),
		OBJECT(MODEL_BATTLEBOX, -1, 3223, -376, 0, 0, 0, 0x00000000, bhvBattleBox),
		OBJECT(MODEL_NONE, 1448, 4822, 124, 0, -45, 0, 0x00010000, bhvBattleGoomba),
		OBJECT(MODEL_NONE, 2372, 3443, 124, 0, -45, 0, 0x00020000, bhvBattleKoopa),
		OBJECT(MODEL_GOOMBA, -1271, 100, 671, 0, 0, 0, 0x02000000, bhvGoomba),
		OBJECT(MODEL_BLUE_FLAME, 635, 2560, -284, 0, 0, 0, 0x00000000, bhvSnufit),
		OBJECT(MODEL_NONE, 0, 1798, -276, 0, 0, 0, 0x000A0000, bhvSpinAirborneWarp),
		MARIO_POS(0x01, 0, 0, 236, 713),
		TERRAIN(bob_area_1_collision),
		MACRO_OBJECTS(bob_area_1_macro_objs),
		SET_BACKGROUND_MUSIC(0x00, SEQ_STREAMED_CITY),
		TERRAIN_TYPE(TERRAIN_STONE),
		/* Fast64 begin persistent block [area commands] */
		/* Fast64 end persistent block [area commands] */
	END_AREA(),

	FREE_LEVEL_POOL(),
	MARIO_POS(0x01, 0, 0, 236, 713),
	CALL(0, lvl_init_or_update),
	CALL_LOOP(1, lvl_init_or_update),
	CLEAR_LEVEL(),
	SLEEP_BEFORE_EXIT(1),
	EXIT(),
};
