#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_drivers/indev/evdev.h"
#include "lv_examples/lv_examples.h"
#include <unistd.h>
//#include <stdio.h>

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

// display buffer size - not sure if this size is really needed
#define LV_BUF_SIZE (LV_HOR_RES_MAX*LV_VER_RES_MAX)		// 800x480
// A static variable to store the display buffers
static lv_disp_buf_t disp_buf;
// Static buffer(s). The second buffer is optional
static lv_color_t lvbuf1[LV_BUF_SIZE];
static lv_color_t lvbuf2[LV_BUF_SIZE];

static void * thread_lv_tick_up(void *arg);

int main(int argc, char *argv[])
{
	int demo_num=0;	//default

	if(argc>1)
		demo_num=atoi(argv[1]);

	printf("lvgl version:%d.%d.%d\n", LVGL_VERSION_MAJOR, LVGL_VERSION_MINOR, LVGL_VERSION_PATCH);
	printf("demo num:%d\n", demo_num);

	// LittlevGL init
	lv_init();

	//Linux frame buffer device init
	fbdev_init();

	// Touch pointer device init
	evdev_init();

	// Initialize `disp_buf` with the display buffer(s)
	lv_disp_buf_init(&disp_buf, lvbuf1, lvbuf2, LV_BUF_SIZE);

	// Initialize and register a display driver
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.flush_cb = fbdev_flush;	// flushes the internal graphical buffer to the frame buffer
	disp_drv.buffer = &disp_buf;		// set teh display buffere reference in the driver
	lv_disp_drv_register(&disp_drv);

	// Initialize and register a pointer device driver
	lv_indev_drv_t indev_drv;
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = evdev_read;    // defined in lv_drivers/indev/evdev.h
	lv_indev_drv_register(&indev_drv);

	switch(demo_num)
	{
		case 0:
		case 1: lv_demo_widgets(); break;
		case 2: lv_demo_music(); break;
		case 3: lv_demo_printer(); break;
		case 4: lv_demo_keypad_encoder(); break;
		case 5: lv_demo_benchmark(); break;
		case 6: lv_ex_get_started_1(); break;
		case 7: lv_ex_get_started_2(); break;
		case 8: lv_ex_get_started_3(); break;
		case 9: lv_ex_style_1(); break;
		case 10:  lv_ex_style_2(); break;
		case 11:  lv_ex_style_3(); break;
		case 12:  lv_ex_style_4(); break;
		case 13:  lv_ex_style_5(); break;
		case 14:  lv_ex_style_6(); break;
		case 15:  lv_ex_style_7(); break;
		case 16:  lv_ex_style_8(); break;
		case 17:  lv_ex_style_10(); break;
		case 18:  lv_ex_style_11(); break;
		case 19:  lv_ex_arc_1(); break;
		case 20:  lv_ex_tileview_1(); break;
		case 21:  lv_ex_spinner_1(); break;
		case 22:  lv_ex_spinbox_1(); break;
		case 23:  lv_ex_slider_1(); break;
		case 24:  lv_ex_roller_1(); break;
		case 25:  lv_ex_page_1(); break;
		case 26:  lv_ex_objmask_1(); break;
		case 27:  lv_ex_objmask_2(); break;
		case 28:  lv_ex_msgbox_2(); break;
		case 29:  lv_ex_list_1(); break;
		case 30:  lv_ex_linemeter_1(); break;
		case 31:  lv_ex_line_1(); break;
		case 32:  lv_ex_imgbtn_1(); break;
		case 33:  lv_ex_img_1(); break;
		case 34:  lv_ex_gauge_1(); break;
		case 35:  lv_ex_gauge_2(); break;
		case 36:  lv_ex_dropdown_1(); break;
		case 37:  lv_ex_dropdown_2(); break;
		case 38:  lv_ex_cpicker_1(); break;
		case 39:  lv_ex_cpicker_2(); break;
		case 40:  lv_ex_cont_1(); break;
		case 41:  lv_ex_checkbox_1(); break;
		case 42:  lv_ex_chart_1(); break;
		case 43:  lv_ex_chart_2(); break;
		case 44:  lv_ex_canvas_1(); break;
		case 45:  lv_ex_canvas_2(); break;
		case 46:  lv_ex_calendar_1(); break;
		case 47:  lv_ex_btnmatrix_1(); break;
		case 48:  lv_ex_btn_1(); break;
		case 49:  lv_ex_btn_2(); break;
		case 50:  lv_ex_bar_1(); break;
		case 51:  lv_ex_arc_1(); break;
		case 52:  lv_ex_arc_2(); break;

		default:
			lv_demo_printer(); break;
	}

	pthread_t tid1;
	int rc1=0;
	rc1 = pthread_create(&tid1, NULL, thread_lv_tick_up, NULL);
	if(rc1 != 0)
		printf("%s: %d\n",__func__, strerror(rc1));

	// Handle LitlevGL tasks (tickless mode)
	while(1) {
		lv_task_handler();
		usleep(1000);
		//printf("main\n");
	}
	return 0;
}

static void * thread_lv_tick_up(void *arg)
{
	while(1){
		lv_tick_inc(5);	//Tell LittelvGL that 5 milliseconds were elapsed
		usleep(5000);	//Sleep for 5 millisecond
		//printf("thread_lv_tick_up\n");
	}

}
