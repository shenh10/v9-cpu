## Lab2 Report

##### 实验需求：实现二级页表

##### Solution:
建立二级页表的过程在os2.c中已经实现。现分析主要代码
``` c
char pg_mem[6 * 4096]; // page dir + 4 entries + alignment　24KB
setup_paging()
{
  int i;

  pg_dir = (int *)((((int)&pg_mem) + 4095) & -4096); // 分配　页目录起始地址。若pg_mem从０开始，pg_dir = 4096
  pg0 = pg_dir + 1024; //　第一张页表起始地址
  pg1 = pg0 + 1024;　//第二张页表起始地址
  pg2 = pg1 + 1024;
  pg3 = pg2 + 1024;

  pg_dir[0] = (int)pg0 | PTE_P | PTE_W | PTE_U;  // 映射页表起始地址到页目录列表：　页表地址　＋ 页表标记位　Present, Writable, User 
  pg_dir[1] = (int)pg1 | PTE_P | PTE_W | PTE_U;
  pg_dir[2] = (int)pg2 | PTE_P | PTE_W | PTE_U;
  pg_dir[3] = (int)pg3 | PTE_P | PTE_W | PTE_U;
  for (i=4;i<1024;i++) pg_dir[i] = 0;

  for (i=0;i<4096;i++) pg0[i] = (i<<12) | PTE_P | PTE_W | PTE_U;  // 初始化从pg0~pg1，每张页表表项包括 地址和3个标记位（0～12位为标记位，13~32可存地址）

  pdir(pg_dir); 设置页目录表起始地址为pg_dir数组首地址
  spage(1); 使能页机制
}


```

之后页表便能正常访问了。两个错误的访问方式会导致CPU报错（内存地址访问超出页表地址）
```
 t = *(int *)(50<<12);
  printf("...ok\n");

  printf("test page fault write...");
  *(int *)(50<<12) = 5;

```