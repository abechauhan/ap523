
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/rbtree.h>
#include <linux/list.h>

#include "wrapper_sched.h"

int switch_job_sched = 0;
EXPORT_SYMBOL(switch_job_sched);
int data = 0;
struct task_struct *switch_task = NULL;

#define for_each_sched_entity(se) \
		for (; se; se = se->parent)

void migrate_tasks_bfs(void)
{
	char *p;
	struct rq *rq;
	struct cfs_rq *cfs_rq;
	struct dl_rq *dl_rq;
	struct rt_rq *rt_rq;

	struct rb_node *node;
	struct rb_root *cfs_tree;
	struct rb_root *dl_tree;
	struct task_struct *task;
	
	
	struct sched_entity *entity;
	struct sched_rt_entity *rt_entity;
	struct sched_dl_entity *dl_entity;


	struct rt_prio_array *array;
	struct list_head *rt_head;
	struct list_head *iter;
	//struct plist_head *p_rt_head;
	int idx;

	int cpu;
	p = 0;
	if (switch_job_sched == 1)
	{
		cpu = smp_processor_id();
		rq = cpu_rq(cpu);
		cfs_rq=&(rq->cfs);
		cfs_tree=&(cfs_rq->tasks_timeline);
		
		// CFS Tasks
		for (node = rb_first(cfs_tree); node; node = rb_next(node))
		{
			entity = rb_entry(node, struct sched_entity, run_node);
			for_each_sched_entity(entity) {
				task = container_of(entity, struct task_struct, se);
				if (task)
				{
					//raw_spin_lock(&grq.lock);
					activate_task_bfs(task, rq);
					//raw_spin_unlock(&grq.lock);
				}
			}
		}
		//Add current task
		//raw_spin_lock(&grq.lock);
		activate_task_bfs(current, rq);
		//raw_spin_unlock(&grq.lock);
 		
		rt_rq=&(rq->rt);
		array= &rt_rq->active;
		/*RT Tasks
		idx = sched_find_first_bit(array->bitmap);
		BUG_ON(idx >= MAX_RT_PRIO);*/
		for (idx=0; idx <MAX_RT_PRIO; idx++)
		{
			rt_head = array->queue + idx;
			list_for_each(iter,rt_head)
			{
				rt_entity = list_entry(iter, struct sched_rt_entity, run_list);
				task = container_of(rt_entity, struct task_struct, rt);
				if (task)
				{
					//raw_spin_lock(&grq.lock);
                			activate_task_bfs(task, rq);
					//raw_spin_unlock(&grq.lock);
				}
			}
		}
/*
			p_rt_head = &rq->rt.pushable_tasks;
			if(!plist_head_empty(&rq->rt.pushable_tasks))
				return NULL;

			plist_for_each_entry(task, p_rt_head, pushable_tasks) {
                			activate_task_bfs(task, rq);
					printk(KERN_ALERT "Abhishek [%d]  %s\n",__LINE__,task->comm);
					printk(KERN_ALERT "Abhishek [%d]  %d\n",__LINE__,task->pid);
			}
*/
		//DL Tasks
		dl_rq=&(rq->dl);
		if (dl_rq == NULL)
		  	
		dl_tree=&(dl_rq->rb_root);
		for (node = rb_first(dl_tree); node; node = rb_next(node))
		{
			dl_entity = rb_entry(node, struct sched_dl_entity, rb_node);
			task = container_of(dl_entity, struct task_struct, dl);
			if (task)
			{
				//raw_spin_lock(&grq.lock);
                		activate_task_bfs(task, rq);
				//raw_spin_unlock(&grq.lock);
			}
		}
		switch_job_sched = 0;
	}

}

int switch_thread_function(void *value)
{
	while(!kthread_should_stop())
	{
		if (switch_job_sched == 1)
		{
			preempt_disable();
			sch_alg = 1;
			sched_init_bfs();
			schedule();
		}
		else
		  schedule();
	}
	return 0;
}

void switch_task_init(void)
{
	if (!switch_task)
	{
		switch_task = kthread_run(&switch_thread_function,
				&data, "switcher");
	}
}
