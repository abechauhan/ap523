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
                sched_init_cfs();
        if (sch_alg == 1)    
                sched_init_bfs();
}

void update_rq_clock(struct rq *rq)
{
        if (sch_alg == 0)
                update_rq_clock_cfs(rq);
        
        if (sch_alg == 1)
                update_rq_clock_bfs(rq);
}
