/*
 * Widgets.h
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#ifndef EXP_LVGLDASHBOARD_SRC_WIDGETS_H_
#define EXP_LVGLDASHBOARD_SRC_WIDGETS_H_

#include "lvgl.h"
#include "src/core/lv_obj.h"
#include "src/misc/lv_area.h"
#include "pico/stdlib.h"


class Widgets {
public:
	Widgets();
	virtual ~Widgets();

	void init();

private:
	void scene();

	static void timerCB(lv_timer_t * timer);
	void timerHandler(lv_timer_t * timer);

	lv_obj_t *xTV;
	lv_obj_t *xTile1;

	lv_obj_t *pDrJonLbl;
	lv_obj_t *pTestLbl;

	lv_obj_t *pBgImg;
	lv_obj_t *pReXP1;
	lv_obj_t * pBpiBO;
	lv_obj_t *pReXP1Txt;
	lv_obj_t * pBpiBOTxt;
	lv_obj_t * pDroidTxt;

	lv_style_t xStyleTile;
	lv_style_t xLabelSt;
	lv_style_t xLabelStA;

	lv_timer_t * pTimer;

	int32_t xPos = 0;
	int32_t yPos = 0;
	int32_t xReXP1Pos = 0;
	int32_t xBpiBOPos = 0;
	int32_t xSleepCount = 0;
	uint xSubStep = 0;
	uint xScene = 0;

};

#endif /* EXP_LVGLDASHBOARD_SRC_WIDGETS_H_ */
