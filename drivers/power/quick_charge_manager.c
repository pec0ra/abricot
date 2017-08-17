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

// TODO: Does nothing yet as variables need to be imported in qpnp-charger.c

#include <linux/module.h>
#include <linux/input.h>
#include <linux/power/quick_charge_manager.h>


static int ibatmax_ma_under_step = IBATMAX_MA_UNDER_STEP_DEFAULT;
static int qc_enabled = ENABLE_QUICK_CHARGE;

static int
set_ibatmax_ma_under_step(const char *val, const struct kernel_param *kp){
	int rc = 0;
	
	/* Read value from sys */
	int ret = param_set_int(val, kp);

	struct power_supply *batt_psy = power_supply_get_by_name("battery");
	struct qpnp_chg_chip *chip = container_of(batt_psy,
				struct qpnp_chg_chip, batt_psy);
	if(qc_enabled){
		printk(TAG "Changing ibatmax_ma_under_step to %d\n", ibatmax_ma_under_step);
		chip->somc_params.stepchg_ibatmax_ma_under_step = ibatmax_ma_under_step;
	} else {
		printk(TAG "QC not enabled. keeping ibatmax_ma_under_step to %d\n", chip->somc_params.stepchg_ibatmax_ma_under_step);
		if (rc)
			pr_err("failed to read required dt parameters %d\n", rc);
	}
	return ret;
}
static struct kernel_param_ops params_ops_change = {
       .set = set_ibatmax_ma_under_step,
       .get = param_get_uint,
};
module_param_cb(ibatmax_ma_under_step, &params_ops_change, &ibatmax_ma_under_step, 0644);

static int
set_qc_enabled(const char *val, const struct kernel_param *kp){
	int rc = 0;
	
	/* Read value from sys */
	int ret = param_set_bool(val, kp);

	struct power_supply *batt_psy = power_supply_get_by_name("battery");
	struct qpnp_chg_chip *chip = container_of(batt_psy,
				struct qpnp_chg_chip, batt_psy);

	if(qc_enabled){
		chip->somc_params.stepchg_ibatmax_ma_under_step = ibatmax_ma_under_step;
		chip->max_bat_chg_current = MAX_BAT_CHG_CURRENT;
		chip->safe_current = SAFE_CURRENT;
		chip->somc_params.maxinput_usb_mv = MAXINPUT_MV;
		chip->somc_params.maxinput_dc_mv = MAXINPUT_MV;
		printk(TAG "QC 2.0 enabled");
		printk(TAG "ibatmax_ma_under_step is set to %d\n", ibatmax_ma_under_step);
	} else {
		OF_PROP_READ(chip, safe_current, "ibatsafe-ma", rc, 0);
		OF_PROP_READ(chip, max_bat_chg_current, "ibatmax-ma", rc, 0);
	
		OF_PROP_READ(chip, somc_params.maxinput_dc_mv, "maxinput-dc-mv",
				rc, 1);
		OF_PROP_READ(chip, somc_params.maxinput_usb_mv, "maxinput-usb-mv",
				rc, 1);
		OF_PROP_READ(chip, somc_params.stepchg_ibatmax_ma_under_step,
				"ibatmax-ma-under-step", rc, 1);
		if (rc)
			pr_err("failed to read required dt parameters %d\n", rc);
		printk(TAG "QC 2.0 disabled");

	}
	return ret;
}
static struct kernel_param_ops params_ops_enable = {
       .set = set_qc_enabled,
       .get = param_get_uint,
};
module_param_cb(qc_enabled, &params_ops_enable, &qc_enabled, 0644);
