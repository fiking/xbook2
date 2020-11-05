#include <xbook/waitqueue.h>
#include <xbook/task.h>

void wait_queue_add(wait_queue_t *wait_queue, void *task_ptr)
{
    task_t *task = (task_t *) task_ptr;
    unsigned long flags;
    spin_lock_irqsave(&wait_queue->lock, flags);
	ASSERT(!list_find(&task->list, &wait_queue->wait_list));
	list_add_tail(&task->list, &wait_queue->wait_list);
    spin_unlock_irqrestore(&wait_queue->lock, flags);
}
void wait_queue_remove(wait_queue_t *wait_queue, void *task_ptr)
{
    task_t *task = (task_t *) task_ptr;
    unsigned long flags;
    spin_lock_irqsave(&wait_queue->lock, flags);
	task_t *target, *next;
	list_for_each_owner_safe (target, next, &wait_queue->wait_list, list) {
		if (target == task) {
			list_del_init(&target->list);
			break;
		}
	}
    spin_unlock_irqrestore(&wait_queue->lock, flags);
}

void wait_queue_wakeup(wait_queue_t *wait_queue)
{
    unsigned long flags;
    spin_lock_irqsave(&wait_queue->lock, flags);
	if (!list_empty(&wait_queue->wait_list)) {
        task_t *task = list_first_owner(&wait_queue->wait_list, task_t, list);
		list_del(&task->list);
		task_wakeup(task);
    }
    spin_unlock_irqrestore(&wait_queue->lock, flags);
}

void wait_queue_wakeup_all(wait_queue_t *wait_queue)
{
    unsigned long flags;
    spin_lock_irqsave(&wait_queue->lock, flags);
    task_t *task, *next;
    list_for_each_owner_safe (task, next, &wait_queue->wait_list, list) {
		list_del(&task->list);
		task_wakeup(task);
    }
    spin_unlock_irqrestore(&wait_queue->lock, flags);
}
