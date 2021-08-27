#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

#define MAXCHILDREN 11
#define true 1

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int 
sys_count_num_of_digits(void)
{
  int inp = (int)myproc()->tf->edx;
  int res = count_num_of_digits();
  cprintf("Number of digits of %d is %d\n", inp, res);
  return res; 
}

int sys_set_path(void) {
  set_path();
  return 0;
}

int sys_get_parent_id(void) {
  int parentID = get_parent_id();
  // cprintf("Parent id is : %d\n", parentID);
  return parentID;
}

int sys_get_children(void) {
  children = 0;
  int inPid = (int)myproc()->tf->edx;
  children = get_children(inPid);
  return children;
}

int sys_sleep_tick(void) {
  struct rtcdate dateNTime;

  int secsToWait, firstClock, curClock, finalSec, finalMin, beginSec, beginMin;

  secsToWait = (int)(myproc()->tf->edx);

  firstClock = sys_uptime();
  cprintf("Starting to wait...\n");
  cmostime(&dateNTime);
  beginSec = dateNTime.second;
  beginMin = dateNTime.minute;
  while (true) {
    curClock = sys_uptime();
    if (curClock - firstClock >= (secsToWait * 100))
      break;
  }
  cmostime(&dateNTime);
  finalSec = dateNTime.second;
  finalMin = dateNTime.minute;
  int minutesPast, secondsPast;
  minutesPast = finalMin - beginMin;
  secondsPast = finalSec - beginSec;
  if (finalSec < beginSec) {
      secondsPast += 60;
      minutesPast -= 1;
  }
  cprintf("Mitunes past is : %d\n", minutesPast);
  cprintf("Seconds past is : %d\n", secondsPast);
  return 0;
}