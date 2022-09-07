#include "src/game/envfx_snow.h"

const GeoLayout librarydoor_geo[] = {
	GEO_NODE_START(),
	GEO_OPEN_NODE(),
		GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, librarydoor_Cube_005_mesh_layer_2),
		GEO_DISPLAY_LIST(LAYER_OPAQUE_DECAL, librarydoor_material_revert_render_settings),
	GEO_CLOSE_NODE(),
	GEO_END(),
};
