GCOV_PROFILE := y
EXTRA_CFLAGS += -Idrivers/video/tegra/host

nvhost-objs = \
	nvhost_acm.o \
	nvhost_syncpt.o \
	nvhost_cdma.o \
	nvhost_intr.o \
	nvhost_channel.o \
	nvhost_job.o \
	dev.o \
	debug.o \
	bus_client.o \
	chip_support.o \
	nvhost_memmgr.o \

obj-$(CONFIG_TEGRA_GRHOST) += mpe/
obj-$(CONFIG_TEGRA_GRHOST) += gr3d/
obj-$(CONFIG_TEGRA_GRHOST) += host1x/
obj-$(CONFIG_TEGRA_GRHOST) += t20/
obj-$(CONFIG_TEGRA_GRHOST) += t30/
obj-$(CONFIG_TEGRA_GRHOST) += gr2d/
obj-$(CONFIG_TEGRA_GRHOST) += isp/
# sk1wg: always; the V4L2 host (VIDEO_TEGRA) is a separate device that
# drives the VI through this nvhost client, not a replacement for it
obj-$(CONFIG_TEGRA_GRHOST) += vi/
obj-$(CONFIG_TEGRA_GRHOST) += t114/
obj-$(CONFIG_TEGRA_GRHOST) += msenc/
obj-$(CONFIG_TEGRA_GRHOST) += tsec/
obj-$(CONFIG_TEGRA_GRHOST) += nvhost.o

obj-$(CONFIG_TEGRA_GRHOST_USE_NVMAP) += nvmap.o
obj-$(CONFIG_TEGRA_GRHOST_USE_DMABUF) += dmabuf.o
