gcc -march=x86-64 -O3 -std=gnu11 -o lassi main.c parsekey.c print.c initialize.c structure.c energy.c cluster.c mcmove.c -lm

gcc -march=x86-64 -O0 -g3 -std=gnu11 -o lassi_gdb main.c parsekey.c print.c initialize.c structure.c energy.c cluster.c mcmove.c -lm

