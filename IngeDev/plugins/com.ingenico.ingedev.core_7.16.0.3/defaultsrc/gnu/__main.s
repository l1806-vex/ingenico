@ __main function to perform the R/W and ZI data initialization and stack initialization    
    .code 32
    
    .global __main
    .type   __main, %function

__main:
    @ C++ static constructors initialization
    ldr r4, =start_ctors
    ldr r5, =end_ctors
    bl test

start:
    @ load the address of the first constructors initialization
    ldr r6, [r4]
    @ Save registers
    stmdb sp!,{r4-r5}	@ Push r4 & r5
    @ Save pc before branching
    mov lr, pc
    add lr, lr, #0x4
    @ branch to initialization
    bx r6
    @ Restore registers
    ldmia sp!,{r4-r5}	@ Pop r4 & r5
    @ put the pointer to the next constructors initialization
    add r4, r4, #0x4

test:
    @ Compare start_ctors with end_ctors addresses to know if
    @ initialization must be done
    cmp r4, r5
    blne start
    
    @ Start application (entry point)
    ldr    r0, Entry_Point
    bx    r0

Entry_Point:
    .word    ApplicationMain

    .end
