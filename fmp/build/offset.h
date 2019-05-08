/* offset.h */

#define TCB_p_tinib	16
#define TCB_texptn	28
#define TCB_sp	40
#define TCB_pc	48
#define TINIB_exinf	8
#define TINIB_task	16
#define PCB_p_runtsk	24
#define PCB_p_schedtsk	32
#define PCB_reqflg	40
#define PCB_ipmflg	128
#define PCB_disdsp	132
#define PCB_dspflg	44
#define EXC_FRAME_cpsr	120
#define EXC_FRAME	288
#define TCB_enatex	26
#define TCB_enatex_bit	2
#define TCB_enatex_mask	0x4
#define PCB_p_firstlock	8
#define PCB_p_secondlock	16
#define PCB_locspnid	48
#define PCB_excpt_nest_count	64
#define PCB_istkpt	72
#define PCB_p_exch_tbl	80
#define PCB_p_inh_tbl	88
#define PCB_p_inh_iipm_tbl	96
#define PCB_p_iipm_mask_tbl	104
#define PCB_iipm	112