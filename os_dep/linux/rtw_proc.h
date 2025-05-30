/******************************************************************************
 *
 * Copyright(c) 2007 - 2019 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#ifndef __RTW_PROC_H__
#define __RTW_PROC_H__

#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define RTW_PROC_HDL_TYPE_SEQ	0
#define RTW_PROC_HDL_TYPE_SSEQ	1
#define RTW_PROC_HDL_TYPE_SZSEQ	2

struct rtw_proc_hdl {
	char *name;
	u8 type;
	union {
		int (*show)(struct seq_file *, void *);
		struct seq_operations *seq_op;
		struct {
			int (*show)(struct seq_file *, void *);
			size_t size;
		} sz;
	} u;
	ssize_t (*write)(struct file *file, const char __user *buffer, size_t count, loff_t *pos, void *data);
};

#define RTW_PROC_HDL_SEQ(_name, _seq_op, _write) \
	{ .name = _name, .type = RTW_PROC_HDL_TYPE_SEQ, .u.seq_op = _seq_op, .write = _write}

#define RTW_PROC_HDL_SSEQ(_name, _show, _write) \
	{ .name = _name, .type = RTW_PROC_HDL_TYPE_SSEQ, .u.show = _show, .write = _write}

#define RTW_PROC_HDL_SZSEQ(_name, _show, _write, _size) \
	{ .name = _name, .type = RTW_PROC_HDL_TYPE_SZSEQ, .u.sz.show = _show, .write = _write, .u.sz.size = _size}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0))
#define rtw_proc_ops proc_ops
#else
#define rtw_proc_ops file_operations
#endif

#ifdef CONFIG_PROC_DEBUG

int rtw_drv_proc_init(void);
void rtw_drv_proc_deinit(void);
struct proc_dir_entry *rtw_adapter_proc_init(struct net_device *dev);
void rtw_adapter_proc_deinit(struct net_device *dev);
void rtw_adapter_proc_replace(struct net_device *dev);

#ifdef CONFIG_SELF_DIAG_INFO
static int proc_get_self_diag_info(struct seq_file *m, void *v);
static ssize_t proc_set_self_diag_info(struct file *file, const char __user *buffer, size_t count, loff_t *pos, void *data);
#endif

#else /* !CONFIG_PROC_DEBUG */

static inline int rtw_drv_proc_init(void) {return _FAIL;}
#define rtw_drv_proc_deinit() do {} while (0)
static inline struct proc_dir_entry *rtw_adapter_proc_init(struct net_device *dev) {return NULL;}
#define rtw_adapter_proc_deinit(dev) do {} while (0)
#define rtw_adapter_proc_replace(dev) do {} while (0)

#endif /* !CONFIG_PROC_DEBUG */

#endif /* __RTW_PROC_H__ */
