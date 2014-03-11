#include <stdio.h>
#include <math.h>
#include <float.h>

#define PRINT_GPR1(name,i,GPR) printf(name "([%02d]) -> %016llx\n", i, *(unsigned long long*)&GPR);
#define PRINT_GPR2(name,i,j,GPR) printf(name "([%02d],[%02d]) -> %016llx\n", i, j, *(unsigned long long*)&GPR);
#define PRINT_GPR3(name,i,j,k,GPR) printf(name "([%02d],[%02d],[%02d]) -> %016llx\n", i, j, k, *(unsigned long long*)&GPR);

// Loops with 64-bit integers
#define ITERATE1i(x) \
	for (unsigned int i=0; i<sizeof(testInts64)/sizeof(long long); i++) \
		{long long r0, r1=testInts64[i]; x;}

#define ITERATE2i(x) \
	for (unsigned int i=0; i<sizeof(testInts64)/sizeof(long long); i++) \
		for (unsigned int j=0; j<sizeof(testInts64)/sizeof(long long); j++) \
			{long long r0, r1=testInts64[i], r2=testInts64[j]; x;}

long long testInts64[] = {
	0, 1, 2, 3, 4, -1, -2, -3, -4,
	0x0003333300330033LL, 0x000000fffff00000LL, 0x1000000000000000LL, 0x0123456789ABCDEFLL,
	0x1fffffffffffffffLL, 0x4238572200000000LL, 0x7000000000000000LL, 0x0000000072233411LL,
	0x7fffffffffffffffLL, 0x8000000000000000LL, 0x8000000000000001LL, 0x8fffffffffffffffLL,
};

int main(void)
{
	//////////////////////////////
	// PPU INTEGER INSTRUCTIONS //
	//////////////////////////////

	// Integer Arithmetic Instructions (TODO: Add *., *o, *o. instructions)
	ITERATE1i(__asm__ ("addi    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("addi   ",i,0,r0));  // SIMM
	ITERATE1i(__asm__ ("addi    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("addi   ",i,1,r0));  // SIMM
	ITERATE1i(__asm__ ("addi    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(-1));  PRINT_GPR2("addi   ",i,-1,r0)); // SIMM
	ITERATE1i(__asm__ ("addis   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("addis  ",i,0,r0));  // SIMM
	ITERATE1i(__asm__ ("addis   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("addis  ",i,1,r0));  // SIMM
	ITERATE1i(__asm__ ("addis   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(-1));  PRINT_GPR2("addis  ",i,-1,r0)); // SIMM
	ITERATE1i(__asm__ ("addic   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("addic  ",i,0,r0));  // SIMM
	ITERATE1i(__asm__ ("addic   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("addic  ",i,1,r0));  // SIMM
	ITERATE1i(__asm__ ("addic   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(-1));  PRINT_GPR2("addic  ",i,-1,r0)); // SIMM
	ITERATE1i(__asm__ ("subfic  %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("subfic ",i,0,r0));  // SIMM
	ITERATE1i(__asm__ ("subfic  %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("subfic ",i,1,r0));  // SIMM
	ITERATE1i(__asm__ ("subfic  %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(-1));  PRINT_GPR2("subfic ",i,-1,r0)); // SIMM
	ITERATE1i(__asm__ ("mulli   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("mulli  ",i,0,r0));  // SIMM
	ITERATE1i(__asm__ ("mulli   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("mulli  ",i,1,r0));  // SIMM
	ITERATE1i(__asm__ ("mulli   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(-1));  PRINT_GPR2("mulli  ",i,-1,r0)); // SIMM
	ITERATE2i(__asm__ ("add     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("add    ",i,j,r0));
	ITERATE2i(__asm__ ("subf    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("subf   ",i,j,r0));
	ITERATE2i(__asm__ ("addc    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("addc   ",i,j,r0));
	ITERATE2i(__asm__ ("subfc   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("subfc  ",i,j,r0));
	ITERATE2i(__asm__ ("adde    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("adde   ",i,j,r0));
	ITERATE2i(__asm__ ("subfe   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("subfe  ",i,j,r0));
	ITERATE1i(__asm__ ("addme   %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("addme  ",i,r0));
	//ITERATE1i(__asm__ ("subfme  %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("subfme ",i,r0));
	ITERATE1i(__asm__ ("addze   %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("addze  ",i,r0));
	//ITERATE1i(__asm__ ("subfze  %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("subfze ",i,r0));
	ITERATE2i(__asm__ ("mullw   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("mullw  ",i,j,r0));
	ITERATE2i(__asm__ ("mulld   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("mulld  ",i,j,r0));
	ITERATE2i(__asm__ ("mulhw   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("mulhw  ",i,j,r0));
	ITERATE2i(__asm__ ("mulhd   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("mulhd  ",i,j,r0));
	ITERATE2i(__asm__ ("mulhwu  %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("mulhwu ",i,j,r0));
	ITERATE2i(__asm__ ("mulhdu  %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("mulhdu ",i,j,r0));
	ITERATE2i(__asm__ ("divw    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("divw   ",i,j,r0));
	ITERATE2i(__asm__ ("divd    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("divd   ",i,j,r0));
	ITERATE2i(__asm__ ("divwu   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("divwu  ",i,j,r0));
	ITERATE2i(__asm__ ("divdu   %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("divdu  ",i,j,r0));

	// Integer Compare Instructions
	// TODO ?

	// Integer Logical Instructions
	ITERATE1i(__asm__ ("andi.   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));  PRINT_GPR2("andi.  ",i,0,r0)); // UIMM
	ITERATE1i(__asm__ ("andi.   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));  PRINT_GPR2("andi.  ",i,1,r0)); // UIMM
	ITERATE1i(__asm__ ("andi.   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0xffff));  PRINT_GPR2("andi.  ",i,0xffff,r0)); // UIMM
	ITERATE1i(__asm__ ("andis.  %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));  PRINT_GPR2("andis. ",i,0,r0)); // UIMM
	ITERATE1i(__asm__ ("andis.  %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));  PRINT_GPR2("andis. ",i,1,r0)); // UIMM
	ITERATE1i(__asm__ ("andis.  %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0xffff));  PRINT_GPR2("andis. ",i,0xffff,r0)); // UIMM
	ITERATE1i(__asm__ ("ori     %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));  PRINT_GPR2("ori    ",i,0,r0)); // UIMM
	ITERATE1i(__asm__ ("ori     %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));  PRINT_GPR2("ori    ",i,1,r0)); // UIMM
	ITERATE1i(__asm__ ("ori     %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0xffff));  PRINT_GPR2("ori    ",i,0xffff,r0)); // UIMM
	ITERATE1i(__asm__ ("oris    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));  PRINT_GPR2("oris   ",i,0,r0)); // UIMM
	ITERATE1i(__asm__ ("oris    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));  PRINT_GPR2("oris   ",i,1,r0)); // UIMM
	ITERATE1i(__asm__ ("oris    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0xffff));  PRINT_GPR2("oris   ",i,0xffff,r0)); // UIMM
	ITERATE1i(__asm__ ("xori     %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));  PRINT_GPR2("xori  ",i,0,r0)); // UIMM
	ITERATE1i(__asm__ ("xori     %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));  PRINT_GPR2("xori  ",i,1,r0)); // UIMM
	ITERATE1i(__asm__ ("xori     %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0xffff));  PRINT_GPR2("xori  ",i,0xffff,r0)); // UIMM
	ITERATE1i(__asm__ ("xoris    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));  PRINT_GPR2("xoris ",i,0,r0)); // UIMM
	ITERATE1i(__asm__ ("xoris    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));  PRINT_GPR2("xoris ",i,1,r0)); // UIMM
	ITERATE1i(__asm__ ("xoris    %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0xffff));  PRINT_GPR2("xoris ",i,0xffff,r0)); // UIMM
	ITERATE2i(__asm__ ("and     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("add   ",i,j,r0));
	ITERATE2i(__asm__ ("or      %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("or    ",i,j,r0));
	ITERATE2i(__asm__ ("xor     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("xor   ",i,j,r0));
	ITERATE2i(__asm__ ("nand    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("nand  ",i,j,r0));
	ITERATE2i(__asm__ ("nor     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("nor   ",i,j,r0));
	ITERATE2i(__asm__ ("eqv     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("eqv   ",i,j,r0));
	ITERATE2i(__asm__ ("andc    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("andc  ",i,j,r0));
	ITERATE2i(__asm__ ("orc     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("orc   ",i,j,r0));
	ITERATE1i(__asm__ ("extsb   %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("extsb  ",i,r0));
	ITERATE1i(__asm__ ("extsh   %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("extsh  ",i,r0));
	ITERATE1i(__asm__ ("extsw   %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("extsw  ",i,r0));
	ITERATE1i(__asm__ ("cntlzw  %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("cntlzw ",i,r0));
	ITERATE1i(__asm__ ("cntlzd  %0,%1" : "=r"(r0) : "r"(r1));  PRINT_GPR1("cntlzd ",i,r0));

	// Integer Rotate and Shift Instructions (TODO: Add rlwinm, rlwnm, rlwimi)
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(0));   PRINT_GPR3("rldicl ",i,0,0,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(1));   PRINT_GPR3("rldicl ",i,0,1,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(63));  PRINT_GPR3("rldicl ",i,0,63,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(0));   PRINT_GPR3("rldicl ",i,1,0,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(1));   PRINT_GPR3("rldicl ",i,1,1,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(63));  PRINT_GPR3("rldicl ",i,1,63,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(0));  PRINT_GPR3("rldicl ",i,63,0,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(1));  PRINT_GPR3("rldicl ",i,63,1,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldicl  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(63)); PRINT_GPR3("rldicl ",i,63,63,r0)); // SH, MB
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(0));   PRINT_GPR3("rldicr ",i,0,0,r0));   // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(1));   PRINT_GPR3("rldicr ",i,0,1,r0));   // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(63));  PRINT_GPR3("rldicr ",i,0,63,r0));  // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(0));   PRINT_GPR3("rldicr ",i,1,0,r0));   // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(1));   PRINT_GPR3("rldicr ",i,1,1,r0));   // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(63));  PRINT_GPR3("rldicr ",i,1,63,r0));  // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(0));  PRINT_GPR3("rldicr ",i,63,0,r0));  // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(1));  PRINT_GPR3("rldicr ",i,63,1,r0));  // SH, ME
	ITERATE1i(__asm__ ("rldicr  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(63)); PRINT_GPR3("rldicr ",i,63,63,r0)); // SH, ME
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(0));   PRINT_GPR3("rldic ",i,0,0,r0));    // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(1));   PRINT_GPR3("rldic ",i,0,1,r0));    // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(63));  PRINT_GPR3("rldic ",i,0,63,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(0));   PRINT_GPR3("rldic ",i,1,0,r0));    // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(1));   PRINT_GPR3("rldic ",i,1,1,r0));    // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(63));  PRINT_GPR3("rldic ",i,1,63,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(0));  PRINT_GPR3("rldic ",i,63,0,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(1));  PRINT_GPR3("rldic ",i,63,1,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldic   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(63)); PRINT_GPR3("rldic ",i,63,63,r0));  // SH, MB
	ITERATE2i(__asm__ ("rldcl   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "r"(r2), "i"(0));  PRINT_GPR3("rldcl  ",i,j,0,r0));   // ME
	ITERATE2i(__asm__ ("rldcl   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "r"(r2), "i"(1));  PRINT_GPR3("rldcl  ",i,j,1,r0));   // ME
	ITERATE2i(__asm__ ("rldcl   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "r"(r2), "i"(63)); PRINT_GPR3("rldcl  ",i,j,63,r0));  // ME
	ITERATE2i(__asm__ ("rldcr   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "r"(r2), "i"(0));  PRINT_GPR3("rldcr  ",i,j,0,r0));   // ME
	ITERATE2i(__asm__ ("rldcr   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "r"(r2), "i"(1));  PRINT_GPR3("rldcr  ",i,j,1,r0));   // ME
	ITERATE2i(__asm__ ("rldcr   %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "r"(r2), "i"(63)); PRINT_GPR3("rldcr  ",i,j,63,r0));  // ME
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(0));   PRINT_GPR3("rldimi ",i,0,0,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(1));   PRINT_GPR3("rldimi ",i,0,1,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(0), "i"(63));  PRINT_GPR3("rldimi ",i,0,63,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(0));   PRINT_GPR3("rldimi ",i,1,0,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(1));   PRINT_GPR3("rldimi ",i,1,1,r0));   // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(1), "i"(63));  PRINT_GPR3("rldimi ",i,1,63,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(0));  PRINT_GPR3("rldimi ",i,63,0,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(1));  PRINT_GPR3("rldimi ",i,63,1,r0));  // SH, MB
	ITERATE1i(__asm__ ("rldimi  %0,%1,%2,%3" : "=r"(r0) : "r"(r1), "i"(63), "i"(63)); PRINT_GPR3("rldimi ",i,63,63,r0)); // SH, MB
	ITERATE2i(__asm__ ("sld     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("sld    ",i,j,r0));
	ITERATE2i(__asm__ ("slw     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("slw    ",i,j,r0));
	ITERATE2i(__asm__ ("srd     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("srd    ",i,j,r0));
	ITERATE2i(__asm__ ("srw     %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("srw    ",i,j,r0));
	ITERATE1i(__asm__ ("sradi   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("sradi  ",i,0,r0));  // SH
	ITERATE1i(__asm__ ("sradi   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("sradi  ",i,1,r0));  // SH
	ITERATE1i(__asm__ ("sradi   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(63));  PRINT_GPR2("sradi  ",i,63,r0)); // SH
	ITERATE1i(__asm__ ("srawi   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(0));   PRINT_GPR2("srawi  ",i,0,r0));  // SH
	ITERATE1i(__asm__ ("srawi   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(1));   PRINT_GPR2("srawi  ",i,1,r0));  // SH
	ITERATE1i(__asm__ ("srawi   %0,%1,%2" : "=r"(r0) : "r"(r1), "i"(31));  PRINT_GPR2("srawi  ",i,31,r0)); // SH
	ITERATE2i(__asm__ ("srad    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("srad   ",i,j,r0));
	ITERATE2i(__asm__ ("sraw    %0,%1,%2" : "=r"(r0) : "r"(r1), "r"(r2));  PRINT_GPR2("sraw   ",i,j,r0));

	return 0;
}
