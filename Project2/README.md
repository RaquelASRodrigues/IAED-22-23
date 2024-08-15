# Projecto 2 - IAED 2022/2023

## Enunciado

O enunciado do projecto está disponível em [enunciado.md](enunciado.md). 

## Data de entrega: 14 de abril de 2023, às 19h59

Informações detalhadas sobre o processo de submissão estão disponíveis em [informacoes.md](informacoes.md).



# Evaluation

2023-04-13T19:33:00

## Test 1: [+ Accepted+].
## Test 2: [+ Accepted+].
## Test 3: [+ Accepted+].
## Test 4: [+ Accepted+].
## Test 5: [+ Accepted+].
## Test 6: [+ Accepted+].
## Test 7: [+ Accepted+].
## Test 8: [+ Accepted+].
## Test 9: [+ Accepted+].
## Test 10: [+ Accepted+].
## Test 11: [+ Accepted+].
## Test 12: [+ Accepted+].
## Test 13: [+ Accepted+].
## Test 14: [+ Accepted+].
## Test 15: [+ Accepted+].
## Test 16: [+ Accepted+].
## Test 17: [+ Accepted+].
## Test 18: [+ Accepted+].
## Test 19: [+ Accepted+].
## Test 20: [+ Accepted+].
## Test 21: [+ Accepted+].
## Test 22: [+ Accepted+].
## Test 23: [+ Accepted+].
## Test 24: [+ Accepted+].
## Test 25: [- Wrong Answer-].


## Test 26: [- Wrong Answer-].


## Test 27: [+ Accepted+].
## Test 28: [+ Accepted+].
## Test 29: [+ Accepted+].
## Test 30: [+ Accepted+].
## Test 31: [+ Accepted+].
## Test 32: [+ Accepted+].


## Number of passed tests: 30/32


## Valgrind Output:


```
==31246== Memcheck, a memory error detector
==31246== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==31246== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==31246== Command: ./proj.out
==31246== 
==31246== Invalid read of size 8
==31246==    at 0x10A557: elimina_paragem_carreiras (paragens.c:164)
==31246==    by 0x10A557: elimina_paragem (paragens.c:182)
==31246==    by 0x10AEFD: comando_e (project2.c:160)
==31246==    by 0x1091F2: main (project2.c:199)
==31246==  Address 0x4b98810 is 0 bytes after a block of size 16 alloc'd
==31246==    at 0x4837D7B: realloc (vg_replace_malloc.c:826)
==31246==    by 0x1094C8: remove_carreira_paragem (carreiras.c:83)
==31246==    by 0x10A452: elimina_paragem_unica_ligacao (paragens.c:72)
==31246==    by 0x10A452: elimina_paragem_ligacoes (paragens.c:130)
==31246==    by 0x10A563: elimina_paragem_carreiras (paragens.c:164)
==31246==    by 0x10A563: elimina_paragem (paragens.c:182)
==31246==    by 0x10AEFD: comando_e (project2.c:160)
==31246==    by 0x1091F2: main (project2.c:199)
==31246== 
==31246== Invalid read of size 8
==31246==    at 0x1098C0: pesquisa_paragem_carreira (carreiras.c:168)
==31246==    by 0x10A31E: elimina_paragem_ligacoes (paragens.c:126)
==31246==    by 0x10A563: elimina_paragem_carreiras (paragens.c:164)
==31246==    by 0x10A563: elimina_paragem (paragens.c:182)
==31246==    by 0x10AEFD: comando_e (project2.c:160)
==31246==    by 0x1091F2: main (project2.c:199)
==31246==  Address 0x18 is not stack'd, malloc'd or (recently) free'd
==31246== 
==31246== 
==31246== Process terminating with default action of signal 11 (SIGSEGV)
==31246==  Access not within mapped region at address 0x18
==31246==    at 0x1098C0: pesquisa_paragem_carreira (carreiras.c:168)
==31246==    by 0x10A31E: elimina_paragem_ligacoes (paragens.c:126)
==31246==    by 0x10A563: elimina_paragem_carreiras (paragens.c:164)
==31246==    by 0x10A563: elimina_paragem (paragens.c:182)
==31246==    by 0x10AEFD: comando_e (project2.c:160)
==31246==    by 0x1091F2: main (project2.c:199)
==31246==  If you believe this happened as a result of a stack
==31246==  overflow in your program's main thread (unlikely but
==31246==  possible), you can try to increase the size of the
==31246==  main thread stack using the --main-stacksize= flag.
==31246==  The main thread stack size used in this run was 8388608.
==31246== 
==31246== HEAP SUMMARY:
==31246==     in use at exit: 522 bytes in 20 blocks
==31246==   total heap usage: 158 allocs, 138 frees, 11,496 bytes allocated
==31246== 
==31246== LEAK SUMMARY:
==31246==    definitely lost: 0 bytes in 0 blocks
==31246==    indirectly lost: 0 bytes in 0 blocks
==31246==      possibly lost: 0 bytes in 0 blocks
==31246==    still reachable: 522 bytes in 20 blocks
==31246==         suppressed: 0 bytes in 0 blocks
==31246== Rerun with --leak-check=full to see details of leaked memory
==31246== 
==31246== For counts of detected and suppressed errors, rerun with: -v
==31246== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

```


Your code will not be reevaluated if you submit before 2023-04-13 19:43:00 @ Lisbon, Portugal. You need to wait 10 minute(s).

