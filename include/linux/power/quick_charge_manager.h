/*
 * Author: Basile Maret <basile.maret@gmail.com>
 *
 * This is a module to configure Quick Charge 2.0
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _QUICK_CHARGE_MANAGER_H
#define _QUICK_CHARGE_MANAGER_H

#define TAG					"QC2.0 : "
#define ENABLE_QUICK_CHARGE			1
#define NO_IBATMAX				-1
#define MAX_IBATMAX_MA_UNDER_STEP		2150
#define IBATMAX_MA_UNDER_STEP_DEFAULT		2150
#define MAX_BAT_CHG_CURRENT			2150
#define SAFE_CURRENT				2150
#define MAXINPUT_MV				13000

#define DEFAULT_PIN_CODE                        0
#define CORRECT_PIN_CODE                        535218

extern int qc_enabled;
extern int ibatmax_ma_under_step;

#endif
