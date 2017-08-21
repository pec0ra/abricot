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

#include <linux/moduleparam.h>

#include <linux/module.h>
#include <linux/input.h>
#include <linux/power_supply.h>
#include <linux/power/quick_charge_manager.h>


int ibatmax_ma_under_step = IBATMAX_MA_UNDER_STEP_DEFAULT;
int qc_enabled = ENABLE_QUICK_CHARGE;
int pin_code = DEFAULT_PIN_CODE;

static int
set_ibatmax_ma_under_step(const char *val, const struct kernel_param *kp){
	
	/* Read value from sys */
	int ret = param_set_int(val, kp);


        printk(TAG "ibatmax_ma_under_step changed to %d\n", ibatmax_ma_under_step);
	return ret;
}
static struct kernel_param_ops params_ops_change = {
       .set = set_ibatmax_ma_under_step,
       .get = param_get_uint,
};
module_param_cb(ibatmax_ma_under_step, &params_ops_change, &ibatmax_ma_under_step, 0644);

static int
set_qc_enabled(const char *val, const struct kernel_param *kp){

        int ret;
	
        if(pin_code != CORRECT_PIN_CODE){
            printk(TAG "Incorrect pin code !");
            qc_enabled = 0;
            return 1;
        }

	/* Read value from sys */
	ret = param_set_bool(val, kp);


	if(qc_enabled){
            printk(TAG "QC 2.0 enabled");
            printk(TAG "ibatmax_ma_under_step is set to %d\n", ibatmax_ma_under_step);
	} else {
            printk(TAG "QC 2.0 disabled");

	}
	return ret;
}
static struct kernel_param_ops params_ops_enable = {
       .set = set_qc_enabled,
       .get = param_get_uint,
};
module_param_cb(qc_enabled, &params_ops_enable, &qc_enabled, 0644);

static int
set_pin_code(const char *val, const struct kernel_param *kp){
	
	/* Read value from sys */
	int ret = param_set_int(val, kp);


        printk(TAG "Pin set to  %d\n", pin_code);
	return ret;
}
static struct kernel_param_ops params_ops_pin = {
       .set = set_pin_code,
       .get = param_get_uint,
};
module_param_cb(pin_code, &params_ops_pin, &pin_code, 0644);
