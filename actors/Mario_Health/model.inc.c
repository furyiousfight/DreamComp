Gfx Mario_Health_pallete_rgba32_aligner[] = {gsSPEndDisplayList()};
u8 Mario_Health_pallete_rgba32[] = {
	0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
	0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0xff, 
	0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 
	0x80, 0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0xff, 
	0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 
	0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 
	0x00, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 
	
};

Vtx Mario_Health_Cube_001_mesh_vtx_0[4] = {
	{{{64, 62, 159}, 0, {96, 89}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{103, 62, 159}, 0, {96, 89}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{103, 67, 159}, 0, {96, 89}, {0xFF, 0xFF, 0xFF, 0xFF}}},
	{{{64, 67, 159}, 0, {96, 89}, {0xFF, 0xFF, 0xFF, 0xFF}}},
};

Gfx Mario_Health_Cube_001_mesh_tri_0[] = {
	gsSPVertex(Mario_Health_Cube_001_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_Mario_Health_pap_layer1[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, SHADE, 0, TEXEL0, 0, PRIMITIVE, 0),
	gsSPClearGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 1, Mario_Health_pallete_rgba32),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 15, 1024),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_RGBA, G_IM_SIZ_32b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0, G_TX_WRAP | G_TX_NOMIRROR, 2, 0),
	gsDPSetTileSize(0, 0, 0, 12, 12),
	gsDPSetPrimColor(0, 0, 255, 255, 255, 255),
	gsSPEndDisplayList(),
};

Gfx mat_revert_Mario_Health_pap_layer1[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_ZBUFFER | G_CULL_BACK | G_LIGHTING),
	gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
	gsSPEndDisplayList(),
};

Gfx Mario_Health_Cube_001_mesh[] = {
	gsSPDisplayList(mat_Mario_Health_pap_layer1),
	gsSPDisplayList(Mario_Health_Cube_001_mesh_tri_0),
	gsSPDisplayList(mat_revert_Mario_Health_pap_layer1),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

