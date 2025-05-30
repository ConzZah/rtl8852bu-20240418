/*
 * This module is designed to collect internal diagnostic information.
 *
 *	Author: Cosa
 *	History: Created at 2023/02/03
 */

#ifndef _PHL_DIAGNOSE_H_
#define _PHL_DIAGNOSE_H_

#define MAX_PHL_DIAG_MSG_LEN 1024
#define INVALID_SUBMODULE_DIAG_EVT 0xff

enum rtw_phl_diag_evt_level {
	PHL_DIAG_LVL_FATAL = 0x0, /* unrecoverable error */
	PHL_DIAG_LVL_CRITICAL = 0x1, /* severe error events */
	PHL_DIAG_LVL_ERROR = 0x2, /* non-severe error events */
	PHL_DIAG_LVL_MAX
};

enum rtw_phl_diag_evt_type {
	PHL_DIAG_EVT_MAC = 0,
	PHL_DIAG_EVT_BB,
	PHL_DIAG_EVT_RF,
	PHL_DIAG_EVT_BTC,
	PHL_DIAG_EVT_LEAVE_PS_FAIL,
	PHL_DIAG_EVT_SER,
	PHL_DIAG_EVT_MAX
};

enum rtw_phl_diag_ser_type {
	PHL_DIAG_SER_L1,
	PHL_DIAG_SER_L2,
	PHL_DIAG_SER_UNKNOWN,
};

enum rtw_phl_diag_ps_mode {
	PHL_DIAG_PS_LPS,
	PHL_DIAG_PS_IPS,
	PHL_DIAG_PS_UNKNOWN,
};

struct diag_ser_content_v1 {
	u8 diag_ser_type;
};

struct diag_leave_ps_fail_content_v1 {
	u8 diag_ps_mode;
};

struct rtw_phl_diag_msg {
	enum rtw_phl_diag_evt_type type;
	enum rtw_phl_diag_evt_level level;
	u8 sub_evt; /* submodule event id */
	u8 ver; /* version of debug content */
	u32 len;
	u8 buf[MAX_PHL_DIAG_MSG_LEN];
};

bool phl_send_diag_hub_msg(void *phl, u16 phl_evt, u8 sub_evt,
	u8 level, u8 ver, u8 *buf, u32 len);

#endif /* _PHL_DIAGNOSE_H_ */

