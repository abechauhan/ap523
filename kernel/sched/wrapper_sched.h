#include "sched.h" 
#include "bfs_sched.h"
#include <linux/module.h>
#include <linux/syscalls.h>
#ifndef WRAPPER_SCHED_H
#define WRAPPER_SCHED_H

bool single_task_running(void);
bool single_task_running_bfs(void);
bool single_task_running_cfs(void);

void __init sched_init(void);
void __init sched_init_bfs(void);
void __init sched_init_cfs(void);


void update_rq_clock(struct rq *rq);
void update_rq_clock_bfs(struct rq *rq);
void update_rq_clock_cfs(struct rq *rq);

unsigned long long nr_context_switches(void);
unsigned long long nr_context_switches_bfs(void);
unsigned long long nr_context_switches_cfs(void);
unsigned long nr_iowait(void);
unsigned long nr_iowait_bfs(void);
unsigned long nr_iowait_cfs(void);
unsigned long nr_iowait_cpu(int cpu);
unsigned long nr_iowait_cpu_bfs(int cpu);
unsigned long nr_iowait_cpu_cfs(int cpu);
unsigned long nr_running(void);
unsigned long nr_running_bfs(void);
unsigned long nr_running_cfs(void);

int idle_cpu(int cpu);
int idle_cpu_bfs(int cpu);
int idle_cpu_cfs(int cpu);

void account_steal_ticks_bfs(unsigned long ticks);

int sched_fork(unsigned long clone_flags, struct task_struct *p);
int sched_fork_bfs(unsigned long clone_flags, struct task_struct *p);
int sched_fork_cfs(unsigned long clone_flags, struct task_struct *p);

void resched_cpu(int cpu);
void resched_cpu_bfs(int cpu);
void resched_cpu_cfs(int cpu);

void rt_mutex_setprio(struct task_struct *p, int prio);
void rt_mutex_setprio_bfs(struct task_struct *p, int prio);
void rt_mutex_setprio_cfs(struct task_struct *p, int prio);

void normalize_rt_tasks(void);
void normalize_rt_tasks_bfs(void);
void normalize_rt_tasks_cfs(void);

void scheduler_tick(void);
void scheduler_tick_bfs(void);
void scheduler_tick_cfs(void);

void init_idle(struct task_struct *idle, int cpu);
void init_idle_bfs(struct task_struct *idle, int cpu);
void init_idle_cfs(struct task_struct *idle, int cpu);

void wake_up_new_task(struct task_struct *p);
void wake_up_new_task_bfs(struct task_struct *p);
void wake_up_new_task_cfs(struct task_struct *p);

void calc_global_load(unsigned long ticks);
void calc_global_load_bfs(unsigned long ticks);
void calc_global_load_cfs(unsigned long ticks);


void set_user_nice(struct task_struct *p, long nice);
void set_user_nice_bfs(struct task_struct *p, long nice);
void set_user_nice_cfs(struct task_struct *p, long nice);

int __sched yield_to(struct task_struct *p, bool preempt);
int __sched yield_to_bfs(struct task_struct *p, bool preempt);
int __sched yield_to_cfs(struct task_struct *p, bool preempt);


void account_system_time(struct task_struct *p, int hardirq_offset,
			 cputime_t cputime, cputime_t cputime_scaled);
void account_system_time_bfs(struct task_struct *p, int hardirq_offset,
			 cputime_t cputime, cputime_t cputime_scaled);
void account_system_time_cfs(struct task_struct *p, int hardirq_offset,
			 cputime_t cputime, cputime_t cputime_scaled);


asmlinkage __visible void __sched schedule(void);
asmlinkage __visible void __sched schedule_cfs(void);
asmlinkage __visible void __sched schedule_bfs(void);

int wake_up_process(struct task_struct *p);
int wake_up_process_bfs(struct task_struct *p);
int wake_up_process_cfs(struct task_struct *p);

int wake_up_state(struct task_struct *p, unsigned int state);
int wake_up_state_bfs(struct task_struct *p, unsigned int state);
int wake_up_state_cfs(struct task_struct *p, unsigned int state);

int default_wake_function(wait_queue_t *curr, unsigned mode, int flags,
                          void *key);
int default_wake_function_bfs(wait_queue_t *curr, unsigned mode, int flags,
                          void *key);
int default_wake_function_cfs(wait_queue_t *curr, unsigned mode, int flags,
                          void *key);


int __sched __cond_resched_softirq(void);
int __cond_resched_lock(spinlock_t *lock);
int __sched _cond_resched(void);


int __sched __cond_resched_softirq_bfs(void);
int __cond_resched_lock_bfs(spinlock_t *lock);
int __sched _cond_resched_bfs(void);


int __sched __cond_resched_softirq_cfs(void);
int __cond_resched_lock_cfs(spinlock_t *lock);
int __sched _cond_resched_cfs(void);


asmlinkage __visible void schedule_tail(struct task_struct *prev);
asmlinkage __visible void schedule_tail_bfs(struct task_struct *prev)
	__releases(grq.lock);
asmlinkage __visible void schedule_tail_cfs(struct task_struct *prev)
	__releases(rq->lock);

        
unsigned long long task_sched_runtime(struct task_struct *p);
unsigned long long task_sched_runtime_bfs(struct task_struct *p);
unsigned long long task_sched_runtime_cfs(struct task_struct *p);

void __sched yield(void);
void __sched yield_bfs(void);
void __sched yield_cfs(void);

extern inline void grq_lock_irq(void);
extern inline void requeue_task(struct task_struct *p);
struct rq *this_rq_lock(void);

void sched_yield_cfs_sys(void);
void sched_yield_bfs_sys(void);


void enqueue_task(struct rq *rq, struct task_struct *p, ...);
void enqueue_task_bfs(struct rq *rq, struct task_struct *p);
void enqueue_task_cfs(struct rq *rq, struct task_struct *p, int flags);

void __sched schedule_preempt_disabled(void);
void __sched schedule_preempt_disabled_bfs(void);
void __sched schedule_preempt_disabled_cfs(void);


asmlinkage __visible void __sched notrace preempt_schedule(void);
asmlinkage __visible void __sched notrace preempt_schedule_bfs(void);
asmlinkage __visible void __sched notrace preempt_schedule_cfs(void);
#endif
