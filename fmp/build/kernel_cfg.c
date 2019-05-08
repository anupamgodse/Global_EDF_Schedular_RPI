/* kernel_cfg.c */
#include "kernel/kernel_int.h"
#include "kernel_cfg.h"

#if TKERNEL_PRID != 0x08u
#error The kernel does not match this configuration file.
#endif

/*
 *  Include Directives (#include)
 */

#include "sample1.h"
#include "target_timer.h"
#include "syssvc/syslog.h"
#include "syssvc/banner.h"
#include "target_syssvc.h"
#include "target_syssvc.h"
#include "target_serial.h"
#include "syssvc/serial.h"
#include "syssvc/logtask.h"
#include "target_ipi.h"

/*
 *  Default Definitions of Trace Log Macros
 */

#ifndef LOG_ISR_ENTER
#define LOG_ISR_ENTER(intno)
#endif /* LOG_ISR_ENTER */

#ifndef LOG_ISR_LEAVE
#define LOG_ISR_LEAVE(intno)
#endif /* LOG_ISR_LEAVE */

/*
 *  Processor Management Functions
 */

PCB _kernel_prc1_pcb;

PCB* const _kernel_p_pcb_table[TNUM_PRCID] = {
	&_kernel_prc1_pcb
};

/*
 *  Task Management Functions
 */

const ID _kernel_tmax_tskid = (TMIN_TSKID + TNUM_TSKID - 1);

static STK_T _kernel_stack_LOGTASK1[COUNT_STK_T(LOGTASK_STACK_SIZE)];
static STK_T _kernel_stack_TASK1_1[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_TASK1_2[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_TASK1_3[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_MAIN_TASK1[COUNT_STK_T(STACK_SIZE)];
static STK_T _kernel_stack_SERVER_TASK1[COUNT_STK_T(STACK_SIZE)];

const TINIB _kernel_tinib_table[TNUM_TSKID] = {
	{ (TA_ACT), (intptr_t)(LOGTASK_PORTID_G_SYSLOG), ((TASK)(logtask_main)), INT_PRIORITY(LOGTASK_PRIORITY), ROUND_STK_T(LOGTASK_STACK_SIZE), _kernel_stack_LOGTASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x10000|1), ((TASK)(task)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1_1, (TA_NULL), (tex_routine), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x10000|2), ((TASK)(task)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1_2, (TA_NULL), (tex_routine), 1, (uint_t)(0x0000000f) },
	{ (TA_NULL), (intptr_t)(0x10000|3), ((TASK)(task)), INT_PRIORITY(MID_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_TASK1_3, (TA_NULL), (tex_routine), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(1), ((TASK)(main_task)), INT_PRIORITY(MAIN_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_MAIN_TASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) },
	{ (TA_ACT), (intptr_t)(1), ((TASK)(server_task)), INT_PRIORITY(SERVER_PRIORITY), ROUND_STK_T(STACK_SIZE), _kernel_stack_SERVER_TASK1, (TA_NULL), (NULL), 1, (uint_t)(0x0000000f) }
};

TCB _kernel_tcb_LOGTASK1;
TCB _kernel_tcb_TASK1_1;
TCB _kernel_tcb_TASK1_2;
TCB _kernel_tcb_TASK1_3;
TCB _kernel_tcb_MAIN_TASK1;
TCB _kernel_tcb_SERVER_TASK1;


TCB* const _kernel_p_tcb_table[TNUM_TSKID] ={
	&_kernel_tcb_LOGTASK1,
	&_kernel_tcb_TASK1_1,
	&_kernel_tcb_TASK1_2,
	&_kernel_tcb_TASK1_3,
	&_kernel_tcb_MAIN_TASK1,
	&_kernel_tcb_SERVER_TASK1
};

const ID _kernel_torder_table[TNUM_TSKID] = {
	LOGTASK1, TASK1_1, TASK1_2, TASK1_3, MAIN_TASK1, SERVER_TASK1
};

/*
 *  Semaphore Functions
 */

const ID _kernel_tmax_semid = (TMIN_SEMID + TNUM_SEMID - 1);

const SEMINIB _kernel_seminib_table[TNUM_SEMID] = {
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (0), (1) },
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (1), (1) }
};

SEMCB _kernel_semcb_SERIAL_RCV_SEM1;
SEMCB _kernel_semcb_SERIAL_SND_SEM1;

SEMCB* const _kernel_p_semcb_table[TNUM_SEMID] = {
	&_kernel_semcb_SERIAL_RCV_SEM1,
	&_kernel_semcb_SERIAL_SND_SEM1
};

/*
 *  Eventflag Functions
 */

const ID _kernel_tmax_flgid = (TMIN_FLGID + TNUM_FLGID - 1);

TOPPERS_EMPTY_LABEL(const FLGINIB, _kernel_flginib_table);
TOPPERS_EMPTY_LABEL(FLGCB* const, _kernel_p_flgcb_table);

/*
 *  Dataqueue Functions
 */

const ID _kernel_tmax_dtqid = (TMIN_DTQID + TNUM_DTQID - 1);

static DTQMB _kernel_dtqmb_SERVER_DTQ1[NUM_SERVER_DTQ];

const DTQINIB _kernel_dtqinib_table[TNUM_DTQID] = {
	{ (TA_TPRI), (&(_kernel_prc1_pcb.obj_lock)), (NUM_SERVER_DTQ), (_kernel_dtqmb_SERVER_DTQ1) }
};

DTQCB _kernel_dtqcb_SERVER_DTQ1;

DTQCB* const _kernel_p_dtqcb_table[TNUM_DTQID] = {
	&_kernel_dtqcb_SERVER_DTQ1
};

/*
 *  Priority Dataqueue Functions
 */

const ID _kernel_tmax_pdqid = (TMIN_PDQID + TNUM_PDQID - 1);

TOPPERS_EMPTY_LABEL(const PDQINIB, _kernel_pdqinib_table);
TOPPERS_EMPTY_LABEL(PDQCB* const, _kernel_p_pdqcb_table);

/*
 *  Mailbox Functions
 */

const ID _kernel_tmax_mbxid = (TMIN_MBXID + TNUM_MBXID - 1);

TOPPERS_EMPTY_LABEL(const MBXINIB, _kernel_mbxinib_table);
TOPPERS_EMPTY_LABEL(MBXCB* const, _kernel_p_mbxcb_table);

/*
 *  Fixed-sized Memorypool Functions
 */

const ID _kernel_tmax_mpfid = (TMIN_MPFID + TNUM_MPFID - 1);

TOPPERS_EMPTY_LABEL(const MPFINIB, _kernel_mpfinib_table);
TOPPERS_EMPTY_LABEL(MPFCB* const, _kernel_p_mpfcb_table);

/*
 *  Cyclic Handler Functions
 */

const ID _kernel_tmax_cycid = (TMIN_CYCID + TNUM_CYCID - 1);

const CYCINIB _kernel_cycinib_table[TNUM_CYCID] = {
	{ (TA_NULL), (intptr_t)(1), (cyclic_handler), (CYC_TIME), (0), 1, (uint_t)(0x0000000f) }
};

CYCCB _kernel_cyccb_CYCHDR1;

CYCCB* const _kernel_p_cyccb_table[TNUM_CYCID] = {
	&_kernel_cyccb_CYCHDR1
};

/*
 *  Alarm Handler Functions
 */

const ID _kernel_tmax_almid = (TMIN_ALMID + TNUM_ALMID - 1);

const ALMINIB _kernel_alminib_table[TNUM_ALMID] = {
	{ (TA_NULL), (intptr_t)(1), (alarm_handler), 1, (uint_t)(0x0000000f) }
};

ALMCB _kernel_almcb_ALMHDR1;

ALMCB* const _kernel_p_almcb_table[TNUM_ALMID] = {
	&_kernel_almcb_ALMHDR1
};

/*
 *  Spin Lock Functions
 */

const ID _kernel_tmax_spnid = (TMIN_SPNID + TNUM_SPNID - 1);

TOPPERS_EMPTY_LABEL(const SPNINIB, _kernel_spninib_table);
TOPPERS_EMPTY_LABEL(SPNCB* const, _kernel_p_spncb_table);

/*
 *  Interrupt Management Functions
 */

void
_kernel_inthdr_93(void)
{
	i_begin_int(93);
	LOG_ISR_ENTER(93);
	((ISR)(sio_isr))((intptr_t)(1));
 	LOG_ISR_LEAVE(93);
	i_end_int(93);
}

#define TNUM_INHNO	3
const uint_t _kernel_tnum_inhno = TNUM_INHNO;

INTHDR_ENTRY(INHNO_TIMER_PRC1, 0x10001, target_timer_handler)
INTHDR_ENTRY(INHNO_IPI_DIS_PRC1, 0x10004, _kernel_ipi_handler)
INTHDR_ENTRY(93, 0x5d, _kernel_inthdr_93)

const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {
	{ (INHNO_TIMER_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_TIMER_PRC1, target_timer_handler)), 1, (uint_t)(0x1) },
	{ (INHNO_IPI_DIS_PRC1), (TA_NULL), (FP)(INT_ENTRY(INHNO_IPI_DIS_PRC1, _kernel_ipi_handler)), 1, (uint_t)(0x1) },
	{ (93), (TA_NULL), (FP)(INT_ENTRY(93, _kernel_inthdr_93)), 1, (uint_t)(0x1) }
};

#define TNUM_INTNO	3
const uint_t _kernel_tnum_intno = TNUM_INTNO;

const INTINIB _kernel_intinib_table[TNUM_INTNO] = {
	{ (INTNO_TIMER_PRC1), (TA_ENAINT|INTATR_TIMER), (INTPRI_TIMER),  1, (uint_t)(0x1)},
	{ (INTNO_SIO), (INTATR_SIO), (INTPRI_SIO),  1, (uint_t)(0x1)},
	{ (INTNO_IPI_DIS_PRC1), (TA_ENAINT), (INTPRI_IPI_DIS_PRC1),  1, (uint_t)(0x1)}
};

/*
 *  CPU Exception Management Functions
 */

/*
 *  Stack Area for Non-task Context
 */

#ifdef DEFAULT_PRC1_ISTK
#define TOPPERS_PRC1_ISTKSZ		DEFAULT_PRC1_ISTKSZ
#define TOPPERS_PRC1_ISTK		DEFAULT_PRC1_ISTK
#else /* DEAULT_PRC1_ISTK */
static STK_T _kernel_prc1_istack[COUNT_STK_T(DEFAULT_PRC1_ISTKSZ)];

#define TOPPERS_PRC1_ISTKSZ		ROUND_STK_T(DEFAULT_PRC1_ISTKSZ)
#define TOPPERS_PRC1_ISTK		_kernel_prc1_istack
#endif /* DEAULT_PRC1_ISTK */

const SIZE _kernel_istksz_table[TNUM_PRCID] = {
	TOPPERS_PRC1_ISTKSZ
};

STK_T *const _kernel_istk_table[TNUM_PRCID] = {
	TOPPERS_PRC1_ISTK
};

#ifdef TOPPERS_ISTKPT
STK_T *const _kernel_istkpt_table[TNUM_PRCID] = {
	TOPPERS_ISTKPT(TOPPERS_PRC1_ISTK, TOPPERS_PRC1_ISTKSZ)
};
#endif /* TOPPERS_ISTKPT */

/*
 *  Time Event Management
 */

TMEVTN   _kernel_prc1_tmevt_heap[TNUM_TSKID + TNUM_CYCID + TNUM_ALMID];

TMEVTN* const _kernel_p_tmevt_heap_table[TNUM_PRCID] = {
	 _kernel_prc1_tmevt_heap
};

TEVTCB   _kernel_prc1_tevtcb;

TEVTCB* const _kernel_p_tevtcb_table[TNUM_PRCID] = {
	 &_kernel_prc1_tevtcb
};


/*
 *  Module Initialization Function
 */

void
_kernel_initialize_object(void)
{
	_kernel_initialize_task();
	_kernel_initialize_semaphore();
	_kernel_initialize_dataqueue();
	_kernel_initialize_cyclic();
	_kernel_initialize_alarm();
	_kernel_initialize_interrupt();
	_kernel_initialize_exception();
}

/*
 *  Initialization Routine
 */

void
_kernel_call_global_inirtn(void)
{
	((INIRTN)(global_inirtn))((intptr_t)(0));
}

void
_kernel_call_local_inirtn(void)
{
	if (x_prc_index() == INDEX_PRC(1)) {
		((INIRTN)(target_timer_initialize))((intptr_t)(0));
		((INIRTN)(syslog_initialize))((intptr_t)(0));
		((INIRTN)(print_banner_copyright))((intptr_t)(0));
		((INIRTN)(print_banner))((intptr_t)(0));
		((INIRTN)(sio_initialize))((intptr_t)(0));
		((INIRTN)(serial_initialize))((intptr_t)(0));
		((INIRTN)(local_inirtn))((intptr_t)(1));
	}

}

/*
 *  Termination Routine
 */

void
_kernel_call_global_terrtn(void)
{
	((TERRTN)(global_terrtn))((intptr_t)(0));
}

void
_kernel_call_local_terrtn(void)
{
	if (x_prc_index() == INDEX_PRC(1)) {
		((TERRTN)(local_terrtn))((intptr_t)(1));
		((TERRTN)(logtask_terminate))((intptr_t)(0));
		((TERRTN)(target_timer_terminate))((intptr_t)(0));
	}
}

const FP _kernel_prc1_exch_table[TNUM_EXCH] = {
	(FP)(_kernel_default_exc_handler), /* 0x10000 */
	(FP)(_kernel_default_exc_handler), /* 0x10001 */
	(FP)(_kernel_default_exc_handler), /* 0x10002 */
	(FP)(_kernel_default_exc_handler), /* 0x10003 */
	(FP)(cpuexc_handler), /* 0x10004 */
	(FP)(_kernel_default_exc_handler), /* 0x10005 */
	(FP)(_kernel_default_exc_handler), /* 0x10006 */
	(FP)(_kernel_default_exc_handler), /* 0x10007 */
	(FP)(_kernel_default_exc_handler), /* 0x10008 */
	(FP)(_kernel_default_exc_handler), /* 0x10009 */
	(FP)(_kernel_default_exc_handler), /* 0x1000a */
	(FP)(_kernel_default_exc_handler), /* 0x1000b */
	(FP)(_kernel_default_exc_handler), /* 0x1000c */
	(FP)(_kernel_default_exc_handler), /* 0x1000d */
	(FP)(_kernel_default_exc_handler), /* 0x1000e */
	(FP)(_kernel_default_exc_handler), /* 0x1000f */

};

const FP* const _kernel_p_exch_table[TNUM_PRCID] = {
	_kernel_prc1_exch_table
};

const FP _kernel_prc1_inh_table[TNUM_INH] = {
	(FP)(_kernel_default_int_handler), /* 0x10000 */
	(FP)(target_timer_handler), /* 0x10001 */
	(FP)(_kernel_default_int_handler), /* 0x10002 */
	(FP)(_kernel_default_int_handler), /* 0x10003 */
	(FP)(_kernel_ipi_handler), /* 0x10004 */
	(FP)(_kernel_default_int_handler), /* 0x10005 */
	(FP)(_kernel_default_int_handler), /* 0x10006 */
	(FP)(_kernel_default_int_handler), /* 0x10007 */
	(FP)(_kernel_default_int_handler), /* 0x10008 */
	(FP)(_kernel_default_int_handler), /* 0x10009 */
	(FP)(_kernel_default_int_handler), /* 0x1000a */
	(FP)(_kernel_default_int_handler), /* 0x1000b */
	(FP)(_kernel_default_int_handler), /* 0x1000c */
	(FP)(_kernel_default_int_handler), /* 0x1000d */
	(FP)(_kernel_default_int_handler), /* 0x1000e */
	(FP)(_kernel_default_int_handler), /* 0x1000f */
	(FP)(_kernel_default_int_handler), /* 0x10010 */
	(FP)(_kernel_default_int_handler), /* 0x10011 */
	(FP)(_kernel_default_int_handler), /* 0x10012 */
	(FP)(_kernel_default_int_handler), /* 0x10013 */
	(FP)(_kernel_default_int_handler), /* 0x10014 */
	(FP)(_kernel_default_int_handler), /* 0x10015 */
	(FP)(_kernel_default_int_handler), /* 0x10016 */
	(FP)(_kernel_default_int_handler), /* 0x10017 */
	(FP)(_kernel_default_int_handler), /* 0x10018 */
	(FP)(_kernel_default_int_handler), /* 0x10019 */
	(FP)(_kernel_default_int_handler), /* 0x1001a */
	(FP)(_kernel_default_int_handler), /* 0x1001b */
	(FP)(_kernel_default_int_handler), /* 0x1001c */
	(FP)(_kernel_default_int_handler), /* 0x1001d */
	(FP)(_kernel_default_int_handler), /* 0x1001e */
	(FP)(_kernel_default_int_handler), /* 0x1001f */
	(FP)(_kernel_default_int_handler), /* 0x10020 */
	(FP)(_kernel_default_int_handler), /* 0x10021 */
	(FP)(_kernel_default_int_handler), /* 0x10022 */
	(FP)(_kernel_default_int_handler), /* 0x10023 */
	(FP)(_kernel_default_int_handler), /* 0x10024 */
	(FP)(_kernel_default_int_handler), /* 0x10025 */
	(FP)(_kernel_default_int_handler), /* 0x10026 */
	(FP)(_kernel_default_int_handler), /* 0x10027 */
	(FP)(_kernel_default_int_handler), /* 0x10028 */
	(FP)(_kernel_default_int_handler), /* 0x10029 */
	(FP)(_kernel_default_int_handler), /* 0x1002a */
	(FP)(_kernel_default_int_handler), /* 0x1002b */
	(FP)(_kernel_default_int_handler), /* 0x1002c */
	(FP)(_kernel_default_int_handler), /* 0x1002d */
	(FP)(_kernel_default_int_handler), /* 0x1002e */
	(FP)(_kernel_default_int_handler), /* 0x1002f */
	(FP)(_kernel_default_int_handler), /* 0x10030 */
	(FP)(_kernel_default_int_handler), /* 0x10031 */
	(FP)(_kernel_default_int_handler), /* 0x10032 */
	(FP)(_kernel_default_int_handler), /* 0x10033 */
	(FP)(_kernel_default_int_handler), /* 0x10034 */
	(FP)(_kernel_default_int_handler), /* 0x10035 */
	(FP)(_kernel_default_int_handler), /* 0x10036 */
	(FP)(_kernel_default_int_handler), /* 0x10037 */
	(FP)(_kernel_default_int_handler), /* 0x10038 */
	(FP)(_kernel_default_int_handler), /* 0x10039 */
	(FP)(_kernel_default_int_handler), /* 0x1003a */
	(FP)(_kernel_default_int_handler), /* 0x1003b */
	(FP)(_kernel_default_int_handler), /* 0x1003c */
	(FP)(_kernel_default_int_handler), /* 0x1003d */
	(FP)(_kernel_default_int_handler), /* 0x1003e */
	(FP)(_kernel_default_int_handler), /* 0x1003f */
	(FP)(_kernel_default_int_handler), /* 0x10040 */
	(FP)(_kernel_default_int_handler), /* 0x10041 */
	(FP)(_kernel_default_int_handler), /* 0x10042 */
	(FP)(_kernel_default_int_handler), /* 0x10043 */
	(FP)(_kernel_default_int_handler), /* 0x10044 */
	(FP)(_kernel_default_int_handler), /* 0x10045 */
	(FP)(_kernel_default_int_handler), /* 0x10046 */
	(FP)(_kernel_default_int_handler), /* 0x10047 */
	(FP)(_kernel_default_int_handler), /* 0x10048 */
	(FP)(_kernel_default_int_handler), /* 0x10049 */
	(FP)(_kernel_default_int_handler), /* 0x1004a */
	(FP)(_kernel_default_int_handler), /* 0x1004b */
	(FP)(_kernel_default_int_handler), /* 0x1004c */
	(FP)(_kernel_default_int_handler), /* 0x1004d */
	(FP)(_kernel_default_int_handler), /* 0x1004e */
	(FP)(_kernel_default_int_handler), /* 0x1004f */
	(FP)(_kernel_default_int_handler), /* 0x10050 */
	(FP)(_kernel_default_int_handler), /* 0x10051 */
	(FP)(_kernel_default_int_handler), /* 0x10052 */
	(FP)(_kernel_default_int_handler), /* 0x10053 */
	(FP)(_kernel_default_int_handler), /* 0x10054 */
	(FP)(_kernel_default_int_handler), /* 0x10055 */
	(FP)(_kernel_default_int_handler), /* 0x10056 */
	(FP)(_kernel_default_int_handler), /* 0x10057 */
	(FP)(_kernel_default_int_handler), /* 0x10058 */
	(FP)(_kernel_default_int_handler), /* 0x10059 */
	(FP)(_kernel_default_int_handler), /* 0x1005a */
	(FP)(_kernel_default_int_handler), /* 0x1005b */
	(FP)(_kernel_default_int_handler), /* 0x1005c */
	(FP)(_kernel_inthdr_93), /* 0x1005d */
	(FP)(_kernel_default_int_handler), /* 0x1005e */
	(FP)(_kernel_default_int_handler), /* 0x1005f */
	(FP)(_kernel_default_int_handler), /* 0x10060 */
	(FP)(_kernel_default_int_handler), /* 0x10061 */
	(FP)(_kernel_default_int_handler), /* 0x10062 */
	(FP)(_kernel_default_int_handler), /* 0x10063 */
	(FP)(_kernel_default_int_handler), /* 0x10064 */
	(FP)(_kernel_default_int_handler), /* 0x10065 */
	(FP)(_kernel_default_int_handler), /* 0x10066 */
	(FP)(_kernel_default_int_handler), /* 0x10067 */
	(FP)(_kernel_default_int_handler), /* 0x10068 */
	(FP)(_kernel_default_int_handler), /* 0x10069 */
	(FP)(_kernel_default_int_handler), /* 0x1006a */
	(FP)(_kernel_default_int_handler), /* 0x1006b */
	(FP)(_kernel_default_int_handler), /* 0x1006c */
	(FP)(_kernel_default_int_handler), /* 0x1006d */
	(FP)(_kernel_default_int_handler), /* 0x1006e */
	(FP)(_kernel_default_int_handler), /* 0x1006f */
	(FP)(_kernel_default_int_handler), /* 0x10070 */
	(FP)(_kernel_default_int_handler), /* 0x10071 */
	(FP)(_kernel_default_int_handler), /* 0x10072 */
	(FP)(_kernel_default_int_handler), /* 0x10073 */
	(FP)(_kernel_default_int_handler), /* 0x10074 */
	(FP)(_kernel_default_int_handler), /* 0x10075 */
	(FP)(_kernel_default_int_handler), /* 0x10076 */
	(FP)(_kernel_default_int_handler), /* 0x10077 */
	(FP)(_kernel_default_int_handler), /* 0x10078 */
	(FP)(_kernel_default_int_handler), /* 0x10079 */
	(FP)(_kernel_default_int_handler), /* 0x1007a */
	(FP)(_kernel_default_int_handler), /* 0x1007b */
	(FP)(_kernel_default_int_handler), /* 0x1007c */
	(FP)(_kernel_default_int_handler), /* 0x1007d */
	(FP)(_kernel_default_int_handler), /* 0x1007e */
	(FP)(_kernel_default_int_handler), /* 0x1007f */
};


const FP* const _kernel_p_inh_table[TNUM_PRCID] = {
	_kernel_prc1_inh_table
};


const uint8_t _kernel_prc1_cfgint_table[TNUM_INH] = {
	0U, /* 0x10000 */
	1U, /* 0x10001 */
	0U, /* 0x10002 */
	0U, /* 0x10003 */
	1U, /* 0x10004 */
	0U, /* 0x10005 */
	0U, /* 0x10006 */
	0U, /* 0x10007 */
	0U, /* 0x10008 */
	0U, /* 0x10009 */
	0U, /* 0x1000a */
	0U, /* 0x1000b */
	0U, /* 0x1000c */
	0U, /* 0x1000d */
	0U, /* 0x1000e */
	0U, /* 0x1000f */
	0U, /* 0x10010 */
	0U, /* 0x10011 */
	0U, /* 0x10012 */
	0U, /* 0x10013 */
	0U, /* 0x10014 */
	0U, /* 0x10015 */
	0U, /* 0x10016 */
	0U, /* 0x10017 */
	0U, /* 0x10018 */
	0U, /* 0x10019 */
	0U, /* 0x1001a */
	0U, /* 0x1001b */
	0U, /* 0x1001c */
	0U, /* 0x1001d */
	0U, /* 0x1001e */
	0U, /* 0x1001f */
	0U, /* 0x10020 */
	0U, /* 0x10021 */
	0U, /* 0x10022 */
	0U, /* 0x10023 */
	0U, /* 0x10024 */
	0U, /* 0x10025 */
	0U, /* 0x10026 */
	0U, /* 0x10027 */
	0U, /* 0x10028 */
	0U, /* 0x10029 */
	0U, /* 0x1002a */
	0U, /* 0x1002b */
	0U, /* 0x1002c */
	0U, /* 0x1002d */
	0U, /* 0x1002e */
	0U, /* 0x1002f */
	0U, /* 0x10030 */
	0U, /* 0x10031 */
	0U, /* 0x10032 */
	0U, /* 0x10033 */
	0U, /* 0x10034 */
	0U, /* 0x10035 */
	0U, /* 0x10036 */
	0U, /* 0x10037 */
	0U, /* 0x10038 */
	0U, /* 0x10039 */
	0U, /* 0x1003a */
	0U, /* 0x1003b */
	0U, /* 0x1003c */
	0U, /* 0x1003d */
	0U, /* 0x1003e */
	0U, /* 0x1003f */
	0U, /* 0x10040 */
	0U, /* 0x10041 */
	0U, /* 0x10042 */
	0U, /* 0x10043 */
	0U, /* 0x10044 */
	0U, /* 0x10045 */
	0U, /* 0x10046 */
	0U, /* 0x10047 */
	0U, /* 0x10048 */
	0U, /* 0x10049 */
	0U, /* 0x1004a */
	0U, /* 0x1004b */
	0U, /* 0x1004c */
	0U, /* 0x1004d */
	0U, /* 0x1004e */
	0U, /* 0x1004f */
	0U, /* 0x10050 */
	0U, /* 0x10051 */
	0U, /* 0x10052 */
	0U, /* 0x10053 */
	0U, /* 0x10054 */
	0U, /* 0x10055 */
	0U, /* 0x10056 */
	0U, /* 0x10057 */
	0U, /* 0x10058 */
	0U, /* 0x10059 */
	0U, /* 0x1005a */
	0U, /* 0x1005b */
	0U, /* 0x1005c */
	1U, /* 0x1005d */
	0U, /* 0x1005e */
	0U, /* 0x1005f */
	0U, /* 0x10060 */
	0U, /* 0x10061 */
	0U, /* 0x10062 */
	0U, /* 0x10063 */
	0U, /* 0x10064 */
	0U, /* 0x10065 */
	0U, /* 0x10066 */
	0U, /* 0x10067 */
	0U, /* 0x10068 */
	0U, /* 0x10069 */
	0U, /* 0x1006a */
	0U, /* 0x1006b */
	0U, /* 0x1006c */
	0U, /* 0x1006d */
	0U, /* 0x1006e */
	0U, /* 0x1006f */
	0U, /* 0x10070 */
	0U, /* 0x10071 */
	0U, /* 0x10072 */
	0U, /* 0x10073 */
	0U, /* 0x10074 */
	0U, /* 0x10075 */
	0U, /* 0x10076 */
	0U, /* 0x10077 */
	0U, /* 0x10078 */
	0U, /* 0x10079 */
	0U, /* 0x1007a */
	0U, /* 0x1007b */
	0U, /* 0x1007c */
	0U, /* 0x1007d */
	0U, /* 0x1007e */
	0U, /* 0x1007f */
};


const uint8_t* const _kernel_p_cfgint_table[TNUM_PRCID] = {
	_kernel_prc1_cfgint_table
};

const PRI _kernel_prc1_inh_iipm_table[TNUM_INH] = {
	0, /* 0x10000 */
	INTPRI_TIMER, /* 0x10001 */
	0, /* 0x10002 */
	0, /* 0x10003 */
	INTPRI_IPI_DIS_PRC1, /* 0x10004 */
	0, /* 0x10005 */
	0, /* 0x10006 */
	0, /* 0x10007 */
	0, /* 0x10008 */
	0, /* 0x10009 */
	0, /* 0x1000a */
	0, /* 0x1000b */
	0, /* 0x1000c */
	0, /* 0x1000d */
	0, /* 0x1000e */
	0, /* 0x1000f */
	0, /* 0x10010 */
	0, /* 0x10011 */
	0, /* 0x10012 */
	0, /* 0x10013 */
	0, /* 0x10014 */
	0, /* 0x10015 */
	0, /* 0x10016 */
	0, /* 0x10017 */
	0, /* 0x10018 */
	0, /* 0x10019 */
	0, /* 0x1001a */
	0, /* 0x1001b */
	0, /* 0x1001c */
	0, /* 0x1001d */
	0, /* 0x1001e */
	0, /* 0x1001f */
	0, /* 0x10020 */
	0, /* 0x10021 */
	0, /* 0x10022 */
	0, /* 0x10023 */
	0, /* 0x10024 */
	0, /* 0x10025 */
	0, /* 0x10026 */
	0, /* 0x10027 */
	0, /* 0x10028 */
	0, /* 0x10029 */
	0, /* 0x1002a */
	0, /* 0x1002b */
	0, /* 0x1002c */
	0, /* 0x1002d */
	0, /* 0x1002e */
	0, /* 0x1002f */
	0, /* 0x10030 */
	0, /* 0x10031 */
	0, /* 0x10032 */
	0, /* 0x10033 */
	0, /* 0x10034 */
	0, /* 0x10035 */
	0, /* 0x10036 */
	0, /* 0x10037 */
	0, /* 0x10038 */
	0, /* 0x10039 */
	0, /* 0x1003a */
	0, /* 0x1003b */
	0, /* 0x1003c */
	0, /* 0x1003d */
	0, /* 0x1003e */
	0, /* 0x1003f */
	0, /* 0x10040 */
	0, /* 0x10041 */
	0, /* 0x10042 */
	0, /* 0x10043 */
	0, /* 0x10044 */
	0, /* 0x10045 */
	0, /* 0x10046 */
	0, /* 0x10047 */
	0, /* 0x10048 */
	0, /* 0x10049 */
	0, /* 0x1004a */
	0, /* 0x1004b */
	0, /* 0x1004c */
	0, /* 0x1004d */
	0, /* 0x1004e */
	0, /* 0x1004f */
	0, /* 0x10050 */
	0, /* 0x10051 */
	0, /* 0x10052 */
	0, /* 0x10053 */
	0, /* 0x10054 */
	0, /* 0x10055 */
	0, /* 0x10056 */
	0, /* 0x10057 */
	0, /* 0x10058 */
	0, /* 0x10059 */
	0, /* 0x1005a */
	0, /* 0x1005b */
	0, /* 0x1005c */
	INTPRI_SIO, /* 0x1005d */
	0, /* 0x1005e */
	0, /* 0x1005f */
	0, /* 0x10060 */
	0, /* 0x10061 */
	0, /* 0x10062 */
	0, /* 0x10063 */
	0, /* 0x10064 */
	0, /* 0x10065 */
	0, /* 0x10066 */
	0, /* 0x10067 */
	0, /* 0x10068 */
	0, /* 0x10069 */
	0, /* 0x1006a */
	0, /* 0x1006b */
	0, /* 0x1006c */
	0, /* 0x1006d */
	0, /* 0x1006e */
	0, /* 0x1006f */
	0, /* 0x10070 */
	0, /* 0x10071 */
	0, /* 0x10072 */
	0, /* 0x10073 */
	0, /* 0x10074 */
	0, /* 0x10075 */
	0, /* 0x10076 */
	0, /* 0x10077 */
	0, /* 0x10078 */
	0, /* 0x10079 */
	0, /* 0x1007a */
	0, /* 0x1007b */
	0, /* 0x1007c */
	0, /* 0x1007d */
	0, /* 0x1007e */
	0, /* 0x1007f */
};


const PRI* const _kernel_p_inh_iipm_table[TNUM_PRCID] = {
	_kernel_prc1_inh_iipm_table
};

const uint32_t _kernel_prc1_iipm_mask_table[(TNUM_INTPRI + 1) * 4] = {
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -31 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -30 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -29 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -28 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -27 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -26 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -25 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -24 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -23 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -22 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -21 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -20 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -19 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -18 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -17 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -16 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -15 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -14 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -13 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -12 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -11 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -10 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -9 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -8 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -7 */
	0x00000012, 0x00000000, 0x20000000, 0x00000000, /* Priority -6 */
	0x00000010, 0x00000000, 0x20000000, 0x00000000, /* Priority -5 */
	0x00000010, 0x00000000, 0x20000000, 0x00000000, /* Priority -4 */
	0x00000010, 0x00000000, 0x20000000, 0x00000000, /* Priority -3 */
	0x00000010, 0x00000000, 0x20000000, 0x00000000, /* Priority -2 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* Priority -1 */
	0x00000000, 0x00000000, 0x00000000, 0x00000000, /* Priority 0 */
};


const uint32_t* const _kernel_p_iipm_mask_table[TNUM_PRCID] = {
	_kernel_prc1_iipm_mask_table
};

