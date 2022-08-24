Gfx TP_Meter_textbox_ovw_i8_aligner[] = {gsSPEndDisplayList()};
u8 TP_Meter_textbox_ovw_i8[] = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 
	
};

Vtx TP_Meter_TP_Meter_mesh_vtx_0[4] = {
	{{{20, 218, 126}, 0, {13, 128}, {0xFF, 0xA0, 0x40, 0xE4}}},
	{{{20, 124, 126}, 0, {13, 128}, {0xFF, 0xA0, 0x40, 0xE4}}},
	{{{30, 124, 126}, 0, {13, 128}, {0xFF, 0xA0, 0x40, 0xE4}}},
	{{{30, 218, 126}, 0, {13, 128}, {0xFF, 0xA0, 0x40, 0xE4}}},
};

Gfx TP_Meter_TP_Meter_mesh_tri_0[] = {
	gsSPVertex(TP_Meter_TP_Meter_mesh_vtx_0 + 0, 4, 0),
	gsSP1Triangle(0, 1, 2, 0),
	gsSP1Triangle(0, 2, 3, 0),
	gsSPEndDisplayList(),
};

Gfx mat_TP_Meter_f3dlite_material_025[] = {
	gsDPPipeSync(),
	gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT),
	gsSPClearGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_POINT),
	gsSPTexture(65535, 65535, 0, 0, 1),
	gsDPTileSync(),
	gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 1, TP_Meter_textbox_ovw_i8),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPLoadSync(),
	gsDPLoadBlock(7, 0, 0, 31, 2048),
	gsDPPipeSync(),
	gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 1, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0, G_TX_WRAP | G_TX_NOMIRROR, 3, 0),
	gsDPSetTileSize(0, 0, 0, 28, 28),
	gsSPEndDisplayList(),
};

Gfx mat_revert_TP_Meter_f3dlite_material_025[] = {
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsSPEndDisplayList(),
};

Gfx TP_Meter_TP_Meter_mesh[] = {
	gsSPDisplayList(mat_TP_Meter_f3dlite_material_025),
	gsSPDisplayList(TP_Meter_TP_Meter_mesh_tri_0),
	gsSPDisplayList(mat_revert_TP_Meter_f3dlite_material_025),
	gsDPPipeSync(),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

