void scroll_sts_mat_fawful_bg_f3dlite_material_006() {
	Gfx *mat = segmented_to_virtual(mat_fawful_bg_f3dlite_material_006);
	shift_s_down(mat, 19, PACK_TILESIZE(0, 5));
};

void scroll_sts_mat_fawful_bg_f3dlite_material_007() {
	Gfx *mat = segmented_to_virtual(mat_fawful_bg_f3dlite_material_007);
	shift_s_down(mat, 19, PACK_TILESIZE(0, 5));
};

void scroll_sts_mat_fawful_bg_f3dlite_material_009() {
	Gfx *mat = segmented_to_virtual(mat_fawful_bg_f3dlite_material_009);
	shift_s_down(mat, 19, PACK_TILESIZE(0, 6));
};

void scroll_sts_mat_fawful_bg_f3dlite_material_008() {
	Gfx *mat = segmented_to_virtual(mat_fawful_bg_f3dlite_material_008);
	shift_s_down(mat, 19, PACK_TILESIZE(0, 7));
};

void scroll_sts_mat_fawful_bg_f3dlite_material_010() {
	Gfx *mat = segmented_to_virtual(mat_fawful_bg_f3dlite_material_010);
	shift_s(mat, 19, PACK_TILESIZE(0, 10));
};

void scroll_actor_geo_fawful_bg() {
	scroll_sts_mat_fawful_bg_f3dlite_material_006();
	scroll_sts_mat_fawful_bg_f3dlite_material_007();
	scroll_sts_mat_fawful_bg_f3dlite_material_009();
	scroll_sts_mat_fawful_bg_f3dlite_material_008();
	scroll_sts_mat_fawful_bg_f3dlite_material_010();
}
