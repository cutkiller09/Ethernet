;**************************************************************
; FUNCTION : interrupt handlers table, boot the target        *
;                                                             *
; ENVIRONMENT : PPC5554                                       *
;**************************************************************

        .file "cpu_lb.s"
        .section .text

.equ INTC_CPR, 0xfff48008

;**************************************************************
; Global function : InitializeL1Cache                         *
;**************************************************************
        .global InitializeL1Cache
InitializeL1Cache:
;   * Disable cache function on L1 cache (Set to 0 the bit CE of register L1CSR0)
    msync
    isync    
    lis    r11,0x0000
    ori    r11,r11,0x0000
    mtspr  1010,r11

    blr
    
;**************************************************************
; Global function : InitializeSPEFSCR                         *
;**************************************************************
        .global InitializeSPEFSCR
InitializeSPEFSCR:
;   * Enable Floating Point Exceptions by setting bits 28 of the SPEFSCR to 1
    lis    r11,0x0000
    ori    r11,r11,0x0010
    mfspr  r12,512
    or    r11,r11,r12
    mtspr  512,r11

    blr

;**************************************************************
; Global function : InitializeInternalSRAMFirst32KB           *
;**************************************************************
        .global    InitializeInternalSRAMFirst32KB
InitializeInternalSRAMFirst32KB:
    ; Get the base address of the first 32KB of the L2SRAM, 64-bit word aligned
    lis r11,0x4000
    ori r11,r11,0x0000
    ; Set the loop counter to get first 32KB of L2SRAM
    ; 32KB/4B/32 GPRs = 256
    li r12,256
    mtctr r12

    init_l2ram_loop_first32:
    ; Write all 32 GPRs to L2SRAM
    stmw r0,0(r11)
    ; inc the ram ptr 32 GPRs * 4 bytes = 128
    addi r11,r11,128
    ; loop for 32KB of L2SRAM
    bdnz init_l2ram_loop_first32

    blr

;**************************************************************
; Global function : InitializeDEC                             *
;**************************************************************
        .global InitializeDEC
InitializeDEC:
;   Load initial DEC value with 112M/20 = 0x00557300 to provide a timeout of DEC/System_Clock_Frequency = 50 ms
    lis   r0, 0x0055
    ori   r0, r0, 0x7300
    mtspr 22, r0
;   Load same initial value to DECAR
    mtspr 54, r0
;   Enable DEC interrupt and auto-reload
    lis   r0, 0x0440
    mtspr 340, r0
;   Enable Time Base and Decrementer (set TBEN in HID0)
    li    r0, 0x4000
    mtspr 1008, r0

    blr

;**************************************************************
; Global function : SetPID0                                   *
;**************************************************************
        .global SetPID0
SetPID0:
; r3      a_PID0_value
    ; Set PID0 register (SPR 48) value
   mtspr 48, r3

    blr

;**************************************************************
; Global function : InitializeMMUTlb                          *
;**************************************************************
        .global InitializeMMUTlb
InitializeMMUTlb:
; r3      a_MAS0_register_value
; r4      a_MAS1_register_value
; r5      a_MAS2_register_value
; r6      a_MAS3_register_value

    ; Load MAS0 with the first parameter contains into r3
    mtMAS0 r3

    ; Load MAS1 with the second parameter contains into r4
    mtMAS1 r4

    ; Load MAS2 with the third parameter contains into r5
    mtMAS2 r5

    ; Load MAS3 with the fourth parameter contains into r6
    mtMAS3 r6

    ; Write entry defined in MAS0 to MMU TLB
    tlbwe

    blr

;**************************************************************
; Global function : UnmaskInterruptINTC                       *
;**************************************************************
        .global UnmaskInterruptINTC
UnmaskInterruptINTC:
    ; Load upper half of INTC_CPR address to r4
    lis r4, INTC_CPR@ha
    ; Restore the INTC_CPR saved value (r17 register) into INTC CPR register
    stw r17, INTC_CPR@l(r4)

    blr

;**************************************************************
; Global function : MaskInterruptINTC                         *
;**************************************************************
        .global MaskInterruptINTC
MaskInterruptINTC:
    ; Load upper half of INTC_CPR address to r4
    lis r4, INTC_CPR@ha
    ; Save the INTC_CPR current value into the r17 register
    lwz r17, INTC_CPR@l(r4)
    li r0, 0xF
    ; Write 0xF to INTC_CPR
    stw r0, INTC_CPR@l(r4)

    blr

;**************************************************************
; Global function : UnmaskInterrupt                           *
;**************************************************************
        .global UnmaskInterrupt
UnmaskInterrupt:
    ; Enable external interrupts (INTC, DEC, FIT)
    wrteei 1
    blr


;**************************************************************
; Global function : Waitus                                    *
;**************************************************************
        .global Waitus
Waitus:
    ;   r3      a_time_in_us
    ;   With a clock to 112MHz, performing 31 nop operations lasts 1 us
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop                
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop                
    nop
    nop
    nop
    nop
    nop
    nop

    ;   Repeat the delay the number of time expected
    addic.  r3,r3,-1
    ;********************************** WARNING *********************************;
    ; The last nop is set between the addic. and the bne instruction to avoid    ;
    ;  any modification of the execution time in case of the function alignement ;
    ;  change between two software revision                                      ;
    ; Ref. e200z6 PowerPC Core Reference Manual §15.1 and §3.1.2                 ;
    ;********************************** WARNING *********************************;
    nop
    bne     Waitus
    blr
 
;**************************************************************
; Global function : WaitHundredus                             *
;**************************************************************
        .global WaitHundredus
WaitHundredus:
    ;       r3      a_time_in_hundredth_ms
    ;       r11     register used in the 0.1 ms loop

    ; With a clock to 112MHz, performing 480 addic operations
    ; lasts 1 hundred us. Wait0 loop does it using r11.
    li      r11,0x1E0
Wait0:
    addic.  r11,r11,-1
    ;********************************** WARNING *********************************;
    ; The last nop is set between the addic. and the bne instruction to avoid    ;
    ;  any modification of the execution time in case of the function alignement ;
    ;  change between two software revision                                      ;
    ; Ref. e200z6 PowerPC Core Reference Manual §15.1 and §3.1.2                 ;
    ;********************************** WARNING *********************************;
    nop
    bne     Wait0

    ; Repeat the delay a_time_in_hundredth_ms times
    addic.  r3,r3,-1
    ;********************************** WARNING *********************************;
    ; The last nop is set between the addic. and the bne instruction to avoid    ;
    ;  any modification of the execution time in case of the function alignement ;
    ;  change between two software revision                                      ;
    ; Ref. e200z6 PowerPC Core Reference Manual §15.1 and §3.1.2                 ;
    ;********************************** WARNING *********************************;
    nop
    bne     WaitHundredus

    blr

 
;**************************************************************
; Global function : GetTime                                   *
;**************************************************************
      .global GetTime
GetTime:
    ; copy TBU to r3
   mfspr r3, 269
    ; copy TBL to r4
   mfspr r4, 268
    blr
