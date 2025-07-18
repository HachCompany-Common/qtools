//============================================================================
// QP/C Real-Time Event Framework (RTEF)
//
// Copyright (C) 2005 Quantum Leaps, LLC. All rights reserved.
//
//                    Q u a n t u m  L e a P s
//                    ------------------------
//                    Modern Embedded Software
//
// SPDX-License-Identifier: LicenseRef-QL-commercial
//
// This software is licensed under the terms of the Quantum Leaps commercial
// licenses. Please contact Quantum Leaps for more information about the
// available licensing options.
//
// RESTRICTIONS
// You may NOT :
// (a) redistribute, encumber, sell, rent, lease, sublicense, or otherwise
//     transfer rights in this software,
// (b) remove or alter any trademark, logo, copyright or other proprietary
//     notices, legends, symbols or labels present in this software,
// (c) plagiarize this software to sidestep the licensing obligations.
//
// Quantum Leaps contact information:
// <www.state-machine.com/licensing>
// <info@state-machine.com>
//============================================================================
#ifndef QS_H_
#define QS_H_

#ifndef Q_SPY
    #error Q_SPY must be defined to include qs.h
#endif

//============================================================================
//! @cond INTERNAL

#ifndef QS_CTR_SIZE
#define QS_CTR_SIZE 2U
#endif

#ifndef QS_TIME_SIZE
#define QS_TIME_SIZE 4U
#endif

//! @endcond

//============================================================================
//! @class QS
typedef struct {
    //! @cond INTERNAL
    uint8_t dummy;
    //! @endcond
} QS;

//! pre-defined QS record IDs
enum QSpyPre {
    // [0] QS session (not maskable)
    QS_EMPTY,             //!< QS record for cleanly starting a session

    // [1] SM records
    QS_QEP_STATE_ENTRY,   //!< a state was entered
    QS_QEP_STATE_EXIT,    //!< a state was exited
    QS_QEP_STATE_INIT,    //!< an initial transition was taken in a state
    QS_QEP_INIT_TRAN,     //!< the top-most initial transition was taken
    QS_QEP_INTERN_TRAN,   //!< an internal transition was taken
    QS_QEP_TRAN,          //!< a regular transition was taken
    QS_QEP_IGNORED,       //!< an event was ignored (silently discarded)
    QS_QEP_DISPATCH,      //!< an event was dispatched (begin of RTC step)
    QS_QEP_UNHANDLED,     //!< an event was un-handled due to a guard

    // [10] Active Object (AO) records
    QS_QF_ACTIVE_DEFER,   //!< AO deferred an event
    QS_QF_ACTIVE_RECALL,  //!< AO recalled an event
    QS_QF_ACTIVE_SUBSCRIBE,   //!< an AO subscribed to an event
    QS_QF_ACTIVE_UNSUBSCRIBE, //!< an AO unsubscribed to an event
    QS_QF_ACTIVE_POST,      //!< an event was posted (FIFO) directly to AO
    QS_QF_ACTIVE_POST_LIFO, //!< an event was posted (LIFO) directly to AO
    QS_QF_ACTIVE_GET,     //!< AO got an event and its queue is not empty
    QS_QF_ACTIVE_GET_LAST,//!< AO got an event and its queue is empty
    QS_QF_ACTIVE_RECALL_ATTEMPT, //!< AO attempted to recall an event

    // [19] Event Queue (EQ) records
    QS_QF_EQUEUE_POST,      //!< an event was posted (FIFO) to a raw queue
    QS_QF_EQUEUE_POST_LIFO, //!< an event was posted (LIFO) to a raw queue
    QS_QF_EQUEUE_GET,     //!< get an event and queue still not empty
    QS_QF_EQUEUE_GET_LAST,//!< get the last event from the queue

    // [23] Framework (QF) records
    QS_QF_NEW_ATTEMPT,    //!< an attempt to allocate an event failed

    // [24] Memory Pool (MP) records
    QS_QF_MPOOL_GET,      //!< a memory block was removed from memory pool
    QS_QF_MPOOL_PUT,      //!< a memory block was returned to memory pool

    // [26] Additional Framework (QF) records
    QS_QF_PUBLISH,        //!< an event was published to active objects
    QS_QF_NEW_REF,        //!< new event reference was created
    QS_QF_NEW,            //!< new event was created
    QS_QF_GC_ATTEMPT,     //!< garbage collection attempt
    QS_QF_GC,             //!< garbage collection
    QS_QF_TICK,           //!< QTimeEvt tick was called

    // [32] Time Event (TE) records
    QS_QF_TIMEEVT_ARM,    //!< a time event was armed
    QS_QF_TIMEEVT_AUTO_DISARM, //!< a time event expired and was disarmed
    QS_QF_TIMEEVT_DISARM_ATTEMPT,//!< attempt to disarm a disarmed QTimeEvt
    QS_QF_TIMEEVT_DISARM, //!< true disarming of an armed time event
    QS_QF_TIMEEVT_REARM,  //!< rearming of a time event
    QS_QF_TIMEEVT_POST,   //!< a time event posted itself directly to an AO

    // [38] Additional Framework (QF) records
    QS_QF_DELETE_REF,     //!< an event reference is about to be deleted
    QS_QF_CRIT_ENTRY,     //!< critical section was entered
    QS_QF_CRIT_EXIT,      //!< critical section was exited
    QS_QF_ISR_ENTRY,      //!< an ISR was entered
    QS_QF_ISR_EXIT,       //!< an ISR was exited
    QS_QF_INT_DISABLE,    //!< interrupts were disabled
    QS_QF_INT_ENABLE,     //!< interrupts were enabled

    // [45] Additional Active Object (AO) records
    QS_QF_ACTIVE_POST_ATTEMPT,//!< attempt to post an evt to AO failed

    // [46] Additional Event Queue (EQ) records
    QS_QF_EQUEUE_POST_ATTEMPT,//!< attempt to post evt to QEQueue failed

    // [47] Additional Memory Pool (MP) records
    QS_QF_MPOOL_GET_ATTEMPT,  //!< attempt to get a memory block failed

    // [48] Scheduler (SC) records
    QS_SCHED_PREEMPT,     //!< scheduler asynchronously preempted a task
    QS_SCHED_RESTORE,     //!< scheduler restored preempted task
    QS_SCHED_LOCK,        //!< scheduler was locked
    QS_SCHED_UNLOCK,      //!< scheduler was unlocked
    QS_SCHED_NEXT,        //!< scheduler started next task
    QS_SCHED_IDLE,        //!< scheduler restored the idle task

    // [54] Miscellaneous QS records (not maskable)
    QS_ENUM_DICT,         //!< enumeration dictionary entry

    // [55] Additional QEP records
    QS_QEP_TRAN_HIST,     //!< a tran. to history was taken
    QS_RESERVED_56,       //!< reserved (previously QS_QEP_TRAN_EP)
    QS_RESERVED_57,       //!< reserved (previously QS_QEP_TRAN_XP)

    // [58] Miscellaneous QS records (not maskable)
    QS_TEST_PAUSED,       //!< test has been paused
    QS_TEST_PROBE_GET,    //!< reports that Test-Probe has been used
    QS_SIG_DICT,          //!< signal dictionary entry
    QS_OBJ_DICT,          //!< object dictionary entry
    QS_FUN_DICT,          //!< function dictionary entry
    QS_USR_DICT,          //!< user QS record dictionary entry
    QS_TARGET_INFO,       //!< reports the Target information
    QS_TARGET_DONE,       //!< reports completion of a user callback
    QS_RX_STATUS,         //!< reports QS data receive status
    QS_QUERY_DATA,        //!< reports the data from "current object" query
    QS_PEEK_DATA,         //!< reports the data from the PEEK query
    QS_ASSERT_FAIL,       //!< assertion failed in the code
    QS_QF_RUN,            //!< QF_run() was entered

    // [71] Semaphore (SEM) records
    QS_SEM_TAKE,          //!< a semaphore was taken by a thread
    QS_SEM_BLOCK,         //!< a semaphore blocked a thread
    QS_SEM_SIGNAL,        //!< a semaphore was signaled
    QS_SEM_BLOCK_ATTEMPT, //!< a semaphore blocked was attempted

    // [75] Mutex (MTX) records
    QS_MTX_LOCK,          //!< a mutex was locked
    QS_MTX_BLOCK,         //!< a mutex blocked a thread
    QS_MTX_UNLOCK,        //!< a mutex was unlocked
    QS_MTX_LOCK_ATTEMPT,  //!< a mutex lock was attempted
    QS_MTX_BLOCK_ATTEMPT, //!< a mutex blocking was attempted
    QS_MTX_UNLOCK_ATTEMPT,//!< a mutex unlock was attempted

    // [81]
    QS_QF_ACTIVE_DEFER_ATTEMPT, //!< AO attempted to deferr an event
    QS_PRE_MAX            //!< the # predefined signals
};

//! QS-TX record groups for QS_GLB_FILTER()
enum QSpyGroups {
    QS_ALL_RECORDS = 0xF0,//!< all maskable QS records
    QS_SM_RECORDS,        //!< State Machine QS records
    QS_AO_RECORDS,        //!< Active Object QS records
    QS_EQ_RECORDS,        //!< Event Queues QS records
    QS_MP_RECORDS,        //!< Memory Pools QS records
    QS_TE_RECORDS,        //!< Time Events QS records
    QS_QF_RECORDS,        //!< QF QS records
    QS_SC_RECORDS,        //!< Scheduler QS records
    QS_SEM_RECORDS,       //!< Semaphore QS records
    QS_MTX_RECORDS,       //!< Mutex QS records
    QS_U0_RECORDS,        //!< User Group 100-104 records
    QS_U1_RECORDS,        //!< User Group 105-109 records
    QS_U2_RECORDS,        //!< User Group 110-114 records
    QS_U3_RECORDS,        //!< User Group 115-119 records
    QS_U4_RECORDS,        //!< User Group 120-124 records
    QS_UA_RECORDS         //!< All User records
};

//! QS user record group offsets for QS_GLB_FILTER()
enum QSpyUserOffsets {
    QS_USER  = 100,          //!< the first record available to QS users
    QS_USER0 = QS_USER,      //!< offset for User Group 0
    QS_USER1 = (enum_t)QS_USER0 + 5, //!< offset for User Group 1
    QS_USER2 = (enum_t)QS_USER1 + 5, //!< offset for User Group 2
    QS_USER3 = (enum_t)QS_USER2 + 5, //!< offset for User Group 3
    QS_USER4 = (enum_t)QS_USER3 + 5  //!< offset for User Group 4
};

//! QS ID offsets for QS_LOC_FILTER()
enum QSpyIdOffsets {
    QS_AO_ID = 0,  //!< offset for AO priorities
    QS_EP_ID = 64, //!< offset for event-pool IDs
    QS_EQ_ID = 80, //!< offset for event-queue IDs
    QS_AP_ID = 96  //!< offset for Application-specific IDs
};

//! QS ID groups for QS_LOC_FILTER()
enum QSpyIdGroups {
    QS_ALL_IDS = 0xF0,                    //!< all QS IDs
    QS_AO_IDS  = 0x80 + (enum_t)QS_AO_ID, //!< AO IDs (priorities)
    QS_EP_IDS  = 0x80 + (enum_t)QS_EP_ID, //!< event-pool IDs
    QS_EQ_IDS  = 0x80 + (enum_t)QS_EQ_ID, //!< event-queue IDs
    QS_AP_IDS  = 0x80 + (enum_t)QS_AP_ID  //!< Application-specific IDs
};

//! @struct QSpyId
typedef struct {
    uint8_t prio;
} QSpyId;

#if (QS_OBJ_PTR_SIZE == 2U)
    typedef uint16_t QSObj;
#elif (QS_OBJ_PTR_SIZE == 4U)
    typedef uint32_t QSObj;
#elif (QS_OBJ_PTR_SIZE == 8U)
    typedef uint64_t QSObj;
#endif //  (QS_OBJ_PTR_SIZE == 8U)

#if (QS_FUN_PTR_SIZE == 2U)
    typedef uint16_t QSFun;
#elif (QS_FUN_PTR_SIZE == 4U)
    typedef uint32_t QSFun;
#elif (QS_FUN_PTR_SIZE == 8U)
    typedef uint64_t QSFun;
#endif //  (QS_FUN_PTR_SIZE == 8U)

//! @static @private @memberof QS
typedef void (* QSpyFunPtr )(void);

#if (QS_CTR_SIZE == 1U)
    typedef uint8_t QSCtr;
#elif (QS_CTR_SIZE == 2U)
    typedef uint16_t QSCtr;
#elif (QS_CTR_SIZE == 4U)
    typedef uint32_t QSCtr;
#endif //  (QS_CTR_SIZE == 4U)

#if (QS_TIME_SIZE == 2U)
    typedef uint16_t QSTimeCtr;
#elif (QS_TIME_SIZE == 4U)
    typedef uint32_t QSTimeCtr;
#endif //  (QS_TIME_SIZE == 4U)

//============================================================================
#define QS_INIT(arg_)        (QS_onStartup(arg_))
#define QS_EXIT()            (QS_onCleanup())
#define QS_OUTPUT()          (QS_output())
#define QS_RX_INPUT()        (QS_rx_input())
#define QS_GLB_FILTER(rec_)  (QS_glbFilter_((int_fast16_t)(rec_)))
#define QS_LOC_FILTER(qsId_) (QS_locFilter_((int_fast16_t)(qsId_)))
#define QS_FLUSH()           (QS_onFlush())

#define QS_BEGIN_ID(rec_, qsId_) \
if (QS_GLB_CHECK_(rec_) && QS_LOC_CHECK_(qsId_)) { \
    QS_CRIT_STAT \
    QS_CRIT_ENTRY(); \
    QS_beginRec_((uint_fast8_t)(rec_)); \
    QS_TIME_PRE(); {

#define QS_END() } \
    QS_endRec_(); \
    QS_CRIT_EXIT(); \
}

#define QS_BEGIN_INCRIT(rec_, qsId_) \
if (QS_GLB_CHECK_(rec_) && QS_LOC_CHECK_(qsId_)) { \
    QS_beginRec_((uint_fast8_t)(rec_)); \
    QS_TIME_PRE(); {

#define QS_END_INCRIT() } \
    QS_endRec_(); \
}

#define QS_GLB_CHECK_(rec_) \
    (((uint_fast8_t)QS_filt_.glb[(uint_fast8_t)(rec_) >> 3U] \
          & ((uint_fast8_t)1U << ((uint_fast8_t)(rec_) & 7U))) != 0U)

#define QS_LOC_CHECK_(qsId_) \
    (((uint_fast8_t)QS_filt_.loc[(uint_fast8_t)(qsId_) >> 3U] \
          & ((uint_fast8_t)1U << ((uint_fast8_t)(qsId_) & 7U))) != 0U)

#ifndef QS_REC_DONE
    #define QS_REC_DONE() ((void)0)
#endif // ndef QS_REC_DONE

#define QS_I8(width_, data_) \
    (QS_u8_fmt_((uint8_t)(((width_) << 4U) & 0x7U) | (uint8_t)QS_I8_ENUM_T, \
                (data_)))

#define QS_U8(width_, data_) \
    (QS_u8_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_U8_T, (data_)))

#define QS_I16(width_, data_) \
    (QS_u16_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_I16_T, (data_)))

#define QS_U16(width_, data_) \
    (QS_u16_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_U16_T, (data_)))

#define QS_I32(width_, data_) \
    (QS_u32_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_I32_T, (data_)))

#define QS_U32(width_, data_) \
    (QS_u32_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_U32_T, (data_)))

#define QS_I64(width_, data_) \
    (QS_u64_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_I64_T, (data_)))

#define QS_U64(width_, data_) \
    (QS_u64_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_U64_T, (data_)))

#define QS_F32(width_, data_) \
    (QS_f32_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_F32_T, (data_)))

#define QS_F64(width_, data_) \
    (QS_f64_fmt_((uint8_t)(((width_) << 4)) | (uint8_t)QS_F64_T, (data_)))

#define QS_STR(str_) (QS_str_fmt_((str_)))

#define QS_MEM(mem_, size_) (QS_mem_fmt_((mem_), (size_)))

#define QS_ENUM(group_, value_) \
    (QS_u8_fmt_((uint8_t)(0x80U | ((group_) << 4U)) | (uint8_t)QS_I8_ENUM_T,\
                (uint8_t)(value_)))

#if (QS_TIME_SIZE == 2U)
    #define QS_TIME_PRE() (QS_u16_raw_(QS_onGetTime()))
#elif (QS_TIME_SIZE == 4U)
    #define QS_TIME_PRE() (QS_u32_raw_(QS_onGetTime()))
#endif //  (QS_TIME_SIZE == 4U)

#if (QS_OBJ_PTR_SIZE == 2U)
    #define QS_OBJ(obj_) (QS_u16_fmt_(QS_OBJ_T, (uint16_t)(obj_)))
#elif (QS_OBJ_PTR_SIZE == 4U)
    #define QS_OBJ(obj_) (QS_u32_fmt_(QS_OBJ_T, (uint32_t)(obj_)))
#elif (QS_OBJ_PTR_SIZE == 8U)
    #define QS_OBJ(obj_) (QS_u64_fmt_(QS_OBJ_T, (uint64_t)(obj_)))
#endif // (QS_OBJ_PTR_SIZE == 8U)

#if (QS_FUN_PTR_SIZE == 2U)
    #define QS_FUN(fun_) (QS_u16_fmt_(QS_FUN_T, (uint16_t)(fun_)))
#elif (QS_FUN_PTR_SIZE == 4U)
    #define QS_FUN(fun_) (QS_u32_fmt_(QS_FUN_T, (uint32_t)(fun_)))
#elif (QS_FUN_PTR_SIZE == 8U)
    #define QS_FUN(fun_) (QS_u64_fmt_(QS_FUN_T, (uint64_t)(fun_)))
#endif // (QS_FUN_PTR_SIZE == 8U)

#if (Q_SIGNAL_SIZE == 1U)
    #define QS_SIG(sig_, obj_) \
            QS_u8_fmt_(QS_SIG_T, (sig_)); \
            QS_obj_raw_(obj_)
#elif (Q_SIGNAL_SIZE == 2U)
    #define QS_SIG(sig_, obj_) \
            QS_u16_fmt_(QS_SIG_T, (sig_)); \
            QS_obj_raw_(obj_)
#elif (Q_SIGNAL_SIZE == 4U)
    #define QS_SIG(sig_, obj_) \
            QS_u32_fmt_(QS_SIG_T, (sig_)); \
            QS_obj_raw_(obj_)
#endif //  (Q_SIGNAL_SIZE == 4U)

#define QS_SIG_DICTIONARY(sig_, obj_) \
    (QS_sig_dict_pre_((QSignal)(sig_), (obj_), #sig_))

#define QS_OBJ_DICTIONARY(obj_) \
    (QS_obj_dict_pre_((obj_), #obj_))

#define QS_OBJ_ARR_DICTIONARY(obj_, idx_) \
    (QS_obj_arr_dict_pre_((obj_), (idx_), #obj_))

#define QS_FUN_DICTIONARY(fun_) \
    (QS_fun_dict_pre_((void (*)(void))(fun_), #fun_))

#define QS_USR_DICTIONARY(rec_) \
    (QS_usr_dict_pre_((rec_), #rec_))

#define QS_ENUM_DICTIONARY(value_, group_) \
    (QS_enum_dict_pre_((value_), (group_), #value_))

#define QS_RX_PUT(b_) (QS_rxPut((b_)))

#define QS_TR_CRIT_ENTRY()
#define QS_TR_CRIT_EXIT()

#define QS_TR_ISR_ENTRY(isrnest_, prio_) do { \
    QS_BEGIN_PRE(QS_QF_ISR_ENTRY, 0U)         \
        QS_TIME_PRE();                        \
        QS_2u8_raw_((isrnest_), (prio_));     \
    QS_END_PRE()                              \
}

void QS_TR_ISR_EXIT(
    uint_fast8_t isrnest,
    uint_fast8_t prio);

#define QS_ONLY(code_) (code_)

#define QS_ASSERTION(module_, id_, delay_) \
    (QS_assertion_pre_((module_), (id_), (delay_)))

#ifndef QS_NFLOAT_T
    typedef float float32_t;
    typedef double float64_t;
#endif

#define QS_EOD     ((uint16_t)0xFFFFU)
#define QS_CMD     ((uint8_t)7U)
#define QS_HEX_FMT ((uint8_t)0x0FU)

//============================================================================
#ifndef QS_CRIT_STAT
    #define QS_CRIT_STAT QF_CRIT_STAT
#endif // ndef QS_CRIT_STAT

#ifndef QS_CRIT_ENTRY
    #define QS_CRIT_ENTRY() QF_CRIT_ENTRY()
#endif // ndef QS_CRIT_ENTRY

#ifndef QS_CRIT_EXIT
    #define QS_CRIT_EXIT() QF_CRIT_EXIT()
#endif // ndef QS_CRIT_EXIT

#if defined(QS_MEM_SYS) || defined(QS_MEM_APP)
    #error Memory isolation not supported in this QP edition, need SafeQP
#endif

//============================================================================
//============================================================================
#ifdef Q_UTEST

//============================================================================
// QP-stub for QUTest
// NOTE: The QP-stub is needed for unit testing QP applications,
// but might NOT be needed for testing QP itself.
#if (Q_UTEST != 0)

//----------------------------------------------------------------------------
// critical section for QP-stub...
typedef uint_fast8_t QCritStatus;
QCritStatus QF_critEntry(void);
void QF_critExit(QCritStatus critStat);

//----------------------------------------------------------------------------
// scheduler locking for QP-stub...
typedef uint_fast8_t QSchedStatus;
QSchedStatus QF_schedLock(uint_fast8_t const ceiling);
void QF_schedUnlock(QSchedStatus const prevCeil);

//----------------------------------------------------------------------------
//! @class QHsmDummy
//! @extends QAsm
typedef struct {
    QAsm super; //!< @protected @memberof QHsmDummy
} QHsmDummy;

//! @public @memberof QHsmDummy
void QHsmDummy_ctor(QHsmDummy * const me);

//! @private @memberof QHsmDummy
void QHsmDummy_init_(
    QAsm * const me,
    void const * const par,
    uint_fast8_t const qsId);

//! @private @memberof QHsmDummy
void QHsmDummy_dispatch_(
    QAsm * const me,
    QEvt const * const e,
    uint_fast8_t const qsId);

//! @private @memberof QHsmDummy
bool QHsmDummy_isIn_(
    QAsm * const me,
    QStateHandler const state);

QStateHandler QHsmDummy_getStateHandler_(QAsm * const me);

//----------------------------------------------------------------------------
//! @class QActiveDummy
//! @extends QActive
typedef struct {
    QActive super; //!< @protected @memberof QActiveDummy
} QActiveDummy;

//! @public @memberof QActiveDummy
void QActiveDummy_ctor(QActiveDummy * const me);

//! @private @memberof QActiveDummy
void QActiveDummy_init_(
    QAsm * const me,
    void const * const par,
    uint_fast8_t const qsId);

//! @private @memberof QActiveDummy
void QActiveDummy_dispatch_(
    QAsm * const me,
    QEvt const * const e,
    uint_fast8_t const qsId);

//! @private @memberof QActiveDummy
bool QActiveDummy_fakePost_(
    QActive * const me,
    QEvt const * const e,
    uint_fast16_t const margin,
    void const * const sender);

//! @private @memberof QActiveDummy
void QActiveDummy_fakePostLIFO_(
    QActive * const me,
    QEvt const * const e);

#endif // Q_UTEST != 0

//----------------------------------------------------------------------------
#define QS_TEST_PROBE_DEF(fun_) \
    uint32_t const qs_tp_ = QS_getTestProbe_((void (*)(void))(fun_));

#define QS_TEST_PROBE(code_) \
    if (qs_tp_ != 0U) { code_ }

#define QS_TEST_PROBE_ID(id_, code_) \
    if (qs_tp_ == (uint32_t)(id_)) { code_ }

#define QS_TEST_PAUSE()  (QS_test_pause_())

#else // Q_UTEST not defined

// dummy definitions when not building for QUTEST
#define QS_TEST_PROBE_DEF(fun_)
#define QS_TEST_PROBE(code_)
#define QS_TEST_PROBE_ID(id_, code_)
#define QS_TEST_PAUSE()  ((void)0)

#endif // Q_UTEST

//============================================================================

//----------------------------------------------------------------------------
//! @struct QS_Filter
typedef struct {
    uint8_t glb[16];
    uint8_t loc[16];
} QS_Filter;

//! @static @private @memberof QS
extern QS_Filter QS_filt_;

typedef struct {
    uint8_t         *buf;
    QSCtr            end;
    QSCtr   volatile head;
    QSCtr   volatile tail;
    QSCtr   volatile used;
    uint8_t volatile seq;
    uint8_t volatile chksum;
    uint8_t volatile critNest;
    uint8_t          flags;
} QS_Attr;

extern QS_Attr QS_priv_;

void QS_glbFilter_(int_fast16_t const filter);
void QS_locFilter_(int_fast16_t const filter);

void QS_beginRec_(uint_fast8_t const rec);
void QS_endRec_(void);

void QS_u8_raw_(uint8_t const d);
void QS_2u8_raw_(uint8_t const d1, uint8_t const d2);
void QS_u16_raw_(uint16_t const d);
void QS_u32_raw_(uint32_t const d);
void QS_u64_raw_(uint64_t const d);
void QS_obj_raw_(void const * const obj);
void QS_str_raw_(char const * const str);

void QS_u8_fmt_(uint8_t const format, uint8_t const d);
void QS_u16_fmt_(uint8_t const format, uint16_t const d);
void QS_u32_fmt_(uint8_t const format, uint32_t const d);
void QS_u64_fmt_(uint8_t const format, uint64_t const d);
void QS_f32_fmt_(uint8_t const format, float32_t const f);
void QS_f64_fmt_(uint8_t const format, float64_t const d);
void QS_str_fmt_(char const * const str);
void QS_mem_fmt_(uint8_t const * const blk, uint8_t const size);

void QS_sig_dict_pre_(QSignal const sig, void const * const obj,
    char const * const name);
void QS_obj_dict_pre_(void const * const obj, char const * const name);
void QS_obj_arr_dict_pre_(void const * const obj, uint_fast16_t const idx,
    char const * const name);
void QS_fun_dict_pre_(QSpyFunPtr const fun, char const * const name);
void QS_usr_dict_pre_(enum_t const rec, char const * const name);
void QS_enum_dict_pre_(enum_t const value, uint8_t const group,
    char const * const name);

void QS_assertion_pre_(char const * const module, int_t const id,
    uint32_t const delay);

//! Enumerates data elements for app-specific trace records
enum QS_preType {
    QS_I8_ENUM_T, //!< signed 8-bit integer or enum format
    QS_U8_T,      //!< unsigned 8-bit integer format
    QS_I16_T,     //!< signed 16-bit integer format
    QS_U16_T,     //!< unsigned 16-bit integer format
    QS_I32_T,     //!< signed 32-bit integer format
    QS_U32_T,     //!< unsigned 32-bit integer format
    QS_F32_T,     //!< 32-bit floating point format
    QS_F64_T,     //!< 64-bit floating point format
    QS_STR_T,     //!< zero-terminated ASCII string format
    QS_MEM_T,     //!< up to 255-bytes memory block format
    QS_SIG_T,     //!< event signal format
    QS_OBJ_T,     //!< object pointer format
    QS_FUN_T,     //!< function pointer format
    QS_I64_T,     //!< signed 64-bit integer format
    QS_U64_T      //!< unsigned 64-bit integer format
};

// @struct TProbe
struct QS_TProbe {
    QSFun    addr;
    uint32_t data;
    uint8_t  idx;
};

//! @static @public @memberof QS
void QS_initBuf(
    uint8_t * const sto,
    uint_fast32_t const stoSize);

//! @static @public @memberof QS
uint16_t QS_getByte(void);

//! @static @public @memberof QS
uint8_t const * QS_getBlock(uint16_t * const pNbytes);

//! @static @public @memberof QS
void QS_doOutput(void);

//! @static @public @memberof QS
uint8_t QS_onStartup(void const * arg);

//! @static @public @memberof QS
void QS_onCleanup(void);

//! @static @public @memberof QS
void QS_onFlush(void);

//! @static @public @memberof QS
QSTimeCtr QS_onGetTime(void);

//! @static @public @memberof QS
void QS_onTestSetup(void);

//! @static @public @memberof QS
void QS_onTestTeardown(void);

//! @static @public @memberof QS
void QS_onTestEvt(QEvt * e);

//! @static @public @memberof QS
void QS_onTestPost(
    void const * sender,
    QActive * recipient,
    QEvt const * e,
    bool status);

//! @static @public @memberof QS
void QS_onTestLoop(void);

#define QUTEST_ON_POST 124
#define QS_RXATTR_SIZE 128U

//----------------------------------------------------------------------------
//! @cond INTERNAL
typedef struct {
    struct QS_TProbe tpBuf[16];
    QPSet     readySet;
    QPSet     readySet_dis;
    QSTimeCtr testTime;
    uint8_t   tpNum;
    uint8_t   intLock;
    uint8_t   lockCeil;
    uint8_t   memProt;
    bool      inTestLoop;
} QSTestAttr;

extern QSTestAttr QS_tstPriv_;

void QS_test_pause_(void);
uint32_t QS_getTestProbe_(QSpyFunPtr const api);

struct QS_RxAttr; // forward declaration

//! @static @private @memberof QS
extern struct QS_RxAttr * const QS_rxPriv_;

//! @endcond
//----------------------------------------------------------------------------
// QS-RX (QS receive channel)

//! @static @public @memberof QS
//! Kinds of objects used in QS-RX
enum QS_QSpyObjKind {
    SM_OBJ,    //!< state machine object
    AO_OBJ,    //!< active object
    MP_OBJ,    //!< event pool object
    EQ_OBJ,    //!< raw queue object
    TE_OBJ,    //!< time event object
    AP_OBJ,    //!< generic Application-specific object
    MAX_OBJ
};

//! @static @public @memberof QS
//! Object combinations for QS-RX
enum QS_OSpyObjComb {
    SM_AO_OBJ = (enum_t)MAX_OBJ //!< combination of SM and AO
};

//! @static @public @memberof QS
void QS_rxInitBuf(
    uint8_t * const sto,
    uint16_t const stoSize);

//! @static @public @memberof QS
bool QS_rxPut(uint8_t const b);

//! @static @public @memberof QS
void QS_rxParse(void);

//! @static @public @memberof QS
void QS_rxParseBuf(uint16_t const len);

//! @static @public @memberof QS
void QS_setCurrObj(
    uint8_t const obj_kind,
    void * const obj_ptr);

//! @static @public @memberof QS
void *QS_getCurrObj(uint8_t const obj_kind);

//! @static @public @memberof QS
uint16_t QS_rxGetNfree(void);

//! @static @public @memberof QS
void QS_doInput(void);

//! @static @public @memberof QS
void QS_onReset(void);

//! @static @public @memberof QS
void QS_onCommand(
    uint8_t cmdId,
    uint32_t param1,
    uint32_t param2,
    uint32_t param3);

    typedef enum {
    QS_TARGET_NO_RESET,
    QS_TARGET_RESET
} QSResetAction;

void QS_target_info_pre_(QSResetAction const act);

#if (defined Q_UTEST) && (Q_UTEST != 0)
void QS_processTestEvts_(void);
#endif // Q_UTEST != 0

#endif // QS_H_
