/*
 * =================================================================
 *
 *
 *	Description:  samsung display panel file
 *
 *	Author: jb09.kim
 *	Company:  Samsung Electronics
 *
 * ================================================================
 */
/*
<one line to give the program's name and a brief idea of what it does.>
Copyright (C) 2012, Samsung Electronics. All rights reserved.

*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
*/
#ifndef _SAMSUNG_DSI_SMART_DIMMING_EA8061V_AMS497EE01_H_
#define _SAMSUNG_DSI_SMART_DIMMING_EA8061V_AMS497EE01_H_

#include "../ss_dsi_panel_common.h"
#include "../ss_dsi_smart_dimming_common.h"

/*
*	From 4.8 inch model use AID function
*	CASE#1 is used for now.
*/
#define AID_OPERATION

enum {
	GAMMA_CURVE_1P9 = 0,
	GAMMA_CURVE_2P15,
	GAMMA_CURVE_2P2,
};

#define REV_C	0x03

#define LUMINANCE_MAX 62
#define GAMMA_SET_MAX 33
#define BIT_SHIFT 22
/*
	it means BIT_SHIFT is 22.  pow(2,BIT_SHIFT) is 4194304.
	BIT_SHIFT is used for right bit shfit
*/
#define BIT_SHFIT_MUL 4194304

#define GRAY_SCALE_MAX 256

/*6.3*4194304 */
#define VREG0_REF_6P3 26424115

/*6.2*4194304 */
#define VREG0_REF_6P2 26004685

/*6.0*4194304 */
#define VREG0_REF_6P0 25165824

/* 5.8 * 4194304 */
#define VREG0_REF_5P8 24326963
/* 5.6 * 4194304 */
#define VREG0_REF_5P6 23488102

/*V0,V3,V11,V23,V35,V51,V87,V151,V203,V255*/
#define ARRAY_MAX 11

/* PANEL DEPENDENT THINGS */
#define MIN_CANDELA	5

/*
*	ID 0x20
*/
#define V255_300CD_R_MSB_20 0x01
#define V255_300CD_R_LSB_20 0x00

#define V255_300CD_G_MSB_20 0x01
#define V255_300CD_G_LSB_20 0x00

#define V255_300CD_B_MSB_20 0x01
#define V255_300CD_B_LSB_20 0x00

#define V203_300CD_R_20 0x80
#define V203_300CD_G_20 0x80
#define V203_300CD_B_20 0x80

#define V151_300CD_R_20 0x80
#define V151_300CD_G_20 0x80
#define V151_300CD_B_20 0x80

#define V87_300CD_R_20 0x80
#define V87_300CD_G_20 0x80
#define V87_300CD_B_20 0x80

#define V51_300CD_R_20 0x80
#define V51_300CD_G_20 0x80
#define V51_300CD_B_20 0x80

#define V35_300CD_R_20 0x80
#define V35_300CD_G_20 0x80
#define V35_300CD_B_20 0x80

#define V23_300CD_R_20 0x80
#define V23_300CD_G_20 0x80
#define V23_300CD_B_20 0x80

#define V11_300CD_R_20 0x80
#define V11_300CD_G_20 0x80
#define V11_300CD_B_20 0x80

#define V3_300CD_R_20 0x80
#define V3_300CD_G_20 0x80
#define V3_300CD_B_20 0x80

#define VT_300CD_R_20 0x00
#define VT_300CD_G_20 0x00
#define VT_300CD_B_20 0x00


/* PANEL DEPENDENT THINGS END*/

enum {
	V1_INDEX = 0,
	V3_INDEX = 1,
	V11_INDEX = 2,
	V23_INDEX = 3,
	V35_INDEX = 4,
	V51_INDEX = 5,
	V87_INDEX = 6,
	V151_INDEX = 7,
	V203_INDEX = 8,
	V255_INDEX = 9,
};

struct GAMMA_LEVEL {
	int level_0;
	int level_1;
	int level_3;
	int level_11;
	int level_23;
	int level_35;
	int level_51;
	int level_87;
	int level_151;
	int level_203;
	int level_255;
} __packed;

struct RGB_OUTPUT_VOLTARE {
	struct GAMMA_LEVEL R_VOLTAGE;
	struct GAMMA_LEVEL G_VOLTAGE;
	struct GAMMA_LEVEL B_VOLTAGE;
} __packed;

struct GRAY_VOLTAGE {
	/*
		This voltage value use 14bit right shit
		it means voltage is divied by 16384.
	*/
	int R_Gray;
	int G_Gray;
	int B_Gray;
} __packed;

struct GRAY_SCALE {
	struct GRAY_VOLTAGE TABLE[GRAY_SCALE_MAX];
	struct GRAY_VOLTAGE VT_TABLE;
} __packed;

/*V0,V1,V3,V11,V23,V35,V51,V87,V151,V203,V255*/

struct MTP_SET {
	char OFFSET_255_MSB;
	char OFFSET_255_LSB;
	char OFFSET_203;
	char OFFSET_151;
	char OFFSET_87;
	char OFFSET_51;
	char OFFSET_35;
	char OFFSET_23;
	char OFFSET_11;
	char OFFSET_3;
	char OFFSET_1;
} __packed;

struct MTP_OFFSET {
	struct MTP_SET R_OFFSET;
	struct MTP_SET G_OFFSET;
	struct MTP_SET B_OFFSET;
} __packed;

struct illuminance_table {
	int lux;
	char gamma_setting[GAMMA_SET_MAX];
} __packed;

struct SMART_DIM {
	struct MTP_OFFSET MTP_ORIGN;

	struct MTP_OFFSET MTP;
	struct RGB_OUTPUT_VOLTARE RGB_OUTPUT;
	struct GRAY_SCALE GRAY;

	/* Because of AID funtion, below members are added*/
	int lux_table_max;
	int *plux_table;
	struct illuminance_table gen_table[LUMINANCE_MAX];

	int brightness_level;
	int ldi_revision;
	int vregout_voltage;
} __packed;

#define AOR_DIM_BASE_CD	115

#define CANDELA_MAX_TABLE 61
#define RGB_COMPENSATION 24

static int candela_table[][2] = {
	{5, 0,},
	{6, 1,},
	{7, 2,},
	{8, 3,},
	{9, 4,},
	{10, 5,},
	{11, 6,},
	{12, 7,},
	{13, 8,},
	{14, 9,},
	{15, 10,},
	{16, 11,},
	{17, 12,},
	{19, 13,},
	{20, 14,},
	{21, 15,},
	{22, 16,},
	{24, 17,},
	{25, 18,},
	{27, 19,},
	{29, 20,},
	{30, 21,},
	{32, 22,},
	{34, 23,},
	{37, 24,},
	{39, 25,},
	{41, 26,},
	{44, 27,},
	{47, 28,},
	{50, 29,},
	{53, 30,},
	{56, 31,},
	{60, 32,},
	{64, 33,},
	{68, 34,},
	{72, 35,},
	{77, 36,},
	{82, 37,},
	{87, 38,},
	{93, 39,},
	{98, 40,},
	{105, 41,},
	{111, 42,},
	{119, 43,},
	{126, 44,},
	{134, 45,},
	{143, 46,},
	{152, 47,},
	{162, 48,},
	{172, 49,},
	{183, 50,},
	{195, 51,},
	{207, 52,},
	{220, 53,},
	{234, 54,},
	{249, 55,},
	{265, 56,},
	{282, 57,},
	{300, 58,},
	{316, 59,},
	{333, 60,},
	{360, 61,},
};
static int base_luminance_revC[][2] = {
	{5,	116,},
	{6,	116,},
	{7,	116,},
	{8,	116,},
	{9,	116,},
	{10, 116,},
	{11, 116,},
	{12, 116,},
	{13, 116,},
	{14, 116,},
	{15, 116,},
	{16, 116,},
	{17, 116,},
	{19, 116,},
	{20, 116,},
	{21, 116,},
	{22, 116,},
	{24, 116,},
	{25, 116,},
	{27, 116,},
	{29, 116,},
	{30, 116,},
	{32, 116,},
	{34, 116,},
	{37, 116,},
	{39, 116,},
	{41, 116,},
	{44, 116,},
	{47, 116,},
	{50, 116,},
	{53, 116,},
	{56, 116,},
	{60, 116,},
	{64, 116,},
	{68, 116,},
	{72, 122,},
	{77, 131,},
	{82, 139,},
	{87, 145,},
	{93, 156,},
	{98, 164,},
	{105, 173,},
	{111, 185,},
	{119, 195,},
	{126, 206,},
	{134, 215,},
	{143, 230,},
	{152, 242,},
	{162, 256,},
	{172, 256,},
	{183, 256,},
	{195, 256,},
	{207, 256,},
	{220, 256,},
	{234, 256,},
	{249, 256,},
	{265, 270,},
	{282, 286,},
	{300, 303,},
	{316, 319,},
	{333, 333,},
	{360, 360,},
};
static int gradation_offset_revC[][9] = {
/*	V255 V203 V151 V87 V51 V35 V23 V11 V3 */
	{0, 6, 12, 22, 29, 32, 35, 40, 43},
	{0, 6, 11, 20, 25, 29, 32, 37, 36},
	{0, 5, 9, 18, 23, 27, 29, 33, 32},
	{0, 5, 9, 17, 21, 25, 27, 31, 33},
	{0, 4, 7, 15, 19, 23, 25, 29, 28},
	{0, 4, 7, 14, 17, 21, 23, 27, 25},
	{0, 4, 6, 13, 17, 20, 22, 26, 25},
	{0, 4, 6, 12, 16, 19, 20, 24, 23},
	{0, 3, 6, 12, 15, 18, 19, 23, 23},
	{0, 3, 5, 12, 14, 17, 18, 22, 22},
	{0, 3, 5, 11, 14 , 16, 17, 21, 21},
	{0, 3, 5, 11, 13, 15, 16, 20, 19},
	{0, 3, 5, 10, 13, 15, 16, 19, 22},
	{0, 3, 4, 9, 12, 13, 14, 18, 18},
	{0, 3, 4, 9, 11, 13, 14, 17, 19},
	{0, 3, 4, 9, 11, 12, 12, 16, 15},
	{0, 3, 4, 8, 10, 12, 13, 16, 19},
	{0, 2, 3, 8, 10, 11, 12, 15, 15},
	{0, 3, 3, 8, 10, 11, 11, 14, 17},
	{0, 2, 3, 7, 8, 10, 10, 13, 15},
	{0, 2, 3, 7, 8, 9, 9, 13, 13},
	{0, 2, 3, 7, 8, 9, 9, 13, 12},
	{0, 2, 3, 7, 7, 8, 9, 12, 12},
	{0, 2, 2, 6, 7, 8, 9, 12, 12},
	{0, 2, 2, 6, 7, 8, 8, 11, 10},
	{0, 2, 2, 5, 6, 7, 8, 10, 12},
	{0, 2, 2, 5, 6, 7, 7, 10, 11},
	{0, 2, 2, 5, 5, 6, 7, 9, 9},
	{0, 2, 2, 5, 5, 5, 7, 9, 9},
	{0, 2, 1, 4, 5, 5, 7, 9, 7},
	{0, 2, 1, 4, 4, 5, 6, 7, 4},
	{0, 2, 1, 4, 4, 4, 5, 7, 9},
	{0, 2, 1, 4, 4, 4, 5, 7, 8},
	{0, 2, 1, 4, 4, 4, 5, 7, 4},
	{0, 1, 1, 4, 4, 4, 5, 6, 6},
	{0, 1, 1, 3, 4, 4, 5, 6, 4},
	{0, 2, 1, 4, 4, 4, 5, 6, 7},
	{0, 2, 1, 3, 4, 3, 4, 6, 2},
	{0, 2, 2, 4, 5, 5, 5, 6, 5},
	{0, 1, 2, 4, 4, 4, 4, 6, 4},
	{0, 1, 2, 4, 4, 3, 5, 6, 7},
	{0, 2, 2, 4, 4, 4, 5, 6, 6},
	{0, 1, 2, 3, 4, 3, 4, 5, 4},
	{0, 2, 2, 4, 4, 3, 4, 5, 4},
	{0, 2, 2, 3, 4, 4, 3, 5, 5},
	{0, 3, 3, 3, 3, 3, 3, 5, 3},
	{0, 2, 2, 2, 3, 2, 3, 4, 3},
	{0, 3, 3, 3, 3, 2, 3, 4, 4},
	{0, 1, 2, 2, 3, 3, 2, 4, 2},
	{0, 1, 2, 2, 3, 3, 2, 4, 0},
	{0, 1, 1, 2, 2, 2, 1, 3, 1},
	{0, 1, 1, 2, 2, 1, 1, 2, 3},
	{0, 1, 1, 1, 1, 1, 1, 2, 0},
	{0, 1, 1, 1, 1, 1, 1, 2, 2},
	{0, 1, 0, 1, 1, 1, 0, 2, 0},
	{0, 0, 1, 1, 1, 1, 1, 2, 0},
	{0, 1, 1, 1, 1, 1, 1, 2, 0},
	{0, 1, 1, 1, 0, 1, 1, 1, 1},
	{0, 1, 1, 0, 0, 0, 1, 1, 1},
	{0, 0, -1, -1, -1, -1, 0, 1, 0},
	{0, 1, 0, -1, -1, 0, 0, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static int rgb_offset_revC[][RGB_COMPENSATION] = {
/*	R255 G255 B255 R203 G203 B203 R151 G151 B151 R87 G87 B87 R51 G51 B51 R35 G35 B35  R23 G23 B23 R11 G11 B11*/
	{-5, 0, -4, -5, 1, -4, -5, 1, -4, -8, 4, -7, -10, 4, -8, -10, 3, -6, -8, 2, -6, -7, 2, -4},
	{-4, 0, -4, -4, 0, -4, -4, 1, -4, -9, 3, -8, -13, 4, -10, -11, 3, -8, -5, 3, -6, -8, 2, -5},
	{-3, 0, -3, -3, 0, -4, -6, 0, -4, -9, 3, -8, -11, 4, -9, -8, 3, -7, -8, 4, -8, -10, 3, -6},
	{-3, 0, -3, -2, 0, -3, -6, 0, -4, -7, 3, -7, -11, 3, -8, -9, 3, -8, -8, 4, -9, -11, 3, -8},
	{-3, 0, -3, -2, 0, -2, -5, 0, -4, -7, 3, -6, -11, 3, -8, -8, 4, -9, -8, 3, -8, -10, 3, -8},
	{-2, 0, -2, -3, 0, -3, -4, 0, -2, -6, 3, -6, -11, 3, -8, -9, 4, -9, -6, 3, -8, -11, 4, -8},
	{-1, 0, -1, -3, 0, -3, -4, 0, -3, -6, 2, -6, -10, 3, -8, -9, 4, -10, -7, 3, -8, -10, 4, -8},
	{-1, 0, -1, -3, 0, -3, -3, 0, -2, -6, 2, -5, -9, 3, -6, -7, 4, -8, -10, 5, -12, -12, 3, -7},
	{-1, 0, -1, -2, 0, -3, -3, 0, -2, -5, 2, -4, -10, 3, -8, -8, 4, -10, -8, 3, -8, -11, 4, -8},
	{-1, 0, -1, -1, 0, -2, -4, 0, -4, -4, 2, -4, -11, 3, -8, -8, 4, -9, -7, 4, -9, -12, 4, -9},
	{0, 0, 0, -2, 0, -3, -4, 0, -3, -4, 2, -4, -9, 3, -7, -8, 4, -9, -6, 4, -8, -12, 4, -9},
	{0, 0, 0, -2, 0, -3, -3, 0, -3, -4, 2, -4, -9, 3, -7, -8, 4, -9, -7, 4, -8, -11, 4, -9},
	{0, 0, 0, -2, 0, -3, -3, 0, -3, -4, 1, -4, -9, 3, -8, -8, 4, -8, -7, 4, -8, -14, 4, -10},
	{0, 0, 0, -1, 0, -1, -3, 0, -3, -5, 1, -4, -8, 3, -7, -8, 4, -9, -7, 4, -8, -12, 4, -9},
	{0, 0, 0, -1, 0, -1, -3, 0, -3, -4, 1, -3, -8, 3, -7, -7, 3, -8, -7, 4, -9, -14, 5, -11},
	{0, 0, 0, -1, 0, -1, -3, 0, -3, -4, 1, -3, -7, 3, -6, -8, 4, -9, -7, 3, -8, -13, 4, -9},
	{0, 0, 0, -1, 0, -1, -3, 0, -3, -4, 1, -4, -6, 3, -6, -8, 3, -8, -6, 4, -8, -14, 5, -10},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -4, 1, -4, -6, 3, -6, -7, 3, -7, -7, 3, -8, -14, 5, -10},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -4, 1, -4, -6, 2, -6, -7, 3, -7, -6, 4, -8, -14, 5, -11},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -2, 1, -2, -6, 3, -7, -6, 3, -6, -7, 4, -8, -13, 5, -11},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -1, 1, -2, -6, 3, -6, -7, 3, -6, -6, 4, -8, -13, 4, -10},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -2, 0, -2, -6, 3, -7, -7, 3, -6, -6, 3, -8, -12, 5, -10},
	{0, 0, 0, -1, 0, -1, -2, 0, -2, -1, 0, -2, -6, 3, -6, -7, 2, -6, -6, 3, -8, -11, 5, -10},
	{0, 0, 0, 0, 0, -1, -2, 0, -2, -2, 0, -2, -6, 2, -6, -7, 2, -6, -6, 3, -8, -11, 4, -10},
	{0, 0, 0, 0, 0, -1, -1, 0, -2, -3, 0, -2, -4, 2, -5, -6, 2, -4, -6, 3, -8, -10, 5, -10},
	{0, 0, 0, 0, 0, -1, -1, 0, -2, -3, 0, -1, -4, 2, -5, -6, 2, -4, -5, 3, -6, -12, 5, -12},
	{0, 0, 0, 0, 0, -1, -1, 0, -2, -2, 0, 0, -4, 2, -5, -6, 2, -4, -6, 3, -8, -11, 4, -10},
	{0, 0, 0, 0, 0, -1, -1, 0, -2, -2, 0, 0, -3, 2, -5, -5, 1, -3, -4, 3, -7, -10, 5, -11},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -3, 0, -1, -2, 2, -4, -7, 1, -4, -4, 3, -6, -9, 5, -10},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -3, 0, -2, -2, 2, -4, -7, 1, -4, -4, 2, -6, -9, 5, -10},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -2, 0, -1, -3, 2, -5, -4, 1, -2, -3, 2, -5, -9, 5, -10},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -2, 0, -1, -2, 2, -4, -5, 1, -2, -3, 2, -6, -11, 5, -11},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, -1, -3, 2, -4, -5, 0, -2, -4, 2, -6, -9, 4, -10},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, -1, -3, 1, -4, -5, 0, -2, -3, 2, -5, -7, 4, -9},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, -1, -3, 1, -4, -4, 0, -1, -2, 2, -4, -9, 5, -11},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, -1, 0, 0, -1, 1, -3, -4, 0, -1, -2, 2, -4, -8, 5, -10},
	{0, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, 0, -2, 1, -3, -4, 0, -1, -2, 2, -4, -9, 5, -11},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, -1, 1, -4, -4, 0, -2, -3, 2, -5, -7, 3, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, -3, 0, -2, 0, 1, -2, -4, 0, -2, -3, 2, -4, -8, 4, -10},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 1, -4, -5, 0, -2, -3, 1, -4, -7, 4, -10},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, -2, 0, -1, 0, 1, -3, -4, 0, -2, -3, 1, -4, -8, 4, -10},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, -1, 0, 1, -2, -4, 0, -2, -2, 2, -4, -8, 4, -10},
	{0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, -1, -1, 1, -2, -3, 1, -2, -2, 1, -4, -7, 4, -9},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 1, -3, -2, 0, -2, -3, 1, -3, -6, 4, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 1, -2, -2, 1, -3, -4, 1, -3, -6, 3, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 1, 1, -2, -2, 0, -1, -4, 1, -3, -6, 3, -8},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 1, 1, -2, -3, 0, -2, -3, 1, -3, -4, 3, -7},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 1, 1, -2, -3, 0, -2, -3, 0, -2, -5, 3, -8},
	{0, 0, 1, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, -2, -1, 1, -3, -4, 1, -2, -3, 3, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, -1, 0, 0, -2, 0, 1, -2, -4, 0, -2, -3, 3, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -2, -1, 0, -1, -2, 0, -1, -3, 2, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, -2, 0, 0, -1, -1, 0, 0, -4, 2, -6},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2, 0, 0, 0, -2, 0, 0, -2, 2, -5},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, -1, -1, 0, -1, -1, 0, 0, -5, 1, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, -1, 0, 0, 0, -1, 0, 0, -3, 2, -4},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

#endif
