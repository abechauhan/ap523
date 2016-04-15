#include "sched.h" 
#include "bfs_sched.h"
#include <linux/module.h>
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
#endif
