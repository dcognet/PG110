/*******************************************************************************
 * This file is part of Bombeirb.
 * Copyright (C) 2018 by Laurent Réveillère
 ******************************************************************************/
#include <SDL/SDL_image.h>
#include <assert.h>
#include <stdio.h>
#include <player.h>
#include <sprite.h>
#include <window.h>
#include <misc.h>
#include <constant.h>


struct player {
	int x, y;
	enum direction current_direction;
	int nb_bombs;
};

struct player* player_init(int bomb_number) {
	struct player* player = malloc(sizeof(*player));
	if (!player)
		error("Memory error");

	player->current_direction = SOUTH;
	player->nb_bombs = bomb_number;

	return player;
}


void player_set_position(struct player *player, int x, int y) {
	assert(player);
	player->x = x;
	player->y = y;
}


void player_free(struct player* player) {
	assert(player);
	free(player);
}

int player_get_x(struct player* player) {
	assert(player != NULL);
	return player->x;
}

int player_get_y(struct player* player) {
	assert(player != NULL);
	return player->y;
}

void player_set_current_way(struct player* player, enum direction way) {
	assert(player);
	player->current_direction = way;
}

int player_get_nb_bomb(struct player* player) {
	assert(player);
	return player->nb_bombs;
}

void player_inc_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bombs += 1;
}

void player_dec_nb_bomb(struct player* player) {
	assert(player);
	player->nb_bombs -= 1;
}

void player_destroy(struct player *player,struct map* map){
	assert(player);
	int x=player->x;
	int y=player->y;
	if (map_get_cell_type(map, x-1, y)==CELL_BOX || map_get_cell_type(map, x+1, y)==CELL_BOX || map_get_cell_type(map, x, y-1)==CELL_BOX || map_get_cell_type(map, x, y+1)==CELL_BOX){
		display_bonus( map, x,y,CELL_BOX);
	}
}

static int player_move_aux(struct player* player, struct map* map, int x, int y) {
	int move_x=0;
	int move_y=0;

	if (!map_is_inside(map, x, y))
		return 0;

	switch (map_get_cell_type(map, x, y)) {
	case CELL_SCENERY:
		return 0;
		break;

	case CELL_BOX:  //il faut alors déplacer la box dans le m sens que le joueur
		if (player->current_direction==0)
			{move_x=0;
			move_y=-1;}
		if (player->current_direction==1)
			{move_x=0;
			move_y=1;}
		if (player->current_direction==2)
				{move_x=-1;
				move_y=0;}
		if (player->current_direction==3)
				{move_x=1;
				move_y=0;}
		if (!map_is_inside(map, x+move_x, y+move_y) || map_get_cell_type(map, x+move_x, y+move_y)!=0 ){ // test si la case est vide ou si elle est dans la map
			return 0;}

		map_set_cell_type(map,x+move_x,y+move_y,CELL_BOX); //déplace la box
		map_set_cell_type(map, x, y, CELL_EMPTY);  // vide la case
		return 1;
		break;

	case CELL_BONUS:
		break;

	case CELL_MONSTER:
		break;

	default:
		break;
	}

	// Player has moved
	return 1;
}

int player_move(struct player* player, struct map* map) {
	int x = player->x;
	int y = player->y;
	int move = 0;
	int move_x=0;
	int move_y=0;

	switch (player->current_direction) {
	case NORTH:
		if (player_move_aux(player, map, x, y - 1)) {
			player->y--;
			move = 1;
			move_x=0;
			move_y=-1;
		}
		break;

	case SOUTH:
		if (player_move_aux(player, map, x, y + 1)) {
			player->y++;
			move = 1;
			move_x=0;
			move_y=1;
		}
		break;

	case WEST:
		if (player_move_aux(player, map, x - 1, y)) {
			player->x--;
			move = 1;
			move_x=-1;
			move_y=0;
		}
		break;

	case EAST:
		if (player_move_aux(player, map, x + 1, y)) {
			player->x++;
			move = 1;
			move_x=1;
			move_y=0;
		}
		break;
	}

	//if (move) {
		//map_set_cell_type(map, x, y, CELL_EMPTY); //vide la case
	//}
	return move;
}

void player_display(struct player* player) {
	assert(player);
	window_display_image(sprite_get_player(player->current_direction),player->x * SIZE_BLOC, player->y * SIZE_BLOC);

}

void player_put_bomb(struct player *player,struct map* map,struct bomb *bomb ,struct game *game){
	explosion(player->x,player->y,bomb);
}

void player_bomb_init(struct player *player,struct bomb *bomb){
	bomb_init(player->x,player->y,bomb);
}
