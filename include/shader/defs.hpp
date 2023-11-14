
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define _XOPEN_SOURCE 700
#undef _FLT_EVAL_METHOD
#define _FLT_EVAL_METHOD_OPTIMIZED 
// #define _FLT_EVAL_METHOD_INLINE
  
// #pragma STDC CX_LIMITED_RANGE ON
// #pragma STDC FP_CONTRACT ON
#define _XOPEN_REALTIME
#define _POSIX_ASYNC_IO
#define _POSIX_PRIO_IO
#define _POSIX_SYNC_IO
#define	_XOPEN_SHM
#define _POSIX_PRIORITIZED_IO 1
#undef _FLT_ROUNDS_NEAREST
#define _FLT_ROUNDS_ZERO
// #define _POSIX_REGEXP

// #pragma pack(4)
// #pragma fenv_access(on)             // enable environment sensitivity

// #pragma float_control(precise, on)  // enable precise semantics
// #pragma float_control(except, on)   // enable exception semantics
