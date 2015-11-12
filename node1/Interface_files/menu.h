/*
 * menu.h
 *
 * Created: 17.09.2015 09:22:34
 *  Author: andreabm
 */ 


#ifndef MENU_H_
#define MENU_H_

typedef void(*function)(void);

typedef struct {
	char *name; //Name of menu
	
	struct menu *parent;
	struct menu *submenues[8];
	int num_submenues;
	
	char* name_functions[8];
	function functions[8]; //Functions in menu
	int num_functions;
	
	int arrow;
} menu;


void menuSystem();
void make_screen(menu* m);

#endif /* MENU_H_ */