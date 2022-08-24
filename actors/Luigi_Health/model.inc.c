Gfx Luigi_Health_pallete_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 Luigi_Health_pallete_rgba32[] = {
	0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
	0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0xff, 
	0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
	0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0xff, 
	0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 
	0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 
	0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 
	
};

Vtx Luigi_Health_Cube_003_mesh_vtx_0[4] = {
	{{{279, 62, 159}, 0, {16, 16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{317, 62, 159}, 0, {16, 16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{317, 67, 159}, 0, {16, 16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{279, 67, 159}, 0, {16, 16}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx Luigi_Health_Cube_003_mesh_tri_0[] = {
	gsSPVertex(Luigi_Health_Cube_003_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_Luigi_Health_pap_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, Luigi_Health_pallete_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 15, 1024),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0),
	gsDPSetTileSize(0, 0, 0, 12, 12),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_Luigi_Health_pap_layer1[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx Luigi_Health_Cube_003_mesh[] = {
	gsSPDisplayList(mat_Luigi_Health_pap_layer1),
	gsSPDisplayList(Luigi_Health_Cube_003_mesh_tri_0),
	gsSPDisplayList(mat_revert_Luigi_Health_pap_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

