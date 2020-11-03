#include <xbook/memcache.h>
#include <xbook/debug.h>
#include <xbook/hardirq.h>
#include <xbook/softirq.h>
#include <xbook/clock.h>
#include <xbook/virmem.h>
#include <xbook/task.h>
#include <xbook/rawblock.h>
#include <xbook/schedule.h>
#include <xbook/sharemem.h>
#include <xbook/msgqueue.h>
#include <xbook/sem.h>
#include <xbook/syscall.h>
#include <xbook/fifo.h>
#include <xbook/driver.h>
#include <xbook/ktime.h>
#include <xbook/srvcall.h>
#include <xbook/fs.h>
#include <xbook/net.h>
#include <xbook/gui.h>
#include <xbook/timer.h>

int kernel_main(void)
{
    printk(KERN_INFO "welcome to xbook kernel.\n");
    mem_caches_init();
    vir_mem_init();
    irq_description_init();
    softirq_init();
    share_mem_init();
    msg_queue_init();
    sem_init();
    fifo_fifo();
    init_syscall();
    init_srvcall();
    init_ktime();
    init_tasks();
    init_clock();
    init_timer_system();
    interrupt_enable();
    init_driver_arch();
    init_fs();
    init_gui();
    init_net();
    
    start_user();
    return 0;    
}
