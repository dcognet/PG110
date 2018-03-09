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




struct bomb{
	int x;
	int y;
	int power;
	int fuse;
};

void explosion(int x, int y,struct bomb *bomb){
	struct bomb *bomb_1=malloc(sizeof(struct bomb));
	*bomb_1=*bomb;
	while ((bomb_1->fuse)!=NULL){}

	//window_display_image(sprite_get_bomb_4(),bomb_1->x * SIZE_BLOC, bomb_1->y * SIZE_BLOC);
	//bomb_1=bomb_1->fuse;
	//}

	window_display_image(sprite_get_bomb_4(),bomb_1->x * SIZE_BLOC, bomb_1->y * SIZE_BLOC);
}

void bomb_init(int x, int y,struct bomb *bomb){
	if (bomb->fuse!=NULL){
	bomb->fuse=NULL;
	bomb->x=x;
	bomb->y=y;}
	else {
		struct bomb *bomb_1=malloc(sizeof(struct bomb));

		bomb_1->fuse=NULL;
		bomb_1->x=x;
		bomb_1->y=y;
		bomb->fuse=bomb_1;
	}


}

