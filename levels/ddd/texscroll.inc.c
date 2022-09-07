void scroll_sts_mat_ddd_dl_f3dlite_material_001() {
	Gfx *mat = segmented_to_virtual(mat_ddd_dl_f3dlite_material_001);
	shift_t_down(mat, 19, PACK_TILESIZE(0, 5));
};

void scroll_sts_mat_ddd_dl_f3dlite_material_002() {
	Gfx *mat = segmented_to_virtual(mat_ddd_dl_f3dlite_material_002);
	shift_s_down(mat, 12, PACK_TILESIZE(0, 2));
	shift_t_down(mat, 12, PACK_TILESIZE(0, 5));
	shift_s(mat, -1, PACK_TILESIZE(0, 1));
	shift_t(mat, -1, PACK_TILESIZE(0, 3));
};

void scroll_ddd() {
	scroll_sts_mat_ddd_dl_f3dlite_material_001();
	scroll_sts_mat_ddd_dl_f3dlite_material_002();
}
