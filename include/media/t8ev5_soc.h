/*
 * T8EV5 / MT9P111 (Jide Remix Ultra Tablet) on the soc_camera framework.
 *
 * The board registers one "soc-camera-pdrv" device per camera with an
 * I2C_BOARD_INFO("t8ev5-soc", 0x3c) and this as its platform data;
 * soc_camera hands the sensor driver &link, so the rest is found with
 * container_of(). link.priv is the Tegra host's
 * struct tegra_camera_platform_data for this camera.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 */

#ifndef __MEDIA_T8EV5_SOC_H__
#define __MEDIA_T8EV5_SOC_H__

#include <linux/types.h>
#include <media/soc_camera.h>

struct yuv_t8ev5_sensor_platform_data;

struct t8ev5_soc_camera_link {
	struct soc_camera_link link;
	/* the board's power hooks, as for the misc ("t8ev5") driver */
	struct yuv_t8ev5_sensor_platform_data *sensor;
	/* T8EV5_FRONT_ID for the front camera, 0 for the back one */
	u8 flag;
	/* CSI-2 data lanes, reported by g_mbus_config */
	int lanes;
};

static inline struct t8ev5_soc_camera_link *
to_t8ev5_soc_camera_link(struct soc_camera_link *icl)
{
	return container_of(icl, struct t8ev5_soc_camera_link, link);
}

#endif /* __MEDIA_T8EV5_SOC_H__ */
