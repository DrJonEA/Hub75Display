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
			lv_color_make(0, 0x00, 0xF0));

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


	pDrJonLbl = lv_label_create(xTV);
	lv_label_set_text(pDrJonLbl, "DrJonEA");
	lv_obj_set_width(pDrJonLbl, hor);
	lv_obj_set_style_text_align(pDrJonLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pDrJonLbl, LV_ALIGN_TOP_LEFT, 10, 5);
	lv_obj_add_style(pDrJonLbl , &xLabelSt,  LV_PART_MAIN);



	pTestLbl = lv_label_create(xTV);
	lv_label_set_text(pTestLbl, "Testing a Scoll Message");
	//lv_obj_set_width(pTestLbl, hor*2);
	lv_obj_set_style_text_align(pTestLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pTestLbl, LV_ALIGN_TOP_LEFT, 0, 0);
	lv_obj_add_style(pTestLbl , &xLabelStA,  LV_PART_MAIN);
	int32_t l = lv_obj_get_width(pTestLbl) ;
	xPos = hor + l;
	lv_obj_set_pos(pTestLbl,  xPos,  ver/2-16);




	pTimer = lv_timer_create(timerCB, 20,  this);

	/*
	pBtmLbl = lv_obj_create(xTV);
	lv_obj_set_size(pBtmLbl, 200, 20);
	lv_obj_set_style_bg_color(pBtmLbl, lv_color_hex(0xFF0000), 0);
	lv_obj_set_style_border_width(pBtmLbl, 0, 0);
	//lv_obj_center(pBtmLbl);
	lv_obj_set_pos(pBtmLbl, 100, 20);
	*/

}


void Widgets::timerCB(lv_timer_t * timer){
	Widgets *self = (Widgets *)lv_timer_get_user_data( timer);
	self->timerHandler(timer);
}

void Widgets::timerHandler(lv_timer_t * timer){
	//printf("Timer to %d\n", xPos);
	uint ver = lv_disp_get_ver_res(NULL);
	lv_obj_set_pos(pTestLbl,  xPos--,  ver/2-16);

	int32_t l = lv_obj_get_width(pTestLbl) ;
	if (xPos < (l * -1)){
		uint hor = lv_disp_get_hor_res(NULL);
		xPos = hor + l;//l;
	}
}


