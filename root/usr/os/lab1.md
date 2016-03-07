## Report Lab1
##### 实验要求：在ｖ9-cpu 上实现时钟中断输出，使得运行整个系统，可以看到大约每1秒会输出一次”100 ticks”，而按下的键也会在屏幕上显示。
Solution:
实验代码如下：
1. 同时支持时钟中断和键盘中断：

``` c
/* 首先在主函数注册中断函数入口地址'alltraps'.　中断调用前，将当前ｐｃ值和中断描述符fc入栈，然后cpu从中断向量表ivec中查找函数入口，进入alltraps()函数。由于在调用trap函数之前已将a,b,c寄存器依次入栈。需要的参数都已按顺序入栈，trap可无参调用。
v9cpu定义的中断异常种类有如下11种
enum { // processor fault codes
  FMEM,   // bad physical address
  FTIMER, // timer interrupt
  FKEYBD, // keyboard interrupt
  FPRIV,  // privileged instruction
  FINST,  // illegal instruction
  FSYS,   // software trap
  FARITH, // arithmetic trap
  FIPAGE, // page fault on opcode fetch
  FWPAGE, // page fault on write
  FRPAGE, // page fault on read
  USER=16 // user mode exception 
};

*/
trap(int c, int b, int a, int fc, int pc) 

{
  switch (fc) {
  case FTIMER: current ++ ; break;　// 时钟中断，current计数加一
  case FKEYBD: out(1,in(0)); break; // 键盘中断，输出　“从键盘输入”的字符　到屏幕
  }
}

alltraps()
{
　＃将a,b,c寄存器的值依次入栈，
  asm(PSHA);
  asm(PSHB);
  asm(PSHC);
  trap();
  asm(POPC);
  asm(POPB);
  asm(POPA);
  asm(RTI);
}

```
２. 每１00次时钟中断输出一次'100 ticks'

``` c
# BOUT指令每次输出一个字符到屏幕
print_ticks(){
 out(1, '1');
 out(1, '0');
 out(1, '0');
 out(1, ' ');
 out(1, 't');
 out(1, 'i');
 out(1, 'c');
 out(1, 'k');
 out(1, 's');
 out(1, '\n');
}

main(){
...
       if ( current == 100) {
                print_ticks();
                current = 0;
        }
...

}
```

