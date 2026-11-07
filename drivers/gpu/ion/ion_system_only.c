/*
 * drivers/gpu/ion/ion_system_only.c
 *
 * Minimal ION device with a single vmalloc-backed system heap.
 *
 * Android 14's Codec2 needs a linear buffer allocator: either DMA-BUF
 * heaps (/dev/dma_heap/system, kernel 5.6+) or ION (/dev/ion). Boards
 * that use nvmap for graphics register no ION device, so without this
 * driver every MediaCodec start fails with NO_MEMORY. Codec2's
 * C2AllocatorIon and libion speak this kernel's legacy ION ABI
 * (ION_IOC_ALLOC + ION_IOC_SHARE/ION_IOC_MAP).
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#define pr_fmt(fmt) "ion-system-only: " fmt

#include <linux/err.h>
#include <linux/init.h>
#include <linux/ion.h>
#include <linux/module.h>
#include "ion_priv.h"

static struct ion_device *idev;
static struct ion_heap *system_heap;

static struct ion_platform_heap system_heap_data = {
	.type = ION_HEAP_TYPE_SYSTEM,
	.id = ION_HEAP_TYPE_SYSTEM,
	.name = "system",
};

static int __init ion_system_only_init(void)
{
	idev = ion_device_create(NULL);
	if (IS_ERR_OR_NULL(idev)) {
		pr_err("cannot create the ion device\n");
		return idev ? PTR_ERR(idev) : -ENOMEM;
	}

	system_heap = ion_heap_create(&system_heap_data);
	if (IS_ERR_OR_NULL(system_heap)) {
		pr_err("cannot create the system heap\n");
		ion_device_destroy(idev);
		return system_heap ? PTR_ERR(system_heap) : -ENOMEM;
	}

	ion_device_add_heap(idev, system_heap);
	pr_info("/dev/ion ready (system heap)\n");
	return 0;
}

static void __exit ion_system_only_exit(void)
{
	ion_device_destroy(idev);
	ion_heap_destroy(system_heap);
}

module_init(ion_system_only_init);
module_exit(ion_system_only_exit);
MODULE_LICENSE("GPL v2");
