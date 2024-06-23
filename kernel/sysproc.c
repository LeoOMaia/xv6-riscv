#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "pstat.h"
#include "defs.h"

uint64
sys_exit(void)
{
  count_sys[1]++;
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  count_sys[10]++;
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  count_sys[0]++;
  return fork();
}

uint64
sys_wait(void)
{
  count_sys[2]++;
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  count_sys[11]++;
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  count_sys[12]++;
  int n;
  uint ticks0;

  argint(0, &n);
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  count_sys[5]++;
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  count_sys[13]++;
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_settickets(void)
{
    count_sys[22]++;
    int n;
    argint(0, &n);
    // check if the number of tickets is in the range [1, 1000]
    if(n < 1 || n > 1000)
        return -1;
    settickets(n);
    return 0;
}

uint64
sys_getpinfo(void)
{
    count_sys[23]++;
    uint64 addr;
    argaddr(0, &addr);
    if (addr<0)
        return -1;
    return getpinfo(&addr);
}
