#!/bin/sh

path="."
path_correcte="$path/map_correcte"
path_incorrecte="$path/map_incorrecte"

new_path="."

echo "Norminette :"
norminette ../libft ../headers ../src | grep -B 1 "Error"

echo "Compilation :"
make val_deb

echo "====================== Tests Correctes ======================"
echo "$path_correcte/test_color.cub"
$1 valgrind ../cub3D $path_correcte/test_color.cub
echo "$path_correcte/test_color2.cub"
$1 valgrind ../cub3D $path_correcte/test_color2.cub
echo "$path_correcte/test_color3.cub"
$1 valgrind ../cub3D $path_correcte/test_color3.cub
echo "$path_correcte/test_color4.cub"
$1 valgrind ../cub3D $path_correcte/test_color4.cub
echo "$path_correcte/grande_map.cub"
$1 valgrind ../cub3D $path_correcte/grande_map.cub
echo "$path_correcte/grande_map2.cub"
$1 valgrind ../cub3D $path_correcte/grande_map2.cub
echo "$path_correcte/grande_map3.cub"
$1 valgrind ../cub3D $path_correcte/grande_map3.cub
echo "$path_correcte/grande_map4.cub"
$1 valgrind ../cub3D $path_correcte/grande_map4.cub
echo "$path_correcte/grande_map5.cub"
$1 valgrind ../cub3D $path_correcte/grande_map5.cub
echo "$path_correcte/grande_map6.cub"
$1 valgrind ../cub3D $path_correcte/grande_map6.cub
#echo "$path_correcte/grande_map7.cub"
#$1 valgrind ../cub3D $path_correcte/grande_map7.cub
echo "$path_correcte/map_nord.cub"
$1 valgrind ../cub3D $path_correcte/map_nord.cub
echo "$path_correcte/map_nord2.cub"
$1 valgrind ../cub3D $path_correcte/map_nord2.cub

echo
echo "Tests dimensions map"
echo "$path_correcte/map_démesurée.cub"
$1 valgrind ../cub3D $path_correcte/map_démesurée.cub
echo "$path_correcte/map_démesurée2.cub"
$1 valgrind ../cub3D $path_correcte/map_démesurée2.cub
echo "$path_correcte/map_démesurée_labyrinthe.cub"
$1 valgrind ../cub3D $path_correcte/map_démesurée_labyrinthe.cub
echo "$path_correcte/toute_petite.cub"
$1 valgrind ../cub3D $path_correcte/toute_petite.cub

echo
echo "=============== Tests format incorrects ===================="
echo
echo "Tests nombre fichier incorrect"
echo
$1 valgrind ../cub3D $path_correcte/grande_map.cub $path_correcte/grande_map.cub
echo "###############################################"
$1 valgrind ../cub3D
echo
echo "Tests nom fichier incorrect"
echo
$1 valgrind ../cub3D not_existing
echo "###############################################"
$1 valgrind ../cub3D not_existing.cub
echo "###############################################"
$1 valgrind ../cub3D $path_correcte/nom_incorecte.cub
echo "###############################################"
$1 valgrind ../cub3D $path_correcte/nom_incorecte.cu
echo "###############################################"
$1 valgrind ../cub3D $path_correcte/nom_incorecte.cubf
echo "###############################################"
$1 valgrind ../cub3D $path_correcte/nom_incorecte.pdf
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/wrong_format.pdf

echo
echo "================= Tests map incorrectes ====================="
echo
echo "Tests règles de générations de map non respectées"
echo
$1 valgrind ../cub3D $path_incorrecte/double_perso.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/double_perso2.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/double_perso3.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/map_démesurée_sans_perso.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/without_perso.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/no_map.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/empty.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/wrong_component.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/unvalid_space.cub

echo
echo "Tests maps non fermées"
echo
$1 valgrind ../cub3D $path_incorrecte/opened_map.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map2.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map3.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map4.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map5.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map6.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map7.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map8.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/opened_map9.cub

echo
echo "Tests sur les textures ou les couleurs"
echo
$1 valgrind ../cub3D $path_incorrecte/same_texture.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/same_texture2.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/test_color.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/test_color2.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/test_color3.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/one_color.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/one_texture.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/double_north_texture.cub
echo "###############################################"
$1 valgrind ../cub3D $path_incorrecte/double_weast_texture.cub

echo
echo "================= Tests nouvelles maps ====================="
echo
echo "MAP INCORRECTES"
echo
echo "$new_path/cub3D/maps/bad/cheese_maze.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/cheese_maze.cub
echo "$new_path/cub3D/maps/bad/color_invalid_rgb.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/color_invalid_rgb.cub
echo "$new_path/cub3D/maps/bad/color_missing_ceiling_rgb.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/color_missing_ceiling_rgb.cub
echo "$new_path/cub3D/maps/bad/color_missing_floor_rgb.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/color_missing_floor_rgb.cub
echo "$new_path/cub3D/maps/bad/color_missing.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/color_missing.cub
echo "$new_path/cub3D/maps/bad/color_none.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/color_none.cub
echo "$new_path/cub3D/maps/bad/empty.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/empty.cub
echo "$new_path/cub3D/maps/bad/file_letter_end.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/file_letter_end.cub
echo "$new_path/cub3D/maps/bad/filetype_missing"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/filetype_missing
echo "$new_path/cub3D/maps/bad/filetype_wrong.buc"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/filetype_wrong.buc
echo "$new_path/cub3D/maps/bad/map_first.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/map_first.cub
echo "$new_path/cub3D/maps/bad/map_middle.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/map_middle.cub
echo "$new_path/cub3D/maps/bad/map_missing.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/map_missing.cub
echo "$new_path/cub3D/maps/bad/map_only.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/map_only.cub
echo "$new_path/cub3D/maps/bad/map_too_small.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/map_too_small.cub
echo "$new_path/cub3D/maps/bad/matrix.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/matrix.cub
echo "$new_path/cub3D/maps/bad/player_multiple.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/player_multiple.cub
echo "$new_path/cub3D/maps/bad/player_none.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/player_none.cub
echo "$new_path/cub3D/maps/bad/player_on_edge.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/player_on_edge.cub
echo "$new_path/cub3D/maps/bad/sad_face.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/sad_face.cub
echo "$new_path/cub3D/maps/bad/textures_dir.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/textures_dir.cub
echo "$new_path/cub3D/maps/bad/textures_duplicates.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/textures_duplicates.cub
echo "$new_path/cub3D/maps/bad/textures_invalid.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/textures_invalid.cub
echo "$new_path/cub3D/maps/bad/textures_missing.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/textures_missing.cub
echo "$new_path/cub3D/maps/bad/textures_none.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/textures_none.cub
echo "$new_path/cub3D/maps/bad/textures_not_xpm.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/textures_not_xpm.cub
echo "$new_path/cub3D/maps/bad/wall_hole_east.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/wall_hole_east.cub
echo "$new_path/cub3D/maps/bad/wall_hole_north.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/wall_hole_north.cub
echo "$new_path/cub3D/maps/bad/wall_hole_south.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/wall_hole_south.cub
echo "$new_path/cub3D/maps/bad/wall_hole_west.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/wall_hole_west.cub
echo "$new_path/cub3D/maps/bad/wall_none.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/bad/wall_none.cub
echo "###############################################"

echo
echo "MAP CORRECTES"
echo

echo "$new_path/cub3D/maps/good/creepy.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/creepy.cub
echo "$new_path/cub3D/maps/good/dungeon.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/dungeon.cub
echo "$new_path/cub3D/maps/good/forbidden.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/forbidden.cub
echo "$new_path/cub3D/maps/good/library.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/library.cub
echo "$new_path/cub3D/maps/good/square_map.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/square_map.cub
echo "$new_path/cub3D/maps/good/subject_map.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/subject_map.cub
echo "$new_path/cub3D/maps/good/test_map_hole.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_map_hole.cub
echo "$new_path/cub3D/maps/good/test_map.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_map.cub
echo "$new_path/cub3D/maps/good/test_pos_bottom.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_pos_bottom.cub
echo "$new_path/cub3D/maps/good/test_pos_left.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_pos_left.cub
echo "$new_path/cub3D/maps/good/test_pos_right.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_pos_right.cub
echo "$new_path/cub3D/maps/good/test_pos_top.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_pos_top.cub
echo "$new_path/cub3D/maps/good/test_textures.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_textures.cub
echo "$new_path/cub3D/maps/good/test_whitespace.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/test_whitespace.cub
echo "$new_path/cub3D/maps/good/textures_forbidden.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/textures_forbidden.cub
echo "$new_path/cub3D/maps/good/works.cub"
$1 valgrind ../cub3D $new_path/cub3D/maps/good/works.cub
echo "###############################################"
