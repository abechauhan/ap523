#include "wrapper_sched.h"

int sch_alg = 0;
EXPORT_SYMBOL(sch_alg);

bool single_task_running(void)
{
        if (sch_alg == 0)
                return single_task_running_cfs();
        else if (sch_alg == 1)    
                return single_task_running_bfs();
        else /* shouldn't get here */
                return false;
}
EXPORT_SYMBOL(single_task_running);

void __init sched_init(void)
{
        if (sch_alg == 0)
        {
                printk("CFS!!!!!!!!!!!!!!!!!!!\n");
                sched_init_cfs();
                sched_init_bfs();
        }
        if (sch_alg == 1)    
        {       
                printk("BFS!!!!!!!!!!!!!!!!!!!\n");
                sched_init_bfs();
                sched_init_cfs();
        }
}

void update_rq_clock(struct rq *rq)
{
        if (sch_alg == 0)
                update_rq_clock_cfs(rq);
        
        if (sch_alg == 1)
                update_rq_clock_bfs(rq);
}

unsigned long long nr_context_switches(void)
{
        
        if (sch_alg == 0)
                return nr_context_switches_cfs();
        else if (sch_alg == 1)
                return  nr_context_switches_bfs();
        else 
                return -1;
}

unsigned long nr_iowait(void)
{
        
        if (sch_alg == 0)
                return nr_iowait_cfs();
        else if (sch_alg == 1)
                return  nr_iowait_bfs();
        else 
                return -1;
}

unsigned long nr_iowait_cpu(int cpu)
{
        
        if (sch_alg == 0)
                return nr_iowait_cpu_cfs(cpu);
        else if (sch_alg == 1)
                return  nr_iowait_cpu_bfs(cpu);
        else 
                return -1;
}

unsigned long nr_running(void)
{
        
        if (sch_alg == 0)
                return nr_running_cfs();
        else if (sch_alg == 1)
                return  nr_running_bfs();
        else 
                return -1;
}


int idle_cpu(int cpu)
{
        if (sch_alg == 0)
                return idle_cpu_cfs(cpu);
        else
                return idle_cpu_bfs(cpu);
}

void resched_cpu(int cpu)
{
        if (sch_alg == 0)
                resched_cpu_cfs(cpu);
        else
                resched_cpu_bfs(cpu);
}

int sched_fork(unsigned long clone_flags, struct task_struct *p)
{
        
        if (sch_alg == 0)
                return sched_fork_cfs(clone_flags,p);
        else
                return sched_fork_bfs(clone_flags,p);
}


void rt_mutex_setprio(struct task_struct *p, int prio)
{
        if (sch_alg == 0)
                rt_mutex_setprio(p, prio);
        else
                rt_mutex_setprio(p, prio);
}


void normalize_rt_tasks()
{
        if (sch_alg == 0)
                normalize_rt_tasks_cfs();
        else
                normalize_rt_tasks_bfs();
}

void scheduler_tick(void)
{
        
        if (sch_alg == 0)
                scheduler_tick_cfs();
        else
                scheduler_tick_bfs();
}

void init_idle(struct task_struct *idle, int cpu)
{
        if (sch_alg == 0)
        {
                init_idle_cfs(idle, cpu);
                printk("CFS!!!!!!!!!!!!!!!!!!!IDLE\n");
        }
        else 
        {
                init_idle_bfs(idle, cpu);
                printk("BFS!!!!!!!!!!!!!!!!!!!IDLE\n");
        }
}

void wake_up_new_task(struct task_struct *p)
{
        if (sch_alg == 0)
                wake_up_new_task_cfs(p);
        else 
                wake_up_new_task_bfs(p); 
}


void calc_global_load(unsigned long ticks)
{
        if (sch_alg == 0)
                calc_global_load_cfs(ticks);
        else
                calc_global_load_bfs(ticks);
}


void set_user_nice(struct task_struct *p, long nice)
{
        if (sch_alg == 0)
                set_user_nice_cfs(p, nice);
        else
                set_user_nice_bfs(p, nice);
}

int __sched yield_to(struct task_struct *p, bool preempt)
{
        if (sch_alg == 0)
                return yield_to_cfs(p, preempt);
        else
                return yield_to_bfs(p, preempt);
}


void account_system_time(struct task_struct *p, int hardirq_offset,
			 cputime_t cputime, cputime_t cputime_scaled)
{
        if (sch_alg == 0)
                account_system_time_cfs(p, hardirq_offset, cputime, cputime_scaled);
        else
                account_system_time_bfs(p, hardirq_offset, cputime, cputime_scaled);
}


asmlinkage __visible void __sched schedule(void)
{
        if (sch_alg == 0)
                schedule_cfs();
        else
                schedule_bfs();
}
EXPORT_SYMBOL(schedule);

int wake_up_process(struct task_struct *p)
{
        if (sch_alg == 0)
                return wake_up_process_cfs(p);
        else
                return wake_up_process_bfs(p);
}

int wake_up_state(struct task_struct *p, unsigned int state)
{
        if (sch_alg == 0)
                return wake_up_state_cfs(p, state);
        else
                return wake_up_state_bfs(p, state);
}


int default_wake_function(wait_queue_t *curr, unsigned mode, int flags,
                          void *key)
{
        if (sch_alg == 0)
                return default_wake_function_cfs(curr, mode, flags, key);
        else
                return default_wake_function_bfs(curr, mode, flags, key);
}

int __sched _cond_resched(void)
{
        if (sch_alg == 0)
                return _cond_resched_cfs();
        else
                return _cond_resched_bfs();
}
EXPORT_SYMBOL(_cond_resched);

int __cond_resched_lock(spinlock_t *lock)
{
        if (sch_alg == 0)
                return __cond_resched_lock_cfs(lock);
        else
                return __cond_resched_lock_bfs(lock);

}
EXPORT_SYMBOL(__cond_resched_lock);

int __sched __cond_resched_softirq(void)
{
        if (sch_alg == 0)
                return __cond_resched_softirq_cfs();
        else
                return __cond_resched_softirq_bfs();
}
EXPORT_SYMBOL(__cond_resched_softirq);


asmlinkage __visible void schedule_tail(struct task_struct *prev)
{
        if (sch_alg == 0)
                schedule_tail_cfs(prev);
        else
                schedule_tail_bfs(prev);
}

unsigned long long task_sched_runtime(struct task_struct *p)
{
        if (sch_alg == 0)
                return task_sched_runtime_cfs(p);
        else
                return task_sched_runtime_bfs(p);
}


void __sched yield(void)
{
        if (sch_alg == 0)
                yield_cfs();
        else
                yield_bfs();
}
EXPORT_SYMBOL(yield);


/**
 * sys_sched_yield - yield the current processor to other threads.
 *
 * This function yields the current CPU to other tasks. If there are no
 * other threads running on this CPU then this function will return.
 *
 * Return: 0.
 */
SYSCALL_DEFINE0(sched_yield)
{
        if (sch_alg == 0)
                sched_yield_cfs_sys();
        else 
                sched_yield_bfs_sys();
	return 0;
}


void enqueue_task(struct rq *rq, struct task_struct *p, ...)
{
        va_list arguments;
        int flags = 0;

        if (sch_alg == 0)
        {
                va_start(arguments, p);
                flags = va_arg(arguments, int);
                enqueue_task_cfs(rq, p, flags);
        }
        else
                enqueue_task_bfs(rq, p);
}


void __sched schedule_preempt_disabled(void)
{
        if (sch_alg == 0)
                schedule_preempt_disabled_cfs();
        else
                schedule_preempt_disabled_bfs();
}
