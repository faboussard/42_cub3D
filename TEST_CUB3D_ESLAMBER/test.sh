#!/bin/sh

path="../tests/cub3D"
path_correcte="$path/map_correcte"
path_incorrecte="$path/map_incorrecte"

new_path="../tests"

echo "Norminette :"
norminette *.c *.h libft/lib_data/* libft/lib_fct/* libft/libft.h

echo "Compilation :"
make val_deb

echo "====================== Tests Correctes ======================"
$1 ./cub3D $path_correcte/test_color.cub
echo "###############################################"
$1 ./cub3D $path_correcte/test_color2.cub
echo "###############################################"
$1 ./cub3D $path_correcte/test_color3.cub
echo "###############################################"
$1 ./cub3D $path_correcte/test_color4.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map2.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map3.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map4.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map5.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map6.cub
echo "###############################################"
$1 ./cub3D $path_correcte/grande_map7.cub
echo "###############################################"
$1 ./cub3D $path_correcte/map_nord.cub
echo "###############################################"
$1 ./cub3D $path_correcte/map_nord2.cub

echo
echo "Tests dimensions map"
echo
# $1 ./cub3D $path_correcte/map_démesurée.cub
# echo "###############################################"
# $1 ./cub3D $path_correcte/map_démesurée2.cub
# echo "###############################################"
$1 ./cub3D $path_correcte/map_démesurée_labyrinthe.cub
echo "###############################################"
$1 ./cub3D $path_correcte/toute_petite.cub

echo
echo "=============== Tests format incorrectes ===================="
echo
echo "Tests nombre fichier incorrecte"
echo
$1 ./cub3D $path_correcte/grande_map.cub $path_correcte/grande_map.cub
echo "###############################################"
$1 ./cub3D
echo
echo "Tests nom fichier incorrecte"
echo
$1 ./cub3D not_existing
echo "###############################################"
$1 ./cub3D not_existing.cub
echo "###############################################"
$1 ./cub3D $path_correcte/nom_incorecte.cub
echo "###############################################"
$1 ./cub3D $path_correcte/nom_incorecte.cu
echo "###############################################"
$1 ./cub3D $path_correcte/nom_incorecte.cubf
echo "###############################################"
$1 ./cub3D $path_correcte/nom_incorecte.pdf
echo "###############################################"
$1 ./cub3D $path_incorrecte/wrong_format.pdf

echo
echo "================= Tests map incorrectes ====================="
echo
echo "Tests regles de generations de map non respectees"
echo
$1 ./cub3D $path_incorrecte/double_perso.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/double_perso2.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/double_perso3.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/map_démesurée_sans_perso.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/without_perso.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/no_map.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/empty.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/wrong_component.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/unvalid_space.cub

echo
echo "Tests maps non fermées"
echo
$1 ./cub3D $path_incorrecte/opened_map.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map2.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map3.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map4.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map5.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map6.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map7.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map8.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/opened_map9.cub

echo
echo "Tests sur les textures ou les couleurs"
echo
$1 ./cub3D $path_incorrecte/same_texture.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/same_texture2.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/test_color.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/test_color2.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/test_color3.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/one_color.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/one_texture.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/double_north_texture.cub
echo "###############################################"
$1 ./cub3D $path_incorrecte/double_weast_texture.cub

echo
echo "================= Tests nouvelles maps ====================="
echo
echo "MAP INCORECTES"
echo
$1 ./cub3D $new_path/cub3D/maps/bad/cheese_maze.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/color_invalid_rgb.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/color_missing_ceiling_rgb.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/color_missing_floor_rgb.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/color_missing.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/color_none.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/empty.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/file_letter_end.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/filetype_missing
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/filetype_wrong.buc
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/map_first.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/map_middle.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/map_missing.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/map_only.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/map_too_small.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/matrix.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/player_multiple.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/player_none.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/player_on_edge.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/sad_face.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/textures_dir.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/textures_duplicates.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/textures_invalid.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/textures_missing.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/textures_none.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/textures_not_xpm.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/wall_hole_east.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/wall_hole_north.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/wall_hole_south.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/wall_hole_west.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/bad/wall_none.cub
echo "###############################################"

echo
echo "MAP CORRECTES"
echo

$1 ./cub3D $new_path/cub3D/maps/good/creepy.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/dungeon.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/forbidden.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/library.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/square_map.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/subject_map.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_map_hole.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_map.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_pos_bottom.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_pos_left.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_pos_right.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_pos_top.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_textures.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/test_whitespace.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/textures_forbidden.cub
echo "###############################################"
$1 ./cub3D $new_path/cub3D/maps/good/works.cub
echo "###############################################"