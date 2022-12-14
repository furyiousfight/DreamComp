#include "src/game/envfx_snow.h"

const GeoLayout battle_mario_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_ANIMATED_PART(LAYER_OPAQUE, 0, -8, 0, battle_mario_Pelivis_mesh_layer_1),
		GEO_OPEN_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 53, 30, -5, 1, 0, 180),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Thigh_L_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 85, 0, -3, 0, 0),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Shin_L_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 78, 0, 94, 0, 0),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Foot_L_mesh_layer_1),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -53, 30, -5, 1, 0, -180),
			GEO_OPEN_NODE(),
				GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Thigh_R_mesh_layer_1),
				GEO_OPEN_NODE(),
					GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 85, 0, -3, 0, 0),
					GEO_OPEN_NODE(),
						GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Shin_R_mesh_layer_1),
						GEO_OPEN_NODE(),
							GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 78, 0, 94, 0, 0),
							GEO_OPEN_NODE(),
								GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Foot_R_mesh_layer_1),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
			GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 55, 0, battle_mario_Torso_mesh_layer_1),
			GEO_OPEN_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, battle_mario_Bicep_L_skinned_mesh_layer_1),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 71, 109, 0, 0, 4, -90),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Bicep_L_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 66, 0, 8, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Tricep_L_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 57, 0, -4, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Hand_L_mesh_layer_1),
									GEO_OPEN_NODE(),
										GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -1, 72, -9, 90, 0, 0),
										GEO_OPEN_NODE(),
											GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Hammer_mesh_layer_1),
										GEO_CLOSE_NODE(),
									GEO_CLOSE_NODE(),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, -71, 109, 0, 0, -4, 90),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Bicep_R_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 66, 0, 8, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Tricep_R_mesh_layer_1),
							GEO_OPEN_NODE(),
								GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 57, 0, -4, 0, 0),
								GEO_OPEN_NODE(),
									GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Hand_R_mesh_layer_1),
								GEO_CLOSE_NODE(),
							GEO_CLOSE_NODE(),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_DISPLAY_LIST(LAYER_OPAQUE, battle_mario_Cape_Upper_skinned_mesh_layer_1),
				GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 130, 0, -106, 0, 0),
				GEO_OPEN_NODE(),
					GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Cape_Upper_mesh_layer_1),
					GEO_OPEN_NODE(),
						GEO_DISPLAY_LIST(LAYER_OPAQUE, battle_mario_Cape_Bottom_skinned_mesh_layer_1),
						GEO_TRANSLATE_ROTATE(LAYER_OPAQUE, 0, 76, 0, -61, 0, 0),
						GEO_OPEN_NODE(),
							GEO_ANIMATED_PART(LAYER_OPAQUE, 0, 0, 0, battle_mario_Cape_Bottom_mesh_layer_1),
						GEO_CLOSE_NODE(),
					GEO_CLOSE_NODE(),
				GEO_CLOSE_NODE(),
				GEO_ANIMATED_PART(LAYER_ALPHA, 0, 130, 0, battle_mario_Head_mesh_layer_4),
				GEO_OPEN_NODE(),
					GEO_DISPLAY_LIST(LAYER_OPAQUE, battle_mario_Head_mesh_layer_1),
				GEO_CLOSE_NODE(),
			GEO_CLOSE_NODE(),
		GEO_CLOSE_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE, battle_mario_material_revert_render_settings),
		GEO_DISPLAY_LIST(LAYER_ALPHA, battle_mario_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
