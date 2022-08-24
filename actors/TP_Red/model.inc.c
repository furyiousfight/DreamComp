Lights1 TP_Red_aaaaaaaaaaaaaaaaa_layer1_lights = gdSPDefLights1(
	0x7F, 0x7F, 0x7F,
	0xFF,0xFF,0xFF,0x28,0x28,0x28);

Gfx TP_Red_pallete_2_rgba16_aligner[] = {gsSPEndDisplayList()};
u8 TP_Red_pallete_2_rgba16[] = {
	0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 
	0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 
	0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 
	0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 
	
};

Vtx TP_Red_TP_Red_mesh_vtx_0[4] = {
	{{{20, 124, 87}, 0, {-16, 112}, {0x0, 0x0, 0x7F, 0xE4}}},
	{{{30, 124, 87}, 0, {112, 112}, {0x0, 0x0, 0x7F, 0xE4}}},
	{{{30, 218, 87}, 0, {112, -16}, {0x0, 0x0, 0x7F, 0xE4}}},
	{{{20, 218, 87}, 0, {-16, -16}, {0x0, 0x0, 0x7F, 0xE4}}},
};

Gfx TP_Red_TP_Red_mesh_tri_0[] = {
	gsSPVertex(TP_Red_TP_Red_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_TP_Red_aaaaaaaaaaaaaaaaa_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BACK),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_NOOP),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, TP_Red_pallete_2_rgba16),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 15, 2048),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0),
	gsDPSetTileSize(0, 0, 0, 12, 12),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPSetLights1(TP_Red_aaaaaaaaaaaaaaaaa_layer1_lights),
	gsSPEndDisplayList(),
};

Gfx mat_revert_TP_Red_aaaaaaaaaaaaaaaaa_layer1[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx TP_Red_TP_Red_mesh[] = {
	gsSPDisplayList(mat_TP_Red_aaaaaaaaaaaaaaaaa_layer1),
	gsSPDisplayList(TP_Red_TP_Red_mesh_tri_0),
	gsSPDisplayList(mat_revert_TP_Red_aaaaaaaaaaaaaaaaa_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

