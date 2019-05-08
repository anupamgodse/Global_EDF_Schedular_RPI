/*
 *  TOPPERS/FMP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Flexible MultiProcessor Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2015 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)～(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: task.c 1087 2015-02-03 01:04:34Z ertl-honda $
 */

/*
 *		タスク管理モジュール
 */

#include "kernel_impl.h"
#include "wait.h"
#include "task.h"
#include "spin_lock.h"
#include "mp.h"

/*
 *  トレースログマクロのデフォルト定義
 */
#ifndef LOG_TEX_ENTER
#define LOG_TEX_ENTER(p_tcb, texptn)
#endif /* LOG_TEX_ENTER */

#ifndef LOG_TEX_LEAVE
#define LOG_TEX_LEAVE(p_tcb)
#endif /* LOG_TEX_LEAVE */

#ifdef TOPPERS_tskini

/*
 *  タスク管理モジュールの初期化
 */
int get_q_len(QUEUE *p_queue) {
    QUEUE *temp = p_queue->p_next;
    int num_elements=0;

    while(temp != p_queue) {
        num_elements++; 
        temp = temp->p_next;
    }

    return num_elements;
}

    void
initialize_task(void)
{
    //changes
    //syslog_2(LOG_INFO, "1 init task core %d, init pcb done %d", ID_PRC(x_prc_index()), init_pcb_done);
    while(!init_pcb_done) {
        tslp_tsk(10);
    }
    //syslog_1(LOG_INFO, "init task core %d", ID_PRC(x_prc_index()));

    uint_t	i, j;
    TCB		*p_tcb;
    PCB		*my_p_pcb;
    

    my_p_pcb = get_my_p_pcb();

    int count=0;
    for(i=0;i<TNUM_TPRI;i++) {
        count+=get_q_len(&(my_p_pcb->ready_queue[i]));
    }


    for (i = 0; i < tnum_tsk; i++) {
        j = INDEX_TSK(torder_table[i]);
        /* 自コアに割り付けれたタスクの初期化 */
        if (tinib_table[j].iaffinity == ID_PRC(x_prc_index())) {
            syslog_2(LOG_INFO, "init task core affinity %d, task %d", ID_PRC(x_prc_index()), i+1);
            p_tcb = p_tcb_table[j];
            p_tcb->p_tinib = &(tinib_table[j]);
            p_tcb->actque = false;
            p_tcb->actprc = TPRC_NONE;
            //p_tcb->p_pcb = my_p_pcb;
            p_tcb->p_pcb = NULL;
            make_dormant(p_tcb);

            //changes
            p_tcb->current_deadline=0;
            queue_initialize(&(p_tcb->global_queue_hook));

            if ((p_tcb->p_tinib->tskatr & TA_ACT) != 0U) {
                (void) make_active(p_tcb);
            }
        }
    }
    //changes
    if(x_sense_mprc()) {
        syslog_1(LOG_INFO, "total tasks at start = %d", count);
        syslog_1(LOG_INFO, "tnumtsk = %d", tnum_tsk);
    }
}

#endif /* TOPPERS_tskini */

/*
 *  ビットマップサーチ関数
 *
 *  bitmap内の1のビットの内，最も下位（右）のものをサーチし，そのビッ
 *  ト番号を返す．ビット番号は，最下位ビットを0とする．bitmapに0を指定
 *  してはならない．この関数では，bitmapが16ビットであることを仮定し，
 *  uint16_t型としている．
 *
 *  ビットサーチ命令を持つプロセッサでは，ビットサーチ命令を使うように
 *  書き直した方が効率が良い場合がある．このような場合には，ターゲット
 *  依存部でビットサーチ命令を使ったbitmap_searchを定義し，
 *  OMIT_BITMAP_SEARCHをマクロ定義すればよい．また，ビットサーチ命令の
 *  サーチ方向が逆などの理由で優先度とビットとの対応を変更したい場合に
 *  は，PRIMAP_BITをマクロ定義すればよい．
 *
 *  また，ライブラリにffsがあるなら，次のように定義してライブラリ関数を 
 *  使った方が効率が良い可能性もある
 *		#define	bitmap_search(bitmap) (ffs(bitmap) - 1)
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1U << (pri))
#endif /* PRIMAP_BIT */

#ifndef OMIT_BITMAP_SEARCH

static const unsigned char bitmap_search_table[] = { 0, 1, 0, 2, 0, 1, 0,
    3, 0, 1, 0, 2, 0, 1, 0 };

    Inline uint_t
bitmap_search(uint16_t bitmap)
{
    uint_t	n = 0U;

    assert(bitmap != 0U);
    if ((bitmap & 0x00ffU) == 0U) {
        bitmap >>= 8;
        n += 8;
    }
    if ((bitmap & 0x0fU) == 0U) {
        bitmap >>= 4;
        n += 4;
    }
    return(n + bitmap_search_table[(bitmap & 0x0fU) - 1]);
}

#endif /* OMIT_BITMAP_SEARCH */

/*
 *  優先度ビットマップが空かのチェック
 */
    Inline bool_t
primap_empty(PCB *p_pcb)
{
    return(p_pcb->ready_primap == 0U);
}

/*
 *  優先度ビットマップのサーチ
 */
    Inline uint_t
primap_search(PCB *p_pcb)
{
    return(bitmap_search(p_pcb->ready_primap));
}

/*
 *  優先度ビットマップのセット
 */
    Inline void
primap_set(PCB *p_pcb, uint_t pri)
{
    p_pcb->ready_primap |= PRIMAP_BIT(pri);
}

/*
 *  優先度ビットマップのクリア
 */
    Inline void
primap_clear(PCB *p_pcb, uint_t pri)
{
    p_pcb->ready_primap &= ~PRIMAP_BIT(pri);
}

/*
 *  最高優先順位タスクのサーチ
 */
#ifdef TOPPERS_tsksched

    TCB *
search_schedtsk(PCB *p_pcb)
{
    uint_t	schedpri;
    schedpri = primap_search(p_pcb);
    return((TCB *)((p_pcb->ready_queue)[schedpri].p_next));
}

TCB *edf_pri_search_schedtsk(int pri) {
    QUEUE *p_queue = &g_edf_q[pri];
    QUEUE *temp = p_queue->p_next; 
    while(temp != p_queue) {
        /*if(GET_TCB_ADDR(temp)->actprc == TPRC_NONE) {
            return GET_TCB_ADDR(temp);
        }*/
        if(GET_TCB_ADDR(temp)->p_pcb == NULL) {
            return GET_TCB_ADDR(temp);
        }
        temp = temp->p_next;
    }
    return NULL;
}

TCB *edf_search_schedtsk() {
    int i=0;
    TCB *target;
    for(i = 0; i<TNUM_TPRI; i++) {
        target = edf_pri_search_schedtsk(i);
        if(target!=NULL) {
            return target;
        }
    }
    return NULL;
}

#endif /* TOPPERS_tsksched */

//changes

//call only for valid position
TCB *get_q_element_edf(QUEUE *p_queue, int position) {
    QUEUE *temp = p_queue->p_next;
    int current=0;

    while(current!=position) {
        temp = temp->p_next;
        current++;
    }

    return GET_TCB_ADDR(temp);
}




TCB *get_q_element_edf_g(int position) {
    int pri;
    int count=0;
    int prev_count=count;

    for(pri = 0; pri < TNUM_TPRI && count <= position; pri++) {
        prev_count=count;
        count+=get_q_len(&((g_edf_q)[pri]));
    }

    return get_q_element_edf(&((g_edf_q)[pri]), position-prev_count);
}
//new
int get_total_ready() {
    int num_elements=0;

    int pri;
    for(pri=0; pri<TNUM_TPRI; pri++) {
        num_elements+=get_q_len(&((g_edf_q)[pri]));
    }

    return num_elements;
}

int get_total_ready_higher(int cpri) {
    int num_elements=0;

    int pri;
    for(pri=0; pri<cpri; pri++) {
        num_elements+=get_q_len(&((g_edf_q)[pri]));
    }

    return num_elements;
}

int q_insert_edf(QUEUE *p_queue, QUEUE *p_entry) {
    QUEUE *temp = p_queue->p_next; 
    int position=-1;
    int core=ID_PRC(x_prc_index());


    //syslog_1(LOG_INFO, "q_ins edf before if core = %d", core);
    //if(temp!=p_queue) {
    //    syslog_1(LOG_INFO, "q_ins edf inside if = %d", core);
    //    syslog_2(LOG_INFO, "while start %d, core=%d ", ((GET_TCB_ADDR(temp))->current_deadline), core);
    //}
    //syslog_1(LOG_INFO, "q_ins edf before while core = %d", core);
    //syslog_2(LOG_INFO, "while start %d, core=%d ", ((GET_TCB_ADDR(p_entry))->current_deadline), core);
    while(temp!=p_queue && (((GET_TCB_ADDR(p_entry))->current_deadline) >= ((GET_TCB_ADDR(temp))->current_deadline))) {
        temp=temp->p_next;
        syslog_2(LOG_INFO, "while position= %d, core=%d", position, core);
        position++;
    }

    //syslog_1(LOG_INFO, "q_insert_prev, core=%d", core);
    queue_insert_prev(temp, p_entry);
    g_edf_q_count++;
    //syslog_1(LOG_INFO, "q_insert_prev done, core=%d", core);

    return (position<0)?0:position;
}

PCB* get_first_open_core() {
    int i;
    PCB *temp;
    for(i = 0; i < TNUM_PRCID; i++) {
        //syslog_0(LOG_INFO, "getpcb");
        temp = get_mp_p_pcb(ID_PRC(i));
        //syslog_0(LOG_INFO, "gotpcb");
        if(temp->p_schedtsk == NULL) {
            //syslog_0(LOG_INFO, "return valid");
            return temp;
        }
    }
    //syslog_0(LOG_INFO, "return null");
    return NULL;
}


/*
 *  実行できる状態への移行
 *
 *  最高優先順位のタスクを更新するのは，実行できるタスクがなかった場合
 *  と，p_tcbの優先度が最高優先順位のタスクの優先度よりも高い場合であ
 *  る．
 */
#ifdef TOPPERS_tskrun

    bool_t
make_runnable(TCB *p_tcb)
{
    uint_t	pri = p_tcb->priority;
    syslog_2(LOG_INFO, "In make runnable prio %d p_tcb = %lu", pri, p_tcb);
    PCB		*p_pcb = NULL;

    int position;
    int num_elements;
    TCB *to_replace;
    bool_t flag=false;
    int core=ID_PRC(x_prc_index());
    int pos_local, pos_global;
    int num_elements_higher;

    //syslog_1(LOG_INFO, "make runnable: acquiring queue lock, core=%d", core);

    //changes  
    t_acquire_obj_lock(&lck_g_edf_q);
    //syslog_1(LOG_INFO, "make runnable: acquired queue lock, core=%d", core);

    /*
    //syslog_1(LOG_INFO, "make runnable: get position, core=%d", core);
    position = q_insert_edf(&((g_edf_q)[pri]), &(p_tcb->global_queue_hook));
    //syslog_1(LOG_INFO, "make runnable: got position, get num_elements, core=%d", core);
    //num_elements = get_q_len(&((g_edf_q)[pri]));
    num_elements = get_total_ready();
    syslog_3(LOG_INFO, "make runnable: pos= %d, num_elem= %d, core=%d", position, num_elements, core);

    //replace
    if(num_elements>TNUM_PRCID && position <= TNUM_PRCID) {
        syslog_0(LOG_INFO, "replace");
        to_replace = get_q_element_edf(&((g_edf_q)[pri]), TNUM_PRCID);
        p_pcb = to_replace->p_pcb;
        syslog_1(LOG_INFO, "replacing on proc %d", to_replace->actprc);
        to_replace->p_pcb = NULL; 
        to_replace->actprc = TPRC_NONE;
        flag = true;
    }
    else if(num_elements <= TNUM_PRCID){//schedule on first open core
        syslog_0(LOG_INFO, "schedule");
        p_pcb = get_first_open_core(); 
        syslog_1(LOG_INFO, "scheduling on proc %d", p_pcb->prcid);
        flag = true;
    }
*/
    //syslog_1(LOG_INFO, "make runnable: done if else, core=%d", core);
    //
    //syslog_1(LOG_INFO, "make runnable: get position, core=%d", core);
    pos_local = q_insert_edf(&((g_edf_q)[pri]), &(p_tcb->global_queue_hook));
    //syslog_1(LOG_INFO, "make runnable: got position, get num_elements, core=%d", core);
    //num_elements = get_q_len(&((g_edf_q)[pri]));
    //num_elements = get_total_ready();
    num_elements_higher = get_total_ready_higher(pri);
    pos_global = pos_local+num_elements_higher;
    syslog_5(LOG_INFO, "make runnable: pos_local= %d, num_elem= %d, pos_global = %d, higher = %d, core=%d", pos_local, g_edf_q_count, pos_global, num_elements_higher, core);

    //replace
    if(g_edf_q_count>TNUM_PRCID && pos_global < TNUM_PRCID) {
        syslog_0(LOG_INFO, "replace");
        //to_replace = get_q_element_edf(&((g_edf_q)[pri]), TNUM_PRCID);
        to_replace = get_q_element_edf_g(TNUM_PRCID);
        syslog_1(LOG_INFO, "to_replace %d", to_replace);
        p_pcb = to_replace->p_pcb;
        syslog_1(LOG_INFO, "replacing on proc %d", to_replace->actprc);
        to_replace->p_pcb = NULL; 
        //to_replace->actprc = TPRC_NONE;
        //to_replace->actque = false;
        flag = true;
    }
    else if(g_edf_q_count <= TNUM_PRCID){//schedule on first open core
        syslog_0(LOG_INFO, "schedule");
        p_pcb = get_first_open_core(); 
        syslog_1(LOG_INFO, "scheduling on proc %d", p_pcb->prcid);
        flag = true;
    }

    //p_pcb = p_tcb->p_pcb;
    //queue_insert_prev(&((p_pcb->ready_queue)[pri]), &(p_tcb->task_queue));
    //primap_set(p_pcb, pri);
    edf_primap |= PRIMAP_BIT(pri);

    if (flag) {
        syslog_0(LOG_INFO, "flag");
        p_pcb->p_schedtsk = p_tcb;
        p_tcb->p_pcb = p_pcb;
        //p_tcb->actprc = p_pcb->prcid;
        //p_tcb->actque = true;
        syslog_1(LOG_INFO, "dispatching make runnable: releasing lock, core=%d", p_pcb->prcid);
        release_obj_lock(&lck_g_edf_q);
        return(p_pcb->dspflg);
    }
    //syslog_1(LOG_INFO, "make runnable: releasing lock, core=%d", core);
    release_obj_lock(&lck_g_edf_q);
    return(false);
}

#endif /* TOPPERS_tskrun */

/*
 *  実行できる状態から他の状態への移行
 *
 *  最高優先順位のタスクを更新するのは，p_tcbが最高優先順位のタスクで
 *  あった場合である．p_tcbと同じ優先度のタスクが他にある場合は，p_tcb
 *  の次のタスクが最高優先順位になる．そうでない場合は，レディキューを
 *  サーチする必要がある．
 */
#ifdef TOPPERS_tsknrun

    bool_t
make_non_runnable(TCB *p_tcb)
{

    t_acquire_obj_lock(&lck_g_edf_q);
    syslog_2(LOG_INFO, "In make non _runnable entry1 total=%d done with %d changes working", get_total_ready(), p_tcb);
    uint_t	pri = p_tcb->priority;
    //QUEUE	*p_queue = &((p_tcb->p_pcb->ready_queue)[pri]);
    QUEUE	*p_queue = &((g_edf_q)[pri]);
    PCB		*p_pcb = p_tcb->p_pcb;

    //queue_delete(&(p_tcb->task_queue));
    queue_delete(&(p_tcb->global_queue_hook));
    g_edf_q_count--;
    syslog_1(LOG_INFO, "In make non _runnable entry2 %d", get_total_ready());

    if (queue_empty(p_queue)) {
       //primap_clear(p_pcb,pri);
        edf_primap &= ~PRIMAP_BIT(pri);
        /*if (p_pcb->p_schedtsk == p_tcb) {
          p_pcb->p_schedtsk = primap_empty(p_pcb) ? (TCB *) NULL : search_schedtsk(p_pcb);
          return(p_pcb->dspflg);
          }*/
    }
    /*else {
      if (p_pcb->p_schedtsk == p_tcb) {
      p_pcb->p_schedtsk = (TCB *)(p_queue->p_next);
      return(p_pcb->dspflg);
      }
      }*/

    //p_tcb->actprc = TPRC_NONE;
    //p_tcb->actque = false;
    p_tcb->p_pcb = NULL;

    if (p_pcb->p_schedtsk == p_tcb) {
        p_pcb->p_schedtsk = (edf_primap == 0U) ? (TCB *) NULL : edf_search_schedtsk();
        release_obj_lock(&lck_g_edf_q);
        syslog_1(LOG_INFO, "In make non _runnable done 1 sched %d", p_pcb->p_schedtsk);
        if(p_pcb->p_schedtsk != NULL) {
            p_pcb->p_schedtsk->p_pcb = p_pcb;
            //p_pcb->p_schedtsk->actprc = p_pcb->prcid;
            //p_pcb->p_schedtsk->actque = true;
        }
        syslog_1(LOG_NOTICE, "IN make_non_runnable dspflg = %d", p_pcb->dspflg);
        return(p_pcb->dspflg);
    }
    release_obj_lock(&lck_g_edf_q);
    syslog_0(LOG_INFO, "In make non _runnable done 2");
    return(false);
}

#endif /* TOPPERS_tsknrun */

/*
 *  休止状態への移行
 */
#ifdef TOPPERS_tskdmt

    void
make_dormant(TCB *p_tcb)
{
    p_tcb->tstat = TS_DORMANT;
    p_tcb->priority = p_tcb->p_tinib->ipriority;
    p_tcb->wupque = false;
    p_tcb->enatex = false;
    p_tcb->texptn = 0U;
#if TTYPE_KLOCK != G_KLOCK
    p_tcb->pend_relwai = false;
    p_tcb->pend_chgpri = false;
#endif /* TTYPE_KLOCK != G_KLOCK */
    LOG_TSKSTAT(p_tcb);
}

#endif /* TOPPERS_tskdmt */

/*
 *  休止状態から実行できる状態への移行
 */
#ifdef TOPPERS_tskact

    bool_t
make_active(TCB *p_tcb)
{
    activate_context(p_tcb);
    p_tcb->tstat = TS_RUNNABLE;
    LOG_TSKSTAT(p_tcb);
    return(make_runnable(p_tcb));
}

#endif /* TOPPERS_tskact */

/*
 *  タスクの優先度の変更
 *
 *  タスクが実行できる状態の場合には，レディキューの中での位置を変更す
 *  る．オブジェクトの待ちキューの中で待ち状態になっている場合には，待
 *  ちキューの中での位置を変更する．
 *
 *  最高優先順位のタスクを更新するのは，(1) p_tcbが最高優先順位のタス
 *  クであって，その優先度を下げた場合，(2) p_tcbが最高優先順位のタス
 *  クではなく，変更後の優先度が最高優先順位のタスクの優先度よりも高い
 *  場合である．(1)の場合には，レディキューをサーチする必要がある．
 */
#ifdef TOPPERS_tskpri

    bool_t
change_priority(TCB *p_tcb, uint_t newpri)
{
    uint_t	oldpri;
    PCB		*p_pcb;

    p_pcb = p_tcb->p_pcb;
    oldpri = p_tcb->priority;
    p_tcb->priority = newpri;

    if (TSTAT_RUNNABLE(p_tcb->tstat)) {
        /*
         *  タスクが実行できる状態の場合
         */
        queue_delete(&(p_tcb->task_queue));
        if (queue_empty(&((p_pcb->ready_queue)[oldpri]))) {
            primap_clear(p_pcb, oldpri);
        }
        queue_insert_prev(&((p_pcb->ready_queue)[newpri]), &(p_tcb->task_queue));
        primap_set(p_pcb, newpri);

        if (p_pcb->p_schedtsk == p_tcb) {
            if (newpri >= oldpri) {
                p_pcb->p_schedtsk = search_schedtsk(p_pcb);
                return(p_pcb->p_schedtsk != p_tcb && p_pcb->dspflg);
            }
        }
        else {
            if (newpri < p_pcb->p_schedtsk->priority) {
                p_pcb->p_schedtsk = p_tcb;
                return(p_pcb->dspflg);
            }
        }
    }
    else {
        if (TSTAT_WAIT_WOBJCB(p_tcb->tstat)) {
            /*
             *  タスクが，同期・通信オブジェクトの管理ブロックの共通部
             *  分（WOBJCB）の待ちキューにつながれている場合
             */
            wobj_change_priority(p_tcb->p_wobjcb, p_tcb);
        }
    }
    return(false);
}

#endif /* TOPPERS_tskpri */

/*
 *  レディキューの回転
 *
 *  最高優先順位のタスクを更新するのは，最高優先順位のタスクがタスクキ
 *  ューの末尾に移動した場合である．
 *
 */
#ifdef TOPPERS_tskrot

    bool_t
rotate_ready_queue(uint_t pri, PCB *p_pcb)
{
    QUEUE	*p_queue = &((p_pcb->ready_queue)[pri]);
    QUEUE	*p_entry;

    if (!queue_empty(p_queue) && p_queue->p_next->p_next != p_queue) {
        p_entry = queue_delete_next(p_queue);
        queue_insert_prev(p_queue, p_entry);
        if (p_pcb->p_schedtsk == (TCB *) p_entry) {
            p_pcb->p_schedtsk = (TCB *)(p_queue->p_next);
            return(p_pcb->dspflg);
        }
    }
    return(false);
}

#endif /* TOPPERS_tskrot */

/*
 *  優先順位を同一優先度のタスクの中で最低に
 *
 *  該当優先度のレディキューの最後尾に接続する． 
 *  最高優先順位のタスクを更新するのは，最高優先順位のタスクがタスクキ
 *  ューの末尾に移動した場合である．
 */
#ifdef TOPPERS_tsklowprce

    bool_t
set_lowest_precedence(TCB *p_tcb, PCB *p_pcb)
{
    uint_t	pri = p_tcb->priority;
    QUEUE	*p_queue = &((p_pcb->ready_queue)[pri]);

    queue_delete(&(p_tcb->task_queue));
    queue_insert_prev(p_queue, &(p_tcb->task_queue));

    if (p_pcb->p_schedtsk == p_tcb) {
        p_pcb->p_schedtsk = (TCB *)(p_queue->p_next);
        return(p_pcb->dspflg);
    }
    return(false);
}

#endif /* TOPPERS_tsklowprce */

/*
 *  タスク例外処理ルーチンの呼出し
 *
 *  FMPカーネルでは，タスク例外処理ルーチン内でCPUロック状態に移行し，
 *  元の状態に戻さずにリターンした場合，カーネルが元の状態に戻す．
 */
#ifdef TOPPERS_tsktex
#ifndef OMIT_CALL_TEXRTN

    void
call_texrtn(PCB *my_p_pcb)
{
    TEXPTN	texptn;
    bool_t	saved_disdsp;
    TCB		*p_runtsk;

    saved_disdsp = my_p_pcb->disdsp;
    p_runtsk = my_p_pcb->p_runtsk;
    p_runtsk->enatex = false;
    do {
        texptn = p_runtsk->texptn;
        p_runtsk->texptn = 0U;
        /* タスクロックの解放 */
        release_tsk_lock(my_p_pcb);
        t_unlock_cpu();

        LOG_TEX_ENTER(p_runtsk, texptn);
        (*((TEXRTN)(p_runtsk->p_tinib->texrtn)))(texptn,
                p_runtsk->p_tinib->exinf);
        LOG_TEX_LEAVE(p_runtsk);

        if (!t_sense_lock()) {
            t_lock_cpu();
        }
        /* タスクロックの取得 */
        my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
        if (!my_p_pcb->ipmflg) {
            t_set_ipm(TIPM_ENAALL);
            my_p_pcb->ipmflg = true;
        }
        my_p_pcb->disdsp = saved_disdsp;
        my_p_pcb->dspflg = !my_p_pcb->disdsp;
        p_runtsk->enatex = false;
        force_unlock_spin(my_p_pcb);
        if (p_runtsk != my_p_pcb->p_schedtsk && my_p_pcb->dspflg) {
            /* タスクロックの解放（CPUロックは解除しない） */
            release_tsk_lock(my_p_pcb);
            dispatch();
            /* タスクロックの取得 */
            my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
        }
    } while (p_runtsk->texptn != 0U);
    p_runtsk->enatex = true;
}

/*
 *  ディスパッチャーからのタスク例外処理ルーチンの呼び出し
 *
 *  タスクロックを取得してから call_texrtn() を呼び出す． 
 */
    void
dispatch_call_texrtn(void)
{
    PCB		*my_p_pcb;

    /* タスクロックの取得 */
    my_p_pcb = t_acquire_tsk_lock_self_without_runnable_check();
    call_texrtn(my_p_pcb);
    /* マイグレーションされている可能性があるので再取得 */
    my_p_pcb = get_my_p_pcb();
    /* タスクロックの解放 */
    release_tsk_lock(my_p_pcb);
}


#endif /* OMIT_CALL_TEXRTN */

/*
 *  タスク例外処理ルーチンの起動
 */
#ifndef OMIT_CALLTEX

    void
calltex(void)
{
    PCB *my_p_pcb;

    my_p_pcb = get_my_p_pcb();
    if (my_p_pcb->p_runtsk->enatex && my_p_pcb->p_runtsk->texptn != 0U
            && my_p_pcb->ipmflg) {
        dispatch_call_texrtn();
    }
}

#endif /* OMIT_CALLTEX */
#endif /* TOPPERS_tsktex */

#ifdef TOPPERS_migrate_self

/*
 *  タスクコンテキストでの自タスクに対するマイグレーション処理
 *
 *  CPUロック，移動元と移動先のタスクロックの取得，コンテキスト
 *  を保存したのち，非タスクコンテキストのスタックで来ること． 
 */
    void
migrate_self(ID prcid)
{
    TCB		*p_tcb;
    PCB		*t_p_pcb;
    PCB		*f_p_pcb;

    f_p_pcb = get_my_p_pcb();
    p_tcb = f_p_pcb->p_runtsk;

    /* 移動先のプロセッサのPCBを取得 */
    t_p_pcb = get_mp_p_pcb(prcid);

    if (TSTAT_RUNNABLE(p_tcb->tstat)) {
        /* レディーキューから外す */
        syslog_0(LOG_INFO, "make non_runnable, task.c, mig_self");
        make_non_runnable(p_tcb);
        /* pcb の書き換え */
        p_tcb->p_pcb = t_p_pcb;
        /* 移行先のプロセッサでmake_runnable する*/
        if (make_runnable(p_tcb)) {
            dispatch_request(t_p_pcb);
        }
    }
    else {
        /*
         * CPUロックかつタスクロックを取得しているため
         * 他の状態にはならない
         */
        assert(0);
    }
    release_dual_tsk_lock(f_p_pcb, t_p_pcb);

    /* ディスパッチャーへ */
    exit_and_dispatch();
    assert(0);
}

#endif /* TOPPERS_migrate_self */

#ifdef TOPPERS_exit_and_migrate_self

/*
 *  タスクコンテキストでの自タスクに対するコンテキストの破棄と
 *  マイグレーション処理
 *
 *  CPUロック，移動元と移動先のタスクロックの取得したのち，
 *  非タスクコンテキストのスタックで来ること． 
 */
    void
exit_and_migrate_self(ID prcid)
{
    TCB		*p_tcb;
    PCB		*t_p_pcb;
    PCB		*f_p_pcb;

    f_p_pcb = get_my_p_pcb();
    p_tcb = f_p_pcb->p_runtsk;

    /* 移動先のプロセッサのPCBを取得 */
    t_p_pcb = get_mp_p_pcb(prcid);

    syslog_0(LOG_INFO,"make non_runnable, task.c, ext_mig_tsk");
    (void) make_non_runnable(p_tcb);
    make_dormant(p_tcb);
    p_tcb->p_pcb = t_p_pcb;
    p_tcb->actque = false;
    p_tcb->actprc = TPRC_NONE;
    if (make_active(p_tcb)) {
        dispatch_request(t_p_pcb);
    }
    release_dual_tsk_lock(f_p_pcb, t_p_pcb);

    /* ディスパッチャーへ */
    exit_and_dispatch();
    assert(0);
}

#endif /* TOPPERS_exit_and_migrate_self */
