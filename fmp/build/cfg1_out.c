/* cfg1_out.c */
#define TOPPERS_CFG1_OUT  1
#include "kernel/kernel_int.h"
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


#ifdef INT64_MAX
  typedef int64_t signed_t;
  typedef uint64_t unsigned_t;
#else
  typedef int32_t signed_t;
  typedef uint32_t unsigned_t;
#endif

#include "target_cfg1_out.h"

const uint32_t TOPPERS_cfg_magic_number = 0x12345678;
const uint32_t TOPPERS_cfg_sizeof_signed_t = sizeof(signed_t);
const uint32_t TOPPERS_cfg_sizeof_pointer = sizeof(const volatile void*);
const unsigned_t TOPPERS_cfg_CHAR_BIT = ((unsigned char)~0u == 0xff ? 8 : 16);
const unsigned_t TOPPERS_cfg_CHAR_MAX = ((char)-1 < 0 ? (char)((unsigned char)~0u >> 1) : (unsigned char)~0u);
const unsigned_t TOPPERS_cfg_CHAR_MIN = (unsigned_t)((char)-1 < 0 ? -((unsigned char)~0u >> 1) - 1 : 0);
const unsigned_t TOPPERS_cfg_SCHAR_MAX = (signed char)((unsigned char)~0u >> 1);
const unsigned_t TOPPERS_cfg_SHRT_MAX = (short)((unsigned short)~0u >> 1);
const unsigned_t TOPPERS_cfg_INT_MAX = (int)(~0u >> 1);
const unsigned_t TOPPERS_cfg_LONG_MAX = (long)(~0ul >> 1);

const unsigned_t TOPPERS_cfg_SIL_ENDIAN_BIG = 
#if defined(SIL_ENDIAN_BIG) 
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_SIL_ENDIAN_LITTLE = 
#if defined(SIL_ENDIAN_LITTLE) 
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TA_NULL = ( unsigned_t )TA_NULL;
const unsigned_t TOPPERS_cfg_TA_ACT = ( unsigned_t )TA_ACT;
const unsigned_t TOPPERS_cfg_TA_TPRI = ( unsigned_t )TA_TPRI;
const unsigned_t TOPPERS_cfg_TA_MPRI = ( unsigned_t )TA_MPRI;
const unsigned_t TOPPERS_cfg_TA_WMUL = ( unsigned_t )TA_WMUL;
const unsigned_t TOPPERS_cfg_TA_CLR = ( unsigned_t )TA_CLR;
const unsigned_t TOPPERS_cfg_TA_STA = ( unsigned_t )TA_STA;
const unsigned_t TOPPERS_cfg_TA_NONKERNEL = ( unsigned_t )TA_NONKERNEL;
const unsigned_t TOPPERS_cfg_TA_ENAINT = ( unsigned_t )TA_ENAINT;
const unsigned_t TOPPERS_cfg_TA_EDGE = ( unsigned_t )TA_EDGE;
const signed_t TOPPERS_cfg_TMIN_TPRI = ( signed_t )TMIN_TPRI;
const signed_t TOPPERS_cfg_TMAX_TPRI = ( signed_t )TMAX_TPRI;
const signed_t TOPPERS_cfg_TMIN_DPRI = ( signed_t )TMIN_DPRI;
const signed_t TOPPERS_cfg_TMAX_DPRI = ( signed_t )TMAX_DPRI;
const signed_t TOPPERS_cfg_TMIN_MPRI = ( signed_t )TMIN_MPRI;
const signed_t TOPPERS_cfg_TMAX_MPRI = ( signed_t )TMAX_MPRI;
const signed_t TOPPERS_cfg_TMIN_ISRPRI = ( signed_t )TMIN_ISRPRI;
const signed_t TOPPERS_cfg_TMAX_ISRPRI = ( signed_t )TMAX_ISRPRI;
const unsigned_t TOPPERS_cfg_TBIT_TEXPTN = ( unsigned_t )TBIT_TEXPTN;
const unsigned_t TOPPERS_cfg_TBIT_FLGPTN = ( unsigned_t )TBIT_FLGPTN;
const unsigned_t TOPPERS_cfg_TMAX_MAXSEM = ( unsigned_t )TMAX_MAXSEM;
const unsigned_t TOPPERS_cfg_TMAX_RELTIM = ( unsigned_t )TMAX_RELTIM;
const signed_t TOPPERS_cfg_TMIN_INTPRI = ( signed_t )TMIN_INTPRI;
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_INTERRUPT = 
#if defined(OMIT_INITIALIZE_INTERRUPT)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_OMIT_INITIALIZE_EXCEPTION = 
#if defined(OMIT_INITIALIZE_EXCEPTION)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_USE_TSKINICTXB = 
#if defined(USE_TSKINICTXB)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TNUM_PRCID = ( unsigned_t )TNUM_PRCID;
const unsigned_t TOPPERS_cfg_TTYPE_KLOCK = ( unsigned_t )TTYPE_KLOCK;
const unsigned_t TOPPERS_cfg_G_KLOCK = ( unsigned_t )G_KLOCK;
const unsigned_t TOPPERS_cfg_P_KLOCK = ( unsigned_t )P_KLOCK;
const unsigned_t TOPPERS_cfg_F_KLOCK = ( unsigned_t )F_KLOCK;
const unsigned_t TOPPERS_cfg_TOPPERS_SYSTIM_LOCAL = 
#if defined(TOPPERS_SYSTIM_LOCAL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SYSTIM_GLOBAL = 
#if defined(TOPPERS_SYSTIM_GLOBAL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SYSTIM_PRCID = ( unsigned_t )TOPPERS_SYSTIM_PRCID;
const unsigned_t TOPPERS_cfg_TTYPE_SPN = ( unsigned_t )TTYPE_SPN;
const unsigned_t TOPPERS_cfg_NATIVE_SPN = ( unsigned_t )NATIVE_SPN;
const unsigned_t TOPPERS_cfg_EMULATE_SPN = ( unsigned_t )EMULATE_SPN;
const signed_t TOPPERS_cfg_TMAX_NATIVE_SPN = ( signed_t )TMAX_NATIVE_SPN;
const unsigned_t TOPPERS_cfg_TARGET_TSKATR = 
#if defined(TARGET_TSKATR)
(TARGET_TSKATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_INTATR = 
#if defined(TARGET_INTATR)
(TARGET_INTATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_INHATR = 
#if defined(TARGET_INHATR)
(TARGET_INHATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_ISRATR = 
#if defined(TARGET_ISRATR)
(TARGET_ISRATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_EXCATR = 
#if defined(TARGET_EXCATR)
(TARGET_EXCATR);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_STKSZ = 
#if defined(TARGET_MIN_STKSZ)
(TARGET_MIN_STKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TARGET_MIN_ISTKSZ = 
#if defined(TARGET_MIN_ISTKSZ)
(TARGET_MIN_ISTKSZ);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STKSZ_ALIGN = 
#if defined(CHECK_STKSZ_ALIGN)
(CHECK_STKSZ_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_FUNC_ALIGN = 
#if defined(CHECK_FUNC_ALIGN)
(CHECK_FUNC_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_FUNC_NONNULL = 
#if defined(CHECK_FUNC_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STACK_ALIGN = 
#if defined(CHECK_STACK_ALIGN)
(CHECK_STACK_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_STACK_NONNULL = 
#if defined(CHECK_STACK_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MPF_ALIGN = 
#if defined(CHECK_MPF_ALIGN)
(CHECK_MPF_ALIGN);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_CHECK_MPF_NONNULL = 
#if defined(CHECK_MPF_NONNULL)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_ID = ( unsigned_t )sizeof(ID);
const unsigned_t TOPPERS_cfg_sizeof_uint_t = ( unsigned_t )sizeof(uint_t);
const unsigned_t TOPPERS_cfg_sizeof_SIZE = ( unsigned_t )sizeof(SIZE);
const unsigned_t TOPPERS_cfg_sizeof_ATR = ( unsigned_t )sizeof(ATR);
const unsigned_t TOPPERS_cfg_sizeof_PRI = ( unsigned_t )sizeof(PRI);
const unsigned_t TOPPERS_cfg_sizeof_void_ptr = ( unsigned_t )sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_VP = ( unsigned_t )sizeof(void*);
const unsigned_t TOPPERS_cfg_sizeof_intptr_t = ( unsigned_t )sizeof(intptr_t);
const unsigned_t TOPPERS_cfg_sizeof_FP = ( unsigned_t )sizeof(FP);
const unsigned_t TOPPERS_cfg_sizeof_INHNO = ( unsigned_t )sizeof(INHNO);
const unsigned_t TOPPERS_cfg_sizeof_INTNO = ( unsigned_t )sizeof(INTNO);
const unsigned_t TOPPERS_cfg_sizeof_EXCNO = ( unsigned_t )sizeof(EXCNO);
const unsigned_t TOPPERS_cfg_sizeof_TINIB = ( unsigned_t )sizeof(TINIB);
const unsigned_t TOPPERS_cfg_sizeof_STK_T_prt = ( unsigned_t )sizeof(STK_T*);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_tskatr = ( unsigned_t )offsetof(TINIB,tskatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_exinf = ( unsigned_t )offsetof(TINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_task = ( unsigned_t )offsetof(TINIB,task);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_ipriority = ( unsigned_t )offsetof(TINIB,ipriority);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stksz = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,stksz));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_stk = 
#if !defined(USE_TSKINICTXB)
(offsetof(TINIB,stk));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texatr = ( unsigned_t )offsetof(TINIB,texatr);
const unsigned_t TOPPERS_cfg_offsetof_TINIB_texrtn = ( unsigned_t )offsetof(TINIB,texrtn);
const unsigned_t TOPPERS_cfg_sizeof_SEMINIB = ( unsigned_t )sizeof(SEMINIB);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_sematr = ( unsigned_t )offsetof(SEMINIB,sematr);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_isemcnt = ( unsigned_t )offsetof(SEMINIB,isemcnt);
const unsigned_t TOPPERS_cfg_offsetof_SEMINIB_maxsem = ( unsigned_t )offsetof(SEMINIB,maxsem);
const unsigned_t TOPPERS_cfg_sizeof_FLGPTN = ( unsigned_t )sizeof(FLGPTN);
const unsigned_t TOPPERS_cfg_sizeof_FLGINIB = ( unsigned_t )sizeof(FLGINIB);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_flgatr = ( unsigned_t )offsetof(FLGINIB,flgatr);
const unsigned_t TOPPERS_cfg_offsetof_FLGINIB_iflgptn = ( unsigned_t )offsetof(FLGINIB,iflgptn);
const unsigned_t TOPPERS_cfg_sizeof_DTQINIB = ( unsigned_t )sizeof(DTQINIB);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqatr = ( unsigned_t )offsetof(DTQINIB,dtqatr);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_dtqcnt = ( unsigned_t )offsetof(DTQINIB,dtqcnt);
const unsigned_t TOPPERS_cfg_offsetof_DTQINIB_p_dtqmb = ( unsigned_t )offsetof(DTQINIB,p_dtqmb);
const unsigned_t TOPPERS_cfg_sizeof_PDQINIB = ( unsigned_t )sizeof(PDQINIB);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqatr = ( unsigned_t )offsetof(PDQINIB,pdqatr);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_pdqcnt = ( unsigned_t )offsetof(PDQINIB,pdqcnt);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_maxdpri = ( unsigned_t )offsetof(PDQINIB,maxdpri);
const unsigned_t TOPPERS_cfg_offsetof_PDQINIB_p_pdqmb = ( unsigned_t )offsetof(PDQINIB,p_pdqmb);
const unsigned_t TOPPERS_cfg_sizeof_MBXINIB = ( unsigned_t )sizeof(MBXINIB);
const unsigned_t TOPPERS_cfg_offsetof_MBXINIB_mbxatr = ( unsigned_t )offsetof(MBXINIB,mbxatr);
const unsigned_t TOPPERS_cfg_offsetof_MBXINIB_maxmpri = ( unsigned_t )offsetof(MBXINIB,maxmpri);
const unsigned_t TOPPERS_cfg_sizeof_MPFINIB = ( unsigned_t )sizeof(MPFINIB);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpfatr = ( unsigned_t )offsetof(MPFINIB,mpfatr);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blkcnt = ( unsigned_t )offsetof(MPFINIB,blkcnt);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_blksz = ( unsigned_t )offsetof(MPFINIB,blksz);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_mpf = ( unsigned_t )offsetof(MPFINIB,mpf);
const unsigned_t TOPPERS_cfg_offsetof_MPFINIB_p_mpfmb = ( unsigned_t )offsetof(MPFINIB,p_mpfmb);
const unsigned_t TOPPERS_cfg_sizeof_CYCINIB = ( unsigned_t )sizeof(CYCINIB);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycatr = ( unsigned_t )offsetof(CYCINIB,cycatr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_exinf = ( unsigned_t )offsetof(CYCINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cychdr = ( unsigned_t )offsetof(CYCINIB,cychdr);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cyctim = ( unsigned_t )offsetof(CYCINIB,cyctim);
const unsigned_t TOPPERS_cfg_offsetof_CYCINIB_cycphs = ( unsigned_t )offsetof(CYCINIB,cycphs);
const unsigned_t TOPPERS_cfg_sizeof_ALMINIB = ( unsigned_t )sizeof(ALMINIB);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almatr = ( unsigned_t )offsetof(ALMINIB,almatr);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_exinf = ( unsigned_t )offsetof(ALMINIB,exinf);
const unsigned_t TOPPERS_cfg_offsetof_ALMINIB_almhdr = ( unsigned_t )offsetof(ALMINIB,almhdr);
const unsigned_t TOPPERS_cfg_sizeof_INHINIB = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(sizeof(INHINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhno = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,inhno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_inhatr = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,inhatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INHINIB_int_entry = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INHINIB,int_entry));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_INTINIB = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(sizeof(INTINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intno = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intatr = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_INTINIB_intpri = 
#if !defined(OMIT_INITIALIZE_INTERRUPT)
(offsetof(INTINIB,intpri));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_sizeof_EXCINIB = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(sizeof(EXCINIB));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excno = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,excno));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_excatr = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,excatr));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offset_EXCINIB_exc_entry = 
#if !defined(OMIT_INITIALIZE_EXCEPTION)
(offsetof(EXCINIB,exc_entry));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TMIN_INTNO = ( unsigned_t )TMIN_INTNO;
const unsigned_t TOPPERS_cfg_TMAX_INTNO = ( unsigned_t )TMAX_INTNO;
const unsigned_t TOPPERS_cfg_TMIN_INHNO = ( unsigned_t )TMIN_INHNO;
const unsigned_t TOPPERS_cfg_TMAX_INHNO = ( unsigned_t )TMAX_INHNO;
const unsigned_t TOPPERS_cfg_TNUM_INH = ( unsigned_t )TNUM_INH;
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_firstlock = 
#if (TTYPE_KLOCK != G_KLOCK)
(offsetof(PCB,p_firstlock));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_secondlock = 
#if (TTYPE_KLOCK != G_KLOCK)
(offsetof(PCB,p_secondlock));
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_offsetof_PCB_locspnid = ( unsigned_t )offsetof(PCB,locspnid);
const unsigned_t TOPPERS_cfg_offsetof_PCB_excpt_nest_count = ( unsigned_t )offsetof(PCB,target_pcb.excpt_nest_count);
const unsigned_t TOPPERS_cfg_offsetof_PCB_istkpt = ( unsigned_t )offsetof(PCB,target_pcb.istkpt);
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_exch_tbl = ( unsigned_t )offsetof(PCB,target_pcb.p_exch_tbl);
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_inh_tbl = ( unsigned_t )offsetof(PCB,target_pcb.p_inh_tbl);
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_inh_iipm_tbl = ( unsigned_t )offsetof(PCB,target_pcb.p_inh_iipm_tbl);
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_iipm_mask_tbl = ( unsigned_t )offsetof(PCB,target_pcb.p_iipm_mask_tbl);
const unsigned_t TOPPERS_cfg_offsetof_PCB_iipm = ( unsigned_t )offsetof(PCB,target_pcb.iipm);
const unsigned_t TOPPERS_cfg_TOPPERS_SAFEG_SECURE = 
#if defined(TOPPERS_SAFEG_SECURE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TOPPERS_SAFEG_NONSECURE = 
#if defined(TOPPERS_SAFEG_NONSECURE)
(1);
#else
(0);
#endif
const unsigned_t TOPPERS_cfg_TMIN_EXCH = ( unsigned_t )TMIN_EXCH;
const unsigned_t TOPPERS_cfg_TMAX_EXCH = ( unsigned_t )TMAX_EXCH;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SP0_SYNC = ( unsigned_t )EXCH_NO_CUR_SP0_SYNC;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SP0_IRQ = ( unsigned_t )EXCH_NO_CUR_SP0_IRQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SP0_FIQ = ( unsigned_t )EXCH_NO_CUR_SP0_FIQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SP0_SERR = ( unsigned_t )EXCH_NO_CUR_SP0_SERR;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SPX_SYNC = ( unsigned_t )EXCH_NO_CUR_SPX_SYNC;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SPX_IRQ = ( unsigned_t )EXCH_NO_CUR_SPX_IRQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SPX_FIQ = ( unsigned_t )EXCH_NO_CUR_SPX_FIQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_CUR_SPX_SERR = ( unsigned_t )EXCH_NO_CUR_SPX_SERR;
const unsigned_t TOPPERS_cfg_EXCH_NO_L64_SYNC = ( unsigned_t )EXCH_NO_L64_SYNC;
const unsigned_t TOPPERS_cfg_EXCH_NO_L64_IRQ = ( unsigned_t )EXCH_NO_L64_IRQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_L64_FIQ = ( unsigned_t )EXCH_NO_L64_FIQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_L64_SERR = ( unsigned_t )EXCH_NO_L64_SERR;
const unsigned_t TOPPERS_cfg_EXCH_NO_L32_SYNC = ( unsigned_t )EXCH_NO_L32_SYNC;
const unsigned_t TOPPERS_cfg_EXCH_NO_L32_IRQ = ( unsigned_t )EXCH_NO_L32_IRQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_L32_FIQ = ( unsigned_t )EXCH_NO_L32_FIQ;
const unsigned_t TOPPERS_cfg_EXCH_NO_L32_SERR = ( unsigned_t )EXCH_NO_L32_SERR;
const unsigned_t TOPPERS_cfg_sizeof_TCB = ( unsigned_t )sizeof(TCB);
const unsigned_t TOPPERS_cfg_offsetof_TCB_p_tinib = ( unsigned_t )offsetof(TCB,p_tinib);
const unsigned_t TOPPERS_cfg_offsetof_TCB_texptn = ( unsigned_t )offsetof(TCB,texptn);
const unsigned_t TOPPERS_cfg_offsetof_TCB_sp = ( unsigned_t )offsetof(TCB,tskctxb.sp);
const unsigned_t TOPPERS_cfg_offsetof_TCB_pc = ( unsigned_t )offsetof(TCB,tskctxb.pc);
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_runtsk = ( unsigned_t )offsetof(PCB,p_runtsk);
const unsigned_t TOPPERS_cfg_offsetof_PCB_p_schedtsk = ( unsigned_t )offsetof(PCB,p_schedtsk);
const unsigned_t TOPPERS_cfg_offsetof_PCB_reqflg = ( unsigned_t )offsetof(PCB,reqflg);
const unsigned_t TOPPERS_cfg_offsetof_PCB_ipmflg = ( unsigned_t )offsetof(PCB,ipmflg);
const unsigned_t TOPPERS_cfg_offsetof_PCB_disdsp = ( unsigned_t )offsetof(PCB,disdsp);
const unsigned_t TOPPERS_cfg_offsetof_PCB_dspflg = ( unsigned_t )offsetof(PCB,dspflg);
const unsigned_t TOPPERS_cfg_offsetof_EXC_FRAME_cpsr = ( unsigned_t )offsetof(exc_frame_t,cpsr);
const unsigned_t TOPPERS_cfg_sizeof_EXC_FRAME = ( unsigned_t )sizeof(exc_frame_t);


/* #include "sample1.h" */
/* #include "target_timer.h" */

#ifdef TOPPERS_SYSTIM_LOCAL

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 13 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_0 = TCL_1;
#line 14 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_0 = 0;
const unsigned_t TOPPERS_cfg_valueof_iniatr_0 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_1 = TCL_1;
#line 15 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_1 = 1;
const unsigned_t TOPPERS_cfg_valueof_teratr_1 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_2 = TCL_1;
#line 16 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_2 = 2;
const unsigned_t TOPPERS_cfg_valueof_inhno_2 = ( unsigned_t )( INHNO_TIMER_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_2 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_3 = TCL_1;
#line 17 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_3 = 3;
const unsigned_t TOPPERS_cfg_valueof_intno_3 = ( unsigned_t )( INTNO_TIMER_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_3 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_3 = ( signed_t )( INTPRI_TIMER ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 18 "../arch/arm64_gcc/common/core_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 21 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_4 = TCL_2;
#line 22 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_4 = 4;
const unsigned_t TOPPERS_cfg_valueof_iniatr_4 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_5 = TCL_2;
#line 23 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_5 = 5;
const unsigned_t TOPPERS_cfg_valueof_teratr_5 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_6 = TCL_2;
#line 24 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_6 = 6;
const unsigned_t TOPPERS_cfg_valueof_inhno_6 = ( unsigned_t )( INHNO_TIMER_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_6 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_7 = TCL_2;
#line 25 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_7 = 7;
const unsigned_t TOPPERS_cfg_valueof_intno_7 = ( unsigned_t )( INTNO_TIMER_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_7 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_7 = ( signed_t )( INTPRI_TIMER ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 26 "../arch/arm64_gcc/common/core_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 30 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_8 = TCL_3;
#line 31 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_8 = 8;
const unsigned_t TOPPERS_cfg_valueof_iniatr_8 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_9 = TCL_3;
#line 32 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_9 = 9;
const unsigned_t TOPPERS_cfg_valueof_teratr_9 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_10 = TCL_3;
#line 33 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_10 = 10;
const unsigned_t TOPPERS_cfg_valueof_inhno_10 = ( unsigned_t )( INHNO_TIMER_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_10 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_11 = TCL_3;
#line 34 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_11 = 11;
const unsigned_t TOPPERS_cfg_valueof_intno_11 = ( unsigned_t )( INTNO_TIMER_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_11 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_11 = ( signed_t )( INTPRI_TIMER ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 35 "../arch/arm64_gcc/common/core_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 39 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_12 = TCL_4;
#line 40 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_12 = 12;
const unsigned_t TOPPERS_cfg_valueof_iniatr_12 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_13 = TCL_4;
#line 41 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_13 = 13;
const unsigned_t TOPPERS_cfg_valueof_teratr_13 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_14 = TCL_4;
#line 42 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_14 = 14;
const unsigned_t TOPPERS_cfg_valueof_inhno_14 = ( unsigned_t )( INHNO_TIMER_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_14 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_15 = TCL_4;
#line 43 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_15 = 15;
const unsigned_t TOPPERS_cfg_valueof_intno_15 = ( unsigned_t )( INTNO_TIMER_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_15 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_15 = ( signed_t )( INTPRI_TIMER ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 44 "../arch/arm64_gcc/common/core_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#else 

#ifndef TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED 1

#line 49 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000d612f_14 = TCL_SYSTIM_PRC;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000d612f_14
const unsigned_t TOPPERS_cfg_valueof_CLASS_16 = TCL_SYSTIM_PRC;
#line 50 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_16 = 16;
const unsigned_t TOPPERS_cfg_valueof_iniatr_16 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_17 = TCL_SYSTIM_PRC;
#line 51 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_17 = 17;
const unsigned_t TOPPERS_cfg_valueof_teratr_17 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_18 = TCL_SYSTIM_PRC;
#line 52 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_18 = 18;
const unsigned_t TOPPERS_cfg_valueof_inhno_18 = ( unsigned_t )( INHNO_TIMER_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_18 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_19 = TCL_SYSTIM_PRC;
#line 53 "../arch/arm64_gcc/common/core_timer.cfg"
const unsigned_t TOPPERS_cfg_static_api_19 = 19;
const unsigned_t TOPPERS_cfg_valueof_intno_19 = ( unsigned_t )( INTNO_TIMER_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_19 = ( unsigned_t )( TA_ENAINT|INTATR_TIMER ); const signed_t TOPPERS_cfg_valueof_intpri_19 = ( signed_t )( INTPRI_TIMER ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000d612f_14

#line 54 "../arch/arm64_gcc/common/core_timer.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000d612f_14


#endif 
/* #include "syssvc/syslog.h" */

#if TNUM_PRCID >= 1

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 12 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_20 = TCL_1;
#line 13 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_20 = 20;
const unsigned_t TOPPERS_cfg_valueof_iniatr_20 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 14 "../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 18 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_21 = TCL_2;
#line 19 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_21 = 21;
const unsigned_t TOPPERS_cfg_valueof_iniatr_21 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 20 "../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 24 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_22 = TCL_3;
#line 25 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_22 = 22;
const unsigned_t TOPPERS_cfg_valueof_iniatr_22 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 26 "../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 30 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_23 = TCL_4;
#line 31 "../syssvc/syslog.cfg"
const unsigned_t TOPPERS_cfg_static_api_23 = 23;
const unsigned_t TOPPERS_cfg_valueof_iniatr_23 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 32 "../syssvc/syslog.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 
/* #include "syssvc/banner.h" */

#if TNUM_PRCID >= 1

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 12 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_24 = TCL_1;
#line 13 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_24 = 24;
const unsigned_t TOPPERS_cfg_valueof_iniatr_24 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_25 = TCL_1;
#line 14 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_25 = 25;
const unsigned_t TOPPERS_cfg_valueof_iniatr_25 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 15 "../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 19 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_26 = TCL_2;
#line 20 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_26 = 26;
const unsigned_t TOPPERS_cfg_valueof_iniatr_26 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 21 "../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 25 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_27 = TCL_3;
#line 26 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_27 = 27;
const unsigned_t TOPPERS_cfg_valueof_iniatr_27 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 27 "../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 31 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_28 = TCL_4;
#line 32 "../syssvc/banner.cfg"
const unsigned_t TOPPERS_cfg_static_api_28 = 28;
const unsigned_t TOPPERS_cfg_valueof_iniatr_28 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 33 "../syssvc/banner.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 
/* #include "target_syssvc.h" */
/* #include "target_syssvc.h" */
/* #include "target_serial.h" */

#ifndef TOPPERS_cfg_valueof_0T_000000000000da91_10_DEFINED
#define TOPPERS_cfg_valueof_0T_000000000000da91_10_DEFINED 1

#line 12 "../arch/arm64_gcc/bcm283x/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_000000000000da91_10 = TCL_1_ONLY;

#endif
#define TOPPERS_cfg_inside_of_0T_000000000000da91_10
const unsigned_t TOPPERS_cfg_valueof_CLASS_29 = TCL_1_ONLY;
#line 13 "../arch/arm64_gcc/bcm283x/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_29 = 29;
const unsigned_t TOPPERS_cfg_valueof_iniatr_29 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_30 = TCL_1_ONLY;
#line 15 "../arch/arm64_gcc/bcm283x/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_30 = 30;
const unsigned_t TOPPERS_cfg_valueof_isratr_30 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_intno_30 = ( unsigned_t )( INTNO_SIO ); const signed_t TOPPERS_cfg_valueof_isrpri_30 = ( signed_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_31 = TCL_1_ONLY;
#line 16 "../arch/arm64_gcc/bcm283x/chip_serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_31 = 31;
const unsigned_t TOPPERS_cfg_valueof_intno_31 = ( unsigned_t )( INTNO_SIO ); const unsigned_t TOPPERS_cfg_valueof_intatr_31 = ( unsigned_t )( INTATR_SIO ); const signed_t TOPPERS_cfg_valueof_intpri_31 = ( signed_t )( INTPRI_SIO ); 
#ifndef TOPPERS_cfg_inside_of_0T_000000000000da91_10

#line 17 "../arch/arm64_gcc/bcm283x/chip_serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_000000000000da91_10

/* #include "syssvc/serial.h" */

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 14 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_32 = TCL_1;
#line 15 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_32 = 32;
const unsigned_t TOPPERS_cfg_valueof_iniatr_32 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_33 = TCL_1;
#line 16 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_33 = 33;
#define SERIAL_RCV_SEM1	(<>)

#line 16 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_33 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_33 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_33 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_34 = TCL_1;
#line 17 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_34 = 34;
#define SERIAL_SND_SEM1	(<>)

#line 17 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_34 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_34 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_34 = ( unsigned_t )( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 18 "../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PORT >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 20 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_35 = TCL_2;
#line 21 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_35 = 35;
const unsigned_t TOPPERS_cfg_valueof_iniatr_35 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_36 = TCL_2;
#line 22 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_36 = 36;
#define SERIAL_RCV_SEM2	(<>)

#line 22 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_36 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_36 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_36 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_37 = TCL_2;
#line 23 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_37 = 37;
#define SERIAL_SND_SEM2	(<>)

#line 23 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_37 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_37 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_37 = ( unsigned_t )( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 24 "../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PORT >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 28 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_38 = TCL_3;
#line 29 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_38 = 38;
const unsigned_t TOPPERS_cfg_valueof_iniatr_38 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_39 = TCL_3;
#line 30 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_39 = 39;
#define SERIAL_RCV_SEM3	(<>)

#line 30 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_39 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_39 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_39 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_40 = TCL_3;
#line 31 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_40 = 40;
#define SERIAL_SND_SEM3	(<>)

#line 31 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_40 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_40 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_40 = ( unsigned_t )( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 32 "../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PORT >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 36 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_41 = TCL_4;
#line 37 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_41 = 41;
const unsigned_t TOPPERS_cfg_valueof_iniatr_41 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_42 = TCL_4;
#line 38 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_42 = 42;
#define SERIAL_RCV_SEM4	(<>)

#line 38 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_42 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_42 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_42 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_43 = TCL_4;
#line 39 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_static_api_43 = 43;
#define SERIAL_SND_SEM4	(<>)

#line 39 "../syssvc/serial.cfg"
const unsigned_t TOPPERS_cfg_valueof_sematr_43 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_isemcnt_43 = ( unsigned_t )( 1 ); const unsigned_t TOPPERS_cfg_valueof_maxsem_43 = ( unsigned_t )( 1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 40 "../syssvc/serial.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 
/* #include "syssvc/logtask.h" */

#ifdef G_SYSLOG

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 13 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_44 = TCL_1;
#line 14 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_44 = 44;
#define LOGTASK1	(<>)

#line 14 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_44 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_44 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_44 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_45 = TCL_1;
#line 16 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_45 = 45;
const unsigned_t TOPPERS_cfg_valueof_teratr_45 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 17 "../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#else 

#if TNUM_PRCID >= 1

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 22 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_46 = TCL_1;
#line 23 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_46 = 46;
#define LOGTASK1	(<>)

#line 23 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_46 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_46 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_46 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_47 = TCL_1;
#line 25 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_47 = 47;
const unsigned_t TOPPERS_cfg_valueof_teratr_47 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 26 "../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 31 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_48 = TCL_2;
#line 32 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_48 = 48;
#define LOGTASK2	(<>)

#line 32 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_48 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_48 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_48 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_49 = TCL_2;
#line 34 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_49 = 49;
const unsigned_t TOPPERS_cfg_valueof_teratr_49 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 35 "../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 39 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_50 = TCL_3;
#line 40 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_50 = 50;
#define LOGTASK3	(<>)

#line 40 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_50 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_50 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_50 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_51 = TCL_3;
#line 42 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_51 = 51;
const unsigned_t TOPPERS_cfg_valueof_teratr_51 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 43 "../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 47 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_52 = TCL_4;
#line 48 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_52 = 52;
#define LOGTASK4	(<>)

#line 48 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_52 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_52 = ( signed_t )( LOGTASK_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_52 = ( unsigned_t )( LOGTASK_STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_53 = TCL_4;
#line 50 "../syssvc/logtask.cfg"
const unsigned_t TOPPERS_cfg_static_api_53 = 53;
const unsigned_t TOPPERS_cfg_valueof_teratr_53 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 51 "../syssvc/logtask.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#endif 
/* #include "target_ipi.h" */

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 10 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_54 = TCL_1;
#line 11 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_54 = 54;
const unsigned_t TOPPERS_cfg_valueof_inhno_54 = ( unsigned_t )( INHNO_IPI_DIS_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_54 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_55 = TCL_1;
#line 12 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_55 = 55;
const unsigned_t TOPPERS_cfg_valueof_intno_55 = ( unsigned_t )( INTNO_IPI_DIS_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_55 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_55 = ( signed_t )( INTPRI_IPI_DIS_PRC1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 13 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 16 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_56 = TCL_2;
#line 17 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_56 = 56;
const unsigned_t TOPPERS_cfg_valueof_inhno_56 = ( unsigned_t )( INHNO_IPI_DIS_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_56 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_57 = TCL_2;
#line 18 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_57 = 57;
const unsigned_t TOPPERS_cfg_valueof_intno_57 = ( unsigned_t )( INTNO_IPI_DIS_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_57 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_57 = ( signed_t )( INTPRI_IPI_DIS_PRC2 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 19 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 23 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_58 = TCL_3;
#line 24 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_58 = 58;
const unsigned_t TOPPERS_cfg_valueof_inhno_58 = ( unsigned_t )( INHNO_IPI_DIS_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_58 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_59 = TCL_3;
#line 25 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_59 = 59;
const unsigned_t TOPPERS_cfg_valueof_intno_59 = ( unsigned_t )( INTNO_IPI_DIS_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_59 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_59 = ( signed_t )( INTPRI_IPI_DIS_PRC3 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 26 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 30 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_60 = TCL_4;
#line 31 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_60 = 60;
const unsigned_t TOPPERS_cfg_valueof_inhno_60 = ( unsigned_t )( INHNO_IPI_DIS_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_60 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_61 = TCL_4;
#line 32 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_61 = 61;
const unsigned_t TOPPERS_cfg_valueof_intno_61 = ( unsigned_t )( INTNO_IPI_DIS_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_61 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_61 = ( signed_t )( INTPRI_IPI_DIS_PRC4 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 33 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#ifdef USE_IPI_DIS_HANDER_BYPASS

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 38 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_62 = TCL_1;
#line 39 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_62 = 62;
const unsigned_t TOPPERS_cfg_valueof_inhno_62 = ( unsigned_t )( INHNO_IPI_EXT_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_62 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_63 = TCL_1;
#line 40 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_63 = 63;
const unsigned_t TOPPERS_cfg_valueof_intno_63 = ( unsigned_t )( INTNO_IPI_EXT_PRC1 ); const unsigned_t TOPPERS_cfg_valueof_intatr_63 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_63 = ( signed_t )( INTPRI_IPI_EXT_PRC1 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 41 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 44 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_64 = TCL_2;
#line 45 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_64 = 64;
const unsigned_t TOPPERS_cfg_valueof_inhno_64 = ( unsigned_t )( INHNO_IPI_EXT_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_64 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_65 = TCL_2;
#line 46 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_65 = 65;
const unsigned_t TOPPERS_cfg_valueof_intno_65 = ( unsigned_t )( INTNO_IPI_EXT_PRC2 ); const unsigned_t TOPPERS_cfg_valueof_intatr_65 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_65 = ( signed_t )( INTPRI_IPI_EXT_PRC2 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 47 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 51 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_66 = TCL_3;
#line 52 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_66 = 66;
const unsigned_t TOPPERS_cfg_valueof_inhno_66 = ( unsigned_t )( INHNO_IPI_EXT_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_66 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_67 = TCL_3;
#line 53 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_67 = 67;
const unsigned_t TOPPERS_cfg_valueof_intno_67 = ( unsigned_t )( INTNO_IPI_EXT_PRC3 ); const unsigned_t TOPPERS_cfg_valueof_intatr_67 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_67 = ( signed_t )( INTPRI_IPI_EXT_PRC3 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 54 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 58 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_68 = TCL_4;
#line 59 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_68 = 68;
const unsigned_t TOPPERS_cfg_valueof_inhno_68 = ( unsigned_t )( INHNO_IPI_EXT_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_inhatr_68 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_69 = TCL_4;
#line 60 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
const unsigned_t TOPPERS_cfg_static_api_69 = 69;
const unsigned_t TOPPERS_cfg_valueof_intno_69 = ( unsigned_t )( INTNO_IPI_EXT_PRC4 ); const unsigned_t TOPPERS_cfg_valueof_intatr_69 = ( unsigned_t )( TA_ENAINT ); const signed_t TOPPERS_cfg_valueof_intpri_69 = ( signed_t )( INTPRI_IPI_EXT_PRC4 ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 61 "../arch/arm64_gcc/bcm283x/chip_ipi.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#endif 

#endif 

#line 18 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_70 = 70;
const unsigned_t TOPPERS_cfg_valueof_iniatr_70 = ( unsigned_t )( TA_NULL ); 
#line 19 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_71 = 71;
const unsigned_t TOPPERS_cfg_valueof_teratr_71 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e7_5_DEFINED 1

#line 21 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e7_5 = TCL_1;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e7_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_72 = TCL_1;
#line 22 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_72 = 72;
#define TASK1_1	(<>)

#line 22 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_72 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_72 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_72 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_73 = TCL_1;
#line 23 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_73 = 73;
#define TASK1_2	(<>)

#line 23 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_73 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_73 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_73 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_74 = TCL_1;
#line 24 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_74 = 74;
#define TASK1_3	(<>)

#line 24 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_74 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_74 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_74 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_75 = TCL_1;
#line 25 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_75 = 75;
#define MAIN_TASK1	(<>)

#line 25 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_75 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_75 = ( signed_t )( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_75 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_76 = TCL_1;
#line 26 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_76 = 76;
#define SERVER_TASK1	(<>)

#line 26 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_76 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_76 = ( signed_t )( SERVER_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_76 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_77 = TCL_1;
#line 27 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_77 = 77;
const unsigned_t TOPPERS_cfg_valueof_texatr_77 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_78 = TCL_1;
#line 28 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_78 = 78;
const unsigned_t TOPPERS_cfg_valueof_texatr_78 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_79 = TCL_1;
#line 29 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_79 = 79;
const unsigned_t TOPPERS_cfg_valueof_texatr_79 = ( unsigned_t )( TA_NULL ); 
#ifdef TOPPERS_SYSTIM_LOCAL
const unsigned_t TOPPERS_cfg_valueof_CLASS_80 = TCL_1;
#line 31 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_80 = 80;
#define CYCHDR1	(<>)

#line 31 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_80 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_80 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_80 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_81 = TCL_1;
#line 32 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_81 = 81;
#define ALMHDR1	(<>)

#line 32 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_81 = ( unsigned_t )( TA_NULL ); 
#endif 

#ifdef CPUEXC1
const unsigned_t TOPPERS_cfg_valueof_CLASS_82 = TCL_1;
#line 35 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_82 = 82;
const unsigned_t TOPPERS_cfg_valueof_excno_82 = ( unsigned_t )( CPUEXC1 ); const unsigned_t TOPPERS_cfg_valueof_excatr_82 = ( unsigned_t )( TA_NULL ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_83 = TCL_1;
#line 37 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_83 = 83;
#define SERVER_DTQ1	(<>)

#line 37 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_83 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_dtqcnt_83 = ( unsigned_t )( NUM_SERVER_DTQ ); const unsigned_t TOPPERS_cfg_valueof_CLASS_84 = TCL_1;
#line 38 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_84 = 84;
const unsigned_t TOPPERS_cfg_valueof_iniatr_84 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_85 = TCL_1;
#line 39 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_85 = 85;
const unsigned_t TOPPERS_cfg_valueof_teratr_85 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e7_5

#line 40 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e7_5


#ifdef TOPPERS_SYSTIM_GLOBAL

#ifndef TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED 1

#line 43 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000d612f_14 = TCL_SYSTIM_PRC;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000d612f_14
const unsigned_t TOPPERS_cfg_valueof_CLASS_86 = TCL_SYSTIM_PRC;
#line 44 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_86 = 86;
#define CYCHDR1	(<>)

#line 44 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_86 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_86 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_86 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_87 = TCL_SYSTIM_PRC;
#line 45 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_87 = 87;
#define ALMHDR1	(<>)

#line 45 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_87 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000d612f_14

#line 46 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000d612f_14


#endif 

#if TNUM_PRCID >= 2

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e4_5_DEFINED 1

#line 50 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e4_5 = TCL_2;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e4_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_88 = TCL_2;
#line 51 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_88 = 88;
#define TASK2_1	(<>)

#line 51 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_88 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_88 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_88 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_89 = TCL_2;
#line 52 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_89 = 89;
#define TASK2_2	(<>)

#line 52 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_89 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_89 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_89 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_90 = TCL_2;
#line 53 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_90 = 90;
#define TASK2_3	(<>)

#line 53 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_90 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_90 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_90 = ( unsigned_t )( STACK_SIZE ); 
#ifndef G_SYSLOG
const unsigned_t TOPPERS_cfg_valueof_CLASS_91 = TCL_2;
#line 55 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_91 = 91;
#define MAIN_TASK2	(<>)

#line 55 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_91 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_91 = ( signed_t )( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_91 = ( unsigned_t )( STACK_SIZE ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_92 = TCL_2;
#line 57 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_92 = 92;
#define SERVER_TASK2	(<>)

#line 57 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_92 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_92 = ( signed_t )( SERVER_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_92 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_93 = TCL_2;
#line 58 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_93 = 93;
const unsigned_t TOPPERS_cfg_valueof_texatr_93 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_94 = TCL_2;
#line 59 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_94 = 94;
const unsigned_t TOPPERS_cfg_valueof_texatr_94 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_95 = TCL_2;
#line 60 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_95 = 95;
const unsigned_t TOPPERS_cfg_valueof_texatr_95 = ( unsigned_t )( TA_NULL ); 
#ifdef TOPPERS_SYSTIM_LOCAL
const unsigned_t TOPPERS_cfg_valueof_CLASS_96 = TCL_2;
#line 62 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_96 = 96;
#define CYCHDR2	(<>)

#line 62 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_96 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_96 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_96 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_97 = TCL_2;
#line 63 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_97 = 97;
#define ALMHDR2	(<>)

#line 63 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_97 = ( unsigned_t )( TA_NULL ); 
#endif 

#ifdef CPUEXC2
const unsigned_t TOPPERS_cfg_valueof_CLASS_98 = TCL_2;
#line 66 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_98 = 98;
const unsigned_t TOPPERS_cfg_valueof_excno_98 = ( unsigned_t )( CPUEXC2 ); const unsigned_t TOPPERS_cfg_valueof_excatr_98 = ( unsigned_t )( TA_NULL ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_99 = TCL_2;
#line 68 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_99 = 99;
#define SERVER_DTQ2	(<>)

#line 68 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_99 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_dtqcnt_99 = ( unsigned_t )( NUM_SERVER_DTQ ); const unsigned_t TOPPERS_cfg_valueof_CLASS_100 = TCL_2;
#line 69 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_100 = 100;
const unsigned_t TOPPERS_cfg_valueof_iniatr_100 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_101 = TCL_2;
#line 70 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_101 = 101;
const unsigned_t TOPPERS_cfg_valueof_teratr_101 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e4_5

#line 71 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e4_5


#ifdef TOPPERS_SYSTIM_GLOBAL

#ifndef TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED 1

#line 74 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000d612f_14 = TCL_SYSTIM_PRC;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000d612f_14
const unsigned_t TOPPERS_cfg_valueof_CLASS_102 = TCL_SYSTIM_PRC;
#line 75 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_102 = 102;
#define CYCHDR2	(<>)

#line 75 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_102 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_102 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_102 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_103 = TCL_SYSTIM_PRC;
#line 76 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_103 = 103;
#define ALMHDR2	(<>)

#line 76 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_103 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000d612f_14

#line 77 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000d612f_14


#endif 

#endif 

#if TNUM_PRCID >= 3

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e5_5_DEFINED 1

#line 82 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e5_5 = TCL_3;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e5_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_104 = TCL_3;
#line 83 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_104 = 104;
#define TASK3_1	(<>)

#line 83 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_104 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_104 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_104 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_105 = TCL_3;
#line 84 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_105 = 105;
#define TASK3_2	(<>)

#line 84 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_105 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_105 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_105 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_106 = TCL_3;
#line 85 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_106 = 106;
#define TASK3_3	(<>)

#line 85 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_106 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_106 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_106 = ( unsigned_t )( STACK_SIZE ); 
#ifndef G_SYSLOG
const unsigned_t TOPPERS_cfg_valueof_CLASS_107 = TCL_3;
#line 87 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_107 = 107;
#define MAIN_TASK3	(<>)

#line 87 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_107 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_107 = ( signed_t )( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_107 = ( unsigned_t )( STACK_SIZE ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_108 = TCL_3;
#line 89 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_108 = 108;
#define SERVER_TASK3	(<>)

#line 89 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_108 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_108 = ( signed_t )( SERVER_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_108 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_109 = TCL_3;
#line 90 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_109 = 109;
const unsigned_t TOPPERS_cfg_valueof_texatr_109 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_110 = TCL_3;
#line 91 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_110 = 110;
const unsigned_t TOPPERS_cfg_valueof_texatr_110 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_111 = TCL_3;
#line 92 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_111 = 111;
const unsigned_t TOPPERS_cfg_valueof_texatr_111 = ( unsigned_t )( TA_NULL ); 
#ifdef TOPPERS_SYSTIM_LOCAL
const unsigned_t TOPPERS_cfg_valueof_CLASS_112 = TCL_3;
#line 94 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_112 = 112;
#define CYCHDR3	(<>)

#line 94 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_112 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_112 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_112 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_113 = TCL_3;
#line 95 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_113 = 113;
#define ALMHDR3	(<>)

#line 95 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_113 = ( unsigned_t )( TA_NULL ); 
#endif 

#ifdef CPUEXC3
const unsigned_t TOPPERS_cfg_valueof_CLASS_114 = TCL_3;
#line 98 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_114 = 114;
const unsigned_t TOPPERS_cfg_valueof_excno_114 = ( unsigned_t )( CPUEXC3 ); const unsigned_t TOPPERS_cfg_valueof_excatr_114 = ( unsigned_t )( TA_NULL ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_115 = TCL_3;
#line 100 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_115 = 115;
#define SERVER_DTQ3	(<>)

#line 100 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_115 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_dtqcnt_115 = ( unsigned_t )( NUM_SERVER_DTQ ); const unsigned_t TOPPERS_cfg_valueof_CLASS_116 = TCL_3;
#line 101 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_116 = 116;
const unsigned_t TOPPERS_cfg_valueof_iniatr_116 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_117 = TCL_3;
#line 102 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_117 = 117;
const unsigned_t TOPPERS_cfg_valueof_teratr_117 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e5_5

#line 103 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e5_5


#ifdef TOPPERS_SYSTIM_GLOBAL

#ifndef TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED 1

#line 106 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000d612f_14 = TCL_SYSTIM_PRC;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000d612f_14
const unsigned_t TOPPERS_cfg_valueof_CLASS_118 = TCL_SYSTIM_PRC;
#line 107 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_118 = 118;
#define CYCHDR3	(<>)

#line 107 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_118 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_118 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_118 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_119 = TCL_SYSTIM_PRC;
#line 108 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_119 = 119;
#define ALMHDR3	(<>)

#line 108 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_119 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000d612f_14

#line 109 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000d612f_14


#endif 

#endif 

#if TNUM_PRCID >= 4

#ifndef TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000006e2_5_DEFINED 1

#line 114 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000006e2_5 = TCL_4;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000006e2_5
const unsigned_t TOPPERS_cfg_valueof_CLASS_120 = TCL_4;
#line 115 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_120 = 120;
#define TASK4_1	(<>)

#line 115 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_120 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_120 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_120 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_121 = TCL_4;
#line 116 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_121 = 121;
#define TASK4_2	(<>)

#line 116 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_121 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_121 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_121 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_122 = TCL_4;
#line 117 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_122 = 122;
#define TASK4_3	(<>)

#line 117 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_122 = ( unsigned_t )( TA_NULL ); const signed_t TOPPERS_cfg_valueof_itskpri_122 = ( signed_t )( MID_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_122 = ( unsigned_t )( STACK_SIZE ); 
#ifndef G_SYSLOG
const unsigned_t TOPPERS_cfg_valueof_CLASS_123 = TCL_4;
#line 119 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_123 = 123;
#define MAIN_TASK4	(<>)

#line 119 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_123 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_123 = ( signed_t )( MAIN_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_123 = ( unsigned_t )( STACK_SIZE ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_124 = TCL_4;
#line 121 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_124 = 124;
#define SERVER_TASK4	(<>)

#line 121 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_tskatr_124 = ( unsigned_t )( TA_ACT ); const signed_t TOPPERS_cfg_valueof_itskpri_124 = ( signed_t )( SERVER_PRIORITY ); const unsigned_t TOPPERS_cfg_valueof_stksz_124 = ( unsigned_t )( STACK_SIZE ); const unsigned_t TOPPERS_cfg_valueof_CLASS_125 = TCL_4;
#line 122 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_125 = 125;
const unsigned_t TOPPERS_cfg_valueof_texatr_125 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_126 = TCL_4;
#line 123 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_126 = 126;
const unsigned_t TOPPERS_cfg_valueof_texatr_126 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_127 = TCL_4;
#line 124 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_127 = 127;
const unsigned_t TOPPERS_cfg_valueof_texatr_127 = ( unsigned_t )( TA_NULL ); 
#ifdef TOPPERS_SYSTIM_LOCAL
const unsigned_t TOPPERS_cfg_valueof_CLASS_128 = TCL_4;
#line 126 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_128 = 128;
#define CYCHDR4	(<>)

#line 126 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_128 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_128 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_128 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_129 = TCL_4;
#line 127 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_129 = 129;
#define ALMHDR4	(<>)

#line 127 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_129 = ( unsigned_t )( TA_NULL ); 
#endif 

#ifdef CPUEXC4
const unsigned_t TOPPERS_cfg_valueof_CLASS_130 = TCL_4;
#line 130 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_130 = 130;
const unsigned_t TOPPERS_cfg_valueof_excno_130 = ( unsigned_t )( CPUEXC4 ); const unsigned_t TOPPERS_cfg_valueof_excatr_130 = ( unsigned_t )( TA_NULL ); 
#endif 
const unsigned_t TOPPERS_cfg_valueof_CLASS_131 = TCL_4;
#line 132 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_131 = 131;
#define SERVER_DTQ4	(<>)

#line 132 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_dtqatr_131 = ( unsigned_t )( TA_TPRI ); const unsigned_t TOPPERS_cfg_valueof_dtqcnt_131 = ( unsigned_t )( NUM_SERVER_DTQ ); const unsigned_t TOPPERS_cfg_valueof_CLASS_132 = TCL_4;
#line 133 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_132 = 132;
const unsigned_t TOPPERS_cfg_valueof_iniatr_132 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_CLASS_133 = TCL_4;
#line 134 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_133 = 133;
const unsigned_t TOPPERS_cfg_valueof_teratr_133 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000006e2_5

#line 135 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000006e2_5


#ifdef TOPPERS_SYSTIM_GLOBAL

#ifndef TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED
#define TOPPERS_cfg_valueof_0T_00000000000d612f_14_DEFINED 1

#line 138 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_0T_00000000000d612f_14 = TCL_SYSTIM_PRC;

#endif
#define TOPPERS_cfg_inside_of_0T_00000000000d612f_14
const unsigned_t TOPPERS_cfg_valueof_CLASS_134 = TCL_SYSTIM_PRC;
#line 139 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_134 = 134;
#define CYCHDR4	(<>)

#line 139 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_cycatr_134 = ( unsigned_t )( TA_NULL ); const unsigned_t TOPPERS_cfg_valueof_cyctim_134 = ( unsigned_t )( CYC_TIME ); const unsigned_t TOPPERS_cfg_valueof_cycphs_134 = ( unsigned_t )( 0 ); const unsigned_t TOPPERS_cfg_valueof_CLASS_135 = TCL_SYSTIM_PRC;
#line 140 "sample1.cfg"
const unsigned_t TOPPERS_cfg_static_api_135 = 135;
#define ALMHDR4	(<>)

#line 140 "sample1.cfg"
const unsigned_t TOPPERS_cfg_valueof_almatr_135 = ( unsigned_t )( TA_NULL ); 
#ifndef TOPPERS_cfg_inside_of_0T_00000000000d612f_14

#line 141 "sample1.cfg"
#error syntax error
#endif
#undef TOPPERS_cfg_inside_of_0T_00000000000d612f_14


#endif 

#endif 

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000d612f_14
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_000000000000da91_10
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e7_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000d612f_14
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e4_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000d612f_14
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e5_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000d612f_14
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000006e2_5
#error missing '}'
#endif

#ifdef TOPPERS_cfg_inside_of_0T_00000000000d612f_14
#error missing '}'
#endif

