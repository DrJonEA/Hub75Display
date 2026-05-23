/*
 * Widgets.cpp
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#include "Widgets.h"
#include <cstdio>





Widgets::Widgets() {

}

Widgets::~Widgets() {
	// TODO Auto-generated destructor stub
}



void Widgets::init() {

	xTV =lv_scr_act();
	lv_obj_clear_flag(xTV, LV_OBJ_FLAG_SCROLLABLE);
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);


	lv_style_init(&xStyleTile);
	lv_style_set_bg_color(&xStyleTile, lv_color_hex(0x000000));
	lv_style_set_bg_opa(&xStyleTile, LV_OPA_COVER);
	lv_obj_add_style(xTV, &xStyleTile, 0);

	lv_style_init(&xLabelSt);
	lv_style_set_text_font(&xLabelSt, &lv_font_montserrat_16);
	lv_style_set_text_color(
			&xLabelSt,
			lv_color_make(255, 247, 56));

	lv_style_init(&xLabelStA);
	lv_style_set_text_font(&xLabelStA, &lv_font_montserrat_32);
	lv_style_set_bg_opa(&xLabelStA, LV_OPA_TRANSP);
	lv_style_set_text_color(
			&xLabelStA,
			lv_color_make(0, 0xF0, 0xF0));
	lv_style_set_bg_color(
				&xLabelStA,
				lv_color_make(0, 0x0, 0x0));
	lv_style_set_border_width(&xLabelStA, 0);


	//Background
	LV_IMAGE_DECLARE(empirered);
	pBgImg = lv_image_create(xTV);
	lv_image_set_src(pBgImg, &empirered);
	lv_obj_align(pBgImg, LV_ALIGN_TOP_LEFT, 0, 0);


	//Dr Jon EA Logo
	pDrJonLbl = lv_label_create(xTV);
	lv_label_set_text(pDrJonLbl, "DrJonEA");
	lv_obj_set_width(pDrJonLbl, hor);
	lv_obj_set_style_text_align(pDrJonLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pDrJonLbl, LV_ALIGN_TOP_LEFT, 10, 5);
	lv_obj_add_style(pDrJonLbl , &xLabelSt,  LV_PART_MAIN);

	//Scroll Text
	pTestLbl = lv_label_create(xTV);
	lv_label_set_text(pTestLbl, "Testing a Scoll Message");
	//lv_obj_set_width(pTestLbl, hor*2);
	lv_obj_set_style_text_align(pTestLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pTestLbl, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(pTestLbl , &xLabelStA,  LV_PART_MAIN);
	int32_t l = lv_obj_get_width(pTestLbl) ;
	xPos = hor + l;
	lv_obj_set_pos(pTestLbl,  xPos,  ver/2-16);

	//Droids
	LV_IMAGE_DECLARE(ReXP1);
	LV_IMAGE_DECLARE(BpiBO);
	pReXP1 = lv_image_create(xTV);
	lv_image_set_src(pReXP1, &ReXP1);
	lv_obj_align(pReXP1, LV_ALIGN_TOP_RIGHT, 0, 0);
	lv_obj_add_flag(pReXP1, LV_OBJ_FLAG_HIDDEN);
	pBpiBO = lv_image_create(xTV);
	lv_image_set_src(pBpiBO, &BpiBO);
	lv_obj_align(pBpiBO, LV_ALIGN_TOP_RIGHT, -64 , 0);
	lv_obj_add_flag(pBpiBO, LV_OBJ_FLAG_HIDDEN);

	//Droid Logos
	pDroidTxt = lv_label_create(xTV);
	lv_label_set_text(pDroidTxt, "Introducing:");
	lv_obj_set_style_text_align(pDroidTxt, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pDroidTxt, LV_ALIGN_TOP_RIGHT, -70, 5);
	lv_obj_add_style(pDroidTxt , &xLabelSt,  LV_PART_MAIN);
	lv_obj_add_flag(pDroidTxt, LV_OBJ_FLAG_HIDDEN);
	pReXP1Txt = lv_label_create(xTV);
	lv_label_set_text(pReXP1Txt, "ReXP1");
	lv_obj_set_style_text_align(pReXP1Txt, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pReXP1Txt, LV_ALIGN_TOP_LEFT, 10, 25);
	lv_obj_add_style(pReXP1Txt , &xLabelSt,  LV_PART_MAIN);
	lv_obj_add_flag(pReXP1Txt, LV_OBJ_FLAG_HIDDEN);
	pBpiBOTxt = lv_label_create(xTV);
	lv_label_set_text(pBpiBOTxt, "and BpiBO");
	lv_obj_set_style_text_align(pBpiBOTxt, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pBpiBOTxt, LV_ALIGN_TOP_LEFT, 10, 40);
	lv_obj_add_style(pBpiBOTxt , &xLabelSt,  LV_PART_MAIN);
	lv_obj_add_flag(pBpiBOTxt, LV_OBJ_FLAG_HIDDEN);

	scene();
	pTimer = lv_timer_create(timerCB, 30,  this);

}


void Widgets::timerCB(lv_timer_t * timer){
	Widgets *self = (Widgets *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void Widgets::timerHandler(lv_timer_t * timer){
	//printf("Timer to %d\n", xPos);
	uint ver = lv_disp_get_ver_res(NULL);
	int32_t l;

	switch(xSubStep){
	case 0:
		lv_obj_set_pos(pTestLbl,  xPos,  ver/2-16);
		xPos -=2;
		l = lv_obj_get_width(pTestLbl) ;
		if (xPos < (l * -1)){
			uint hor = lv_disp_get_hor_res(NULL);
			xPos = hor + l;//l;
			yPos = 0;
			xSubStep++;
		}
		break;
	case 1:
		lv_obj_set_pos(pBgImg,  0, yPos--);
		if (yPos < (ver * -1)){
			xSubStep++;
			xReXP1Pos = 64;
			xBpiBOPos = 64;
			xSleepCount = 64;
			lv_obj_align(pReXP1, LV_ALIGN_TOP_RIGHT, 0, xReXP1Pos);
			lv_obj_clear_flag(pReXP1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_align(pBpiBO, LV_ALIGN_TOP_RIGHT, -64 , xBpiBOPos);
			lv_obj_clear_flag(pBpiBO, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(pDroidTxt, LV_OBJ_FLAG_HIDDEN);
		}
		break;
	case 2:
		if (xReXP1Pos <=0){
			if (xBpiBOPos <= 0){
				xSleepCount--;
			} else {
				xBpiBOPos --;
				lv_obj_clear_flag(pBpiBOTxt, LV_OBJ_FLAG_HIDDEN);
			}
		} else {
			xReXP1Pos --;
			lv_obj_clear_flag(pReXP1Txt, LV_OBJ_FLAG_HIDDEN);
		}
		lv_obj_align(pReXP1, LV_ALIGN_TOP_RIGHT, 0, xReXP1Pos);
		lv_obj_align(pBpiBO, LV_ALIGN_TOP_RIGHT, -64 , xBpiBOPos);
		if (xSleepCount <=0){
			xSubStep++;
			lv_obj_add_flag(pBpiBOTxt, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(pReXP1Txt, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(pDroidTxt, LV_OBJ_FLAG_HIDDEN);
		}
		break;
	case 3:
		lv_obj_set_pos(pBgImg,  0, yPos++);
		lv_obj_align(pReXP1, LV_ALIGN_TOP_RIGHT, 0, xReXP1Pos++);
		lv_obj_align(pBpiBO, LV_ALIGN_TOP_RIGHT, -64 , xBpiBOPos++);
		if (yPos >= 0){
			scene();
			xSubStep=0;
			lv_obj_add_flag(pReXP1, LV_OBJ_FLAG_HIDDEN);
			lv_obj_add_flag(pBpiBO, LV_OBJ_FLAG_HIDDEN);
		}
		break;
	}
}


void Widgets::scene(){
	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);
	xPos = hor ;
	lv_obj_set_pos(pTestLbl,  xPos,  ver/2-16);
	switch (xScene){
	case 0:
		lv_label_set_text(pTestLbl, "The Droids You re Looking For");
		break;
	case 1:
		lv_label_set_text(pTestLbl, "Assemble. Break. Connect. Discover. Explore.");
		break;
	case 2:
		lv_label_set_text(pTestLbl, "Create. Consult. Coach. Celebrate Creativity");
		break;
	case 3:
		lv_label_set_text(pTestLbl, "Adapt. Build. Create. Discover. Explore. Meet a Robot.");
		break;
	case 4:
		lv_label_set_text(pTestLbl, "Software. Firmware. PCBs. 3D Models. 3D Prints. All Made With Curiosity");
		break;
	case 5:
		lv_label_set_text(pTestLbl, "Powered by Raspberry PI Pico 2: RP2350");
		break;
	}



	xScene++;
	if (xScene > 5){
		xScene = 0;
	}
}

