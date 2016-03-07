// os0.c -- simple timer isr test

#include <u.h>

int current, last_current;

int in(port)    { asm(LL,8); asm(BIN); }
out(port, val)  { asm(LL,8); asm(LBL,16); asm(BOUT); }
ivec(void *isr) { asm(LL,8); asm(IVEC); }
stmr(int val)   { asm(LL,8); asm(TIME); }
halt(val)       { asm(LL,8); asm(HALT); }
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


trap(int c, int b, int a, int fc, int pc)

{
  switch (fc) {
  case FTIMER: current ++ ; break;
  case FKEYBD: out(1,in(0)); break;
  }
}

alltraps()
{
  asm(PSHA);
  asm(PSHB);
  asm(PSHC);
  trap();
  asm(POPC);
  asm(POPB);
  asm(POPA);
  asm(RTI);
}



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
main()
{
  current = 0;

  stmr(1000000);
  ivec(alltraps);
  
  asm(STI);
 
  while (1) {
	if ( current == 100) {
		print_ticks();
		current = 0;
	}
  }

  halt(0);
}
