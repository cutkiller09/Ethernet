;**************************************************************
; FUNCTION : external interrupt handlers table with prolog    *
;            and epilog macros                                *
;                                                             *
; ENVIRONMENT : PPC5554                                       *
;**************************************************************

        .file    "trap_tab.s"
        .section .text

.equ    INTC_CPR,       0xfff48008
.equ    INTC_IACKR,     0xfff48010
.equ    INTC_EOIR,        0xfff48018
.equ    INTC_SSCIR,     0xfff48020
.equ    ESCIA_CR1_ADDR,   0xFFFB0000
.equ    ESCIA_CR1_115200, 0x003C130C


    ; The followining code of the function shall be mapped into the exception handlers for user mode memory area
        .section .exception_handlers_user_mode, c
        

;**************************************************************
; Local function : launch_c_function                          *
;**************************************************************
        .align 4
launch_c_function:
; r4 shall contain the address of the C function to launch

    ; Create a stack frame of 0x10 bytes
    stwu    r1, -0x10 (r1)
    ; Store the TCR register into the stack frame
    mfspr   r5, 340
    stw     r5,  0xC (r1)     
    
    ; IF the address of the function to launch is included into the Software IT zone address
    lis r3,_SOFTWARE_IT_FUNCTION_ADDR@h
    ori r3,r3,_SOFTWARE_IT_FUNCTION_ADDR@l
    lis r5,_SOFTWARE_IT_FUNCTION_END_ADDR@h
    ori r5,r5,_SOFTWARE_IT_FUNCTION_END_ADDR@l    
    cmplw r3,r4
    bgt do_not_set_BITE_PID_value
    cmplw r5,r4
    blt do_not_set_BITE_PID_value
set_BITE_PID_value:
    ; THEN
        cmplw r3,r4
        bne clear_Software1IRQHandler
        ; IF the address of the fucntion to launch is equal to the start address of the Software IT zone
        ; THEN
clear_Software0IRQHandler: 
            ; As the function to execute is the Software0IRQHandler, clears the Software interrupt 0  
            msync
            lis     r5, INTC_SSCIR@ha
            lis     r3, 0x01000000@h
            stw     r3, INTC_SSCIR@l(r5) 
            msync   
            b clear_SoftwarexIRQHandler_end 
        ; ELSE
clear_Software1IRQHandler: 
            ; As the function to execute is the Software1IRQHandler, clears the Software interrupt 1
            msync
            lis     r5, INTC_SSCIR@ha
            lis     r3, 0x00010000@h
            stw     r3, INTC_SSCIR@l(r5) 
            msync
        ; END IF
clear_SoftwarexIRQHandler_end: 
        ; Set the PID0 register (SPR 48) to 5 if the ISR is for BITE functionnality   
        li     r5, 0x5
        mtspr   48, r5   
        b set_user_mode    
    ; ELSE
do_not_set_BITE_PID_value:  
        ; Disable Decrementer interrupt (TCR[DIE] set to 0)
        mfspr r5, 340
        lis r3, 0xFBFFFFFF@h
        ori r3, r3, 0xFBFFFFFF@l
        and r5, r5, r3
        mtspr 340, r5
    ; END IF 
    
set_user_mode:
    ; Store the return pointer into the stack
    stwu    r1, -0x10 (r1)
    mflr    r5
    stw     r5,  0x14 (r1) 
    
    ; Enable processor recognition of interrupts (Set MSR[EE]=1)
    wrteei  1
    
    ; Set the processor in USER mode (e200z6 MSR[PR] register set to 1) 
    ; and active the SPE APU
    mfmsr r5
    ori    r5,r5,0x02004000@l
    oris    r5,r5,0x02004000@h
    sync
    mtmsr r5     
    isync     
    
    ; Set LR register with the C function address     
    mtlr    r4
    
    ; Branch to ISR, but return here
    blrl
    
    ; Call the "System Call" exception to set the supervisor mode 
    sc
            
    ; Restore the return pointer from the stack
    lwz     r5,  0x14 (r1)  
    mtlr    r5
    addi    r1, r1, 0x10   
    
    ; Set the PID0 register (SPR 48) to 4 for BSP access   
    li     r5, 0x4
    mtspr   48, r5   
    
    ; Restore the TCR register from the stack frame
    lwz     r5,  0xC (r1)    
    mtspr   340, r5
    
    ; Restore stack frame of 0x8 bytes
    addi    r1, r1, 0x10  
    
    ; Return to interrupt handler
    blr               
        
    ; The following code of the function shall be mapped into the exception handlers for supervisor mode memory area
        .section .exception_handlers_supervisor_mode, c
        
;**************************************************************
; Local function : prolog                                     *
; Macro (before starting treatment in an interrupt)           *
;**************************************************************
prolog:    .macro
    ; Create stack frame
    stwu    r1, -0xC8 (r1)
    ; Store r0 working register
    stw r0,  0x28 (r1)
    ; Store a second working register (r4)
    stw    r4,  0x38 (r1)
        
    ; Save SRR0 and SRR1 registers
    mfsrr0  r0
    stw     r0,  0x10 (r1)
    mfsrr1  r0
    stw     r0,  0x14 (r1)
    
    ; Save LR (LR will be used for ISR Vector)    
    mflr    r0
    stw     r0,  0x18 (r1) 
    
    ; Save CTR, XER and CR registers
    mfctr   r0            
    stw     r0,  0x1C (r1)
    mfxer   r0            
    stw     r0,  0x20 (r1)
    mfcr    r0            
    stw     r0,  0x24 (r1)
    
    ; Save general purpose register (r3, r5, r6, r7, r8, r9, r10, r11, r12, r14, r15 and r16)
    stw     r3,  0x30 (r1)
    stw     r5,  0x40 (r1)
    stw     r6,  0x48 (r1)
    stw     r7,  0x50 (r1)
    stw     r8,  0x58 (r1)
    stw     r9,  0x60 (r1)
    stw     r10, 0x68 (r1)
    stw     r11, 0x70 (r1)
    stw     r12, 0x78 (r1)
    stw     r14, 0x80 (r1) 
    stw     r15, 0x88 (r1)
    stw     r16, 0x90 (r1)
    stw     r17, 0x98 (r1)
    stw     r18, 0xA0 (r1)
    
    ; Save CSRR0 and CSRR1 registers
    mfcsrr0 r0
    stw     r0,  0xA8 (r1)
    mfcsrr1 r0
    stw     r0,  0xAC (r1)
    
    ; Save DEAR register 
    mfspr   r4,  61  
    stw     r4,  0xB0 (r1)    
    
    ; Save ESR register 
    mfspr   r4,  62
    stw     r4,  0xB4 (r1)    
    
    ; Read PID0 register (SPR 48) value and store it into the stack frame    
    mfspr   r4,  48
    stw     r4,  0xBC (r1)    
    
    ; Set the PID0 register (SPR 48) to 4 for BSP access   
    li      r4,  0x4
    mtspr   48,  r4    
    
    ; Read INTC CPR register value and store it into the stack frame    
    lis     r4,  INTC_CPR@ha
    lwz     r4,  INTC_CPR@l(r4)
    stw     r4,  0xB8 (r1)  
    
    ; Save MCSR register
    mfmcsr  r0
    stw     r0,  0xC0 (r1) 
    
    ; Save MSR register
    mfmsr   r0
    stw     r0,  0xC4 (r1)
    
               .endm


;**************************************************************
; Local function : epilog                                     *
; Macro (before returning from an interrupt)                  *
;**************************************************************
epilog:     .macro
    ; Restore context required by EABI (LR, CTR, XER and CR) 
    lwz     r0,  0x18 (r1)
    mtlr    r0
    lwz     r0,  0x1C (r1)
    mtctr   r0
    lwz     r0,  0x20 (r1)
    mtxer   r0
    lwz     r0,  0x24 (r1)
    mtcrf   0xff, r0
    
    ; Restore rest of context required by EABI (r3, r5, r6, r7, r8, r9, r10, r11, r12, r16, r17 and r18)
    lwz     r3,  0x30 (r1)
    lwz     r5,  0x40 (r1)
    lwz     r6,  0x48 (r1)
    lwz     r7,  0x50 (r1)
    lwz     r8,  0x58 (r1)
    lwz     r9,  0x60 (r1)
    lwz     r10, 0x68 (r1)
    lwz     r11, 0x70 (r1)
    lwz     r12, 0x78 (r1)
    lwz     r16, 0x90 (r1)
    lwz     r17, 0x98 (r1)
    lwz     r18, 0xA0 (r1)
    
    ; Restore PID0 register (SPR 48) value   
    lwz     r4, 0xBC (r1)
    mtspr   48, r4   
    
    ; Ensure interrupt flag has finished clearing 
    mbar    0
    
    ; Retrieve SRR0 and SRR1 Registers
    lwz     r0,  0x10 (r1)
    mtsrr0  r0
    lwz     r0,  0x14 (r1)
    mtsrr1  r0
    
    ; Retrieve CSRR0 and CSRR1 Registers
    lwz     r0,  0xA8 (r1)
    mtcsrr0 r0
    lwz     r0,  0xAC (r1)
    mtcsrr1 r0

    ; Restore Other Working Registers (r4 and r0)
    lwz     r4,  0x38 (r1)
    lwz     r0,  0x28 (r1)

    ; Restore space on stack 
    addi    r1, r1, 0xC8
                .endm
        
        
;**************************************************************
; Local function : Control_to_BITE_SP                         *
; Macro                                                       *
;**************************************************************
Control_to_BITE_SP:     .macro
    ; Store the SP (r1) into r15
    mr     r15, r1
    ; Load r14 into the SP (r1)
    mr     r1,  r14
                .endm
                
;**************************************************************
; Local function : BITE_to_Control_SP                         *
; Macro                                                       *
;**************************************************************
BITE_to_Control_SP:     .macro
    ; Store the SP (r1) into r14
    mr     r14, r1
    ; Load r15 into the SP (r1)
    mr     r1,  r15
                .endm
                
        
;**************************************************************
; Local function : store_SP                                   *
;**************************************************************
        .global store_SP 
        .align 4        
store_SP:
; r4 shall contain the address of the C function to launch
; r16 shall contain the number of the last IVOR launched

    ; Set the r18 register to 0
    li r18, 0

    ; IF the SP (r1) value is not included into the BITE stack zone address
    lis r5,_BITE_STACK_END_ADDR@h
    ori r5,r5,_BITE_STACK_END_ADDR@l
    cmplw r1,r5
    ble store_SP_is_in_BITE_zone
    ; THEN
store_SP_is_in_Control_zone:
        ; IF the exception is an IVOR 4 AND the address of the function to launch is included into the Software IT zone address
        li r6, 0x0400
        cmplw r16,r6
        bne store_SP_end
        lis r3,_SOFTWARE_IT_FUNCTION_ADDR@h
        ori r3,r3,_SOFTWARE_IT_FUNCTION_ADDR@l
        lis r5,_SOFTWARE_IT_FUNCTION_END_ADDR@h
        ori r5,r5,_SOFTWARE_IT_FUNCTION_END_ADDR@l    
        cmplw r3,r4
        bgt store_SP_end
        cmplw r5,r4
        blt store_SP_end
        ; THEN
            ; Call Control_to_BITE_SP function to change the stack pointer to the BITE zone
            Control_to_BITE_SP
            ; Set the r18 register to 1
            li r18, 1
            b store_SP_end
        ; END IF
    ; ELSE
store_SP_is_in_BITE_zone:
        ; IF the exception is not an IVOR 4 OR the address of the function to launch is not included into the Software IT zone addres
        li r6, 0x0400
        cmplw r16,r6
        bne store_SP_Set_Control_zone
        lis r3,_SOFTWARE_IT_FUNCTION_ADDR@h
        ori r3,r3,_SOFTWARE_IT_FUNCTION_ADDR@l
        lis r5,_SOFTWARE_IT_FUNCTION_END_ADDR@h
        ori r5,r5,_SOFTWARE_IT_FUNCTION_END_ADDR@l    
        cmplw r3,r4
        bgt store_SP_Set_Control_zone
        cmplw r5,r4
        bgt store_SP_end
        ; THEN
store_SP_Set_Control_zone:
            ; Call BITE_to_Control_SP function to change the stack pointer to the Control zone
            BITE_to_Control_SP
            ; Set the r18 register to 2
            li r18, 2
        ; END IF
    ; END IF
store_SP_end:
    blr
        
;**************************************************************
; Local function : restore_SP                                 *
;**************************************************************
        .global restore_SP 
        .align 4        
restore_SP:
    ; IF the handler have to restore the CONTROL stack pointer (r18 = 1)
    li r6, 1
    cmplw r18, r6
    bne restore_SP_BITE
    ; THEN 
        ; Call BITE_to_Control_SP function to change the stack pointer to the Control zone
    BITE_to_Control_SP  
    b restore_SP_end
restore_SP_BITE:
    ; ELSE IF the handler have to restore the CONTROL stack pointer (r18 = 2)
    li r6, 2
    cmplw r18, r6
    bne restore_SP_end
    ; THEN 
        ; Call Control_to_BITE_SP function to change the stack pointer to the BITE zone
    Control_to_BITE_SP
restore_SP_end:
    ; END IF    
    blr
        
           
;**************************************************************
; Global function : MainTaskHandler                           *
; main task handler (IVOR10)                                  *
;**************************************************************
        .global MainTaskHandler 
        .align 4        
MainTaskHandler:     
    ; Call prolog function, to store current context into the stack
    prolog         
    
    ; Store interrupt id (0x0A00) into r16 register
    li r16,0x0A00
    
    ; Call store_SP function to manage the SP address between BITE and Control zone
    bl store_SP
    
    ; Set current priority to 5
    li      r0, 5
    lis     r4, INTC_CPR@ha
    stw     r0, INTC_CPR@l(r4)
    
    ; Store MainTask function address into the r4 register to use it for branching later
    lis     r4, MainTask@h
    ori     r4, r4, MainTask@l    
    
    ; Write "1" to clear Dec Interrupt Status (DIS) flag
    lis     r0, 0x0800
    ; DIS flag is in spr TSR (spr 336)
    mtspr   336, r0
     
    ; Call launch_c_function function to start the user mode and launch the C function of the interrupt functionnality
    bl launch_c_function
    
    ; Enable Decrementer interrupt (TCR[DIE] set to 1)
    mfspr r0, 340
    oris r0, r0, 0x04000000@h
    mtspr 340, r0
    
    ; Call restore_SP function to manage the SP address between BITE and Control zone
    bl restore_SP
    
    ; Restore INTC current priority value from stack
    lwz     r0,  0xB8 (r1)      
    lis     r4, INTC_CPR@ha  
    stw     r0, INTC_CPR@l(r4)  
    
    ; Call epilog function, to restore the previous context
    epilog     
    
    ; End of Interrupt (MSR contents are restored from SRR1)
    rfi           

           
;**************************************************************
; Global function : ExternalIntHandler                        *
; external interrupt handler (IVOR4)                          *
;**************************************************************
        .global ExternalIntHandler  
        .align 4
ExternalIntHandler:      
    ; Call prolog function, to store current context into the stack
    prolog         
    ; Store interrupt id (0x0400) into r16 register
    li      r16,0x0400
    
    ; Store ISR address (with the IANTC_IACKR register) into the r4 register to use it for branching later
    lis     r5, INTC_IACKR@ha  
    lwz     r5, INTC_IACKR@l(r5) 
    lwz     r4, 0x0(r5) 
    
    ; Call store_SP function to manage the SP address between BITE and Control zone
    bl store_SP
        
    ; Call launch_c_function function to start the user mode and launch the C function of the interrupt functionnality
    bl launch_c_function
        
    ; Write 0 to INTC_EOIR to clear the interrupt flag
    msync
    lis     r4, INTC_EOIR@ha
    li      r0, 0
    stw     r0, INTC_EOIR@l(r4) 
    msync
    
    ; Call restore_SP function to manage the SP address between BITE and Control zone
    bl restore_SP
    
    ; Call epilog function, to restore the previous context
    epilog     
    
    ; End of Interrupt
    rfi
    

;**************************************************************
; Global function : Ivor0Handler                              *
; IVOR0 handler (Critical input)                              *
;**************************************************************
        .global Ivor0Handler 
        .align 4
Ivor0Handler:             
    ; Store interrupt id (0x0000) into r16 register
    li r16,0x0000
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler        
    

;**************************************************************
; Global function : Ivor1Handler                              *
; IVOR1 handler (Machine check)                               *
;**************************************************************
        .global Ivor1Handler 
        .align 4
Ivor1Handler:            
    ; Store interrupt id (0x0100) into r16 register
    li  r16,0x0100
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor2Handler                              *
; IVOR2 handler (Data storage)                                *
;**************************************************************
        .global Ivor2Handler 
        .align 4
Ivor2Handler:       
    ; Call prolog function, to store current context into the stack
    prolog   
    ; Store interrupt id (0x0200) into r16 register
    li  r16,0x0200
    
    ; Read PID0 register (SPR 48) value from the stack frame
    lwz     r4, 0xBC (r1)
    ; IF the PID0 is equal to the BITE PID (default handler was called due to a BITE error)
    li      r0, 0x5
    cmplw   r4,  r0
    ; THEN Restore PID0 register (SPR 48) value and call the DefaultHandler function
    bne Ivor2Handler_no_BITE_execution
        ; Restore PID0 register (SPR 48) value and call the DefaultHandler function
        mtspr   48, r4    
        b   DefaultHandler
    
    ; ELSE manage the exception
Ivor2Handler_no_BITE_execution:
    
    ; Call store_SP function to manage the SP address between BITE and Control zone
    bl store_SP
    
    ; Store ECCTask function address into the r4 register to use it for branching later
    lis     r4, ECCTask@h
    ori     r4, r4, ECCTask@l
    
    ; Call launch_c_function function to start the user mode and launch the C function of the interrupt functionnality
    bl launch_c_function    
    
    ; Call restore_SP function to manage the SP address between BITE and Control zone
    bl restore_SP
    
    ; Call epilog function, to restore the previous context
    epilog     
    
    ; End of Interrupt
    rfi
    

;**************************************************************
; Global function : Ivor3Handler                              *
; IVOR3 handler (Instruction storage)                         *
;**************************************************************
        .global Ivor3Handler 
        .align 4
Ivor3Handler:       
    ; Store interrupt id (0x0300) into r16 register
    li  r16,0x0300
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor5Handler                              *
; IVOR5 handler (Alignment)                                   *
;**************************************************************
        .global Ivor5Handler 
        .align 4
Ivor5Handler:            
    ; Store interrupt id (0x0500) into r16 register
    li  r16,0x0500
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor6Handler                              *
; IVOR6 handler (Program)                                     *
;**************************************************************
        .global Ivor6Handler 
        .align 4
Ivor6Handler:          
    ; Store interrupt id (0x0600) into r16 register
    li  r16,0x0600
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor7Handler                              *
; IVOR7 handler (Floating-point unavailable)                  *
;**************************************************************
        .global Ivor7Handler 
        .align 4
Ivor7Handler:         
    ; Store interrupt id (0x0700) into r16 register
    li  r16,0x0700
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor8Handler                              *
; IVOR8 handler (System Call)                                 *
;**************************************************************
        .global Ivor8Handler 
        .align 4
Ivor8Handler:          
    ; Disable the Interrupt (MSR[EE]) and set the Supervisor Mode (MSR[PR]):
    ; Read the MSR value from the SRR1 register into r0     
    mfsrr1  r0
    ; Into r0 set the MSR[PR] and MSR[EE] bits to 0 ; r0 = r0 & 0xFFFF3FFF
    lis r4,0xFFFF3FFF@h
    ori r4,r4,0xFFFF3FFF@l
    and r0,r0,r4
    ; Set new MSR value to the SRR1 register 
    mtsrr1  r0          
    ; End of Interrupt
    rfi  
    

;**************************************************************
; IVOR11 handler (Fixed-interval timer interrupt)             *
;**************************************************************
; Mapped to DefaultHandler as the interrupt is not enabled
    

;**************************************************************
; IVOR12 handler (Watchdog timer interrupt)                   *
;**************************************************************
; Mapped to DefaultHandler as the interrupt is not enabled
    

;**************************************************************
; Global function : Ivor13Handler                             *
; IVOR13 handler (Data TLB error)                             *
;**************************************************************
        .global Ivor13Handler 
        .align 4
Ivor13Handler:          
    ; Store interrupt id (0x0D00) into r16 register
    li  r16,0x0D00
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor14Handler                             *
; IVOR14 handler (Instruction TLB error)                      *
;**************************************************************
        .global Ivor14Handler 
        .align 4
Ivor14Handler:          
    ; Store interrupt id (0x0E00) into r16 register
    li  r16,0x0E00
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; IVOR15 handler (Debug)                                      *
;**************************************************************
; Mapped to DefaultHandler as the interrupt is not enabled
    

;**************************************************************
; Global function : Ivor32Handler                             *
; IVOR32 handler (SPE APU unavailable)                        *
;**************************************************************
        .global Ivor32Handler 
        .align 4
Ivor32Handler:            
    ; Store interrupt id (0x2000) into r16 register
    li  r16,0x2000
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; Global function : Ivor33Handler                             *
; IVOR33 handler (SPE floating-point data exception)          *
;**************************************************************
        .global Ivor33Handler 
        .align 4
Ivor33Handler:         
    ; Store interrupt id (0x2100) into r16 register
    li  r16,0x2100
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler    
    

;**************************************************************
; IVOR34 handler (SPE floating-point round exception)         *
;**************************************************************
; Mapped to DefaultHandler as the interrupt is not enabled
        

;**************************************************************
; Global function : DefaultHandlerUser                        *
; Default handler in user mode                                *
;**************************************************************
        .global DefaultHandlerUser 
        .align 4
DefaultHandlerUser:
    ; Call the "System Call" exception to set the supervisor mode 
    sc
    ; Call DefaultHandler function, to reset the software
    b   DefaultHandler
        

;**************************************************************
; Global function : DefaultHandler                            *
; Default handler                                             *
;**************************************************************
        .global DefaultHandler 
        .align 4
DefaultHandler:
    ; Call prolog function, to store current context into the stack
    prolog    
    
    ; IF the last interrupt is not an External Interrupt
    li      r0,  0x0400
    cmplw   r16,  r0
    beq DefaultHandlerDump
    ; THEN
    ; Read PID0 register (SPR 48) value from the stack frame    
    lwz     r4, 0xBC (r1)
    ; IF the PID0 is equal to the BITE PID (default handler was called due to a BITE error)
        li      r0,  0x5
    cmplw   r4,  r0    
    bne DefaultHandlerDump
    ; THEN
        ; Disable pending BITE interrupt (SW interrupt 0 and 1 shall be cleared)
        ; INTC.SSCIR[1].B.CLEAR = TRUE;
        ; INTC.SSCIR[0].B.CLEAR = TRUE;        
        msync
        lis     r4, INTC_SSCIR@ha
        lis     r0, 0x01010000@h
        stw     r0, INTC_SSCIR@l(r4) 
        msync
        ; Restart the BITE SW (Set signal I_BSP_Out.bite_status.F_BITE_to_be_reset)
        lis     r4, I_BSP_Out@ha
        li      r0, 1
            stb     r0, I_BSP_Out@l(r4)
            ; Set current priority to 0
            li      r0, 0
            lis     r4, INTC_CPR@ha  
            stw     r0, INTC_CPR@l(r4)  
            ; Set the stack pointer (r1) to the Control stack
            BITE_to_Control_SP
        ; Call epilog function, to restore previous context from the stack 
        epilog
            ; Initialize r14 register to the BITE STACK start address
            lis r14,_BITE_STACK_END_ADDR@h
            ori r14,r14,_BITE_STACK_END_ADDR@l
        ; Execute the End of Interrupt instruction (MSR contents are restored from SRR1)
        rfi
    ; ELSE dump the stack frame to the RS link
    ; ELSE dump the stack frame to the RS link
DefaultHandlerDump:    
        ; Switch RS speed on SCI_A bus to 115200 bauds
        lis     r3, ESCIA_CR1_115200@h
        ori     r3, r3, ESCIA_CR1_115200@l
        lis     r4, ESCIA_CR1_ADDR@h
        ori     r4, r4, ESCIA_CR1_ADDR@l
        stw     r3, 0(r4)
    
        ; Initialize TAB_MC_STACK_DUMP area in the internal SRAM to 0x00000000 (0x40007F00--0x40007FFF)
            ; Set the address of TAB_MC_STACK_DUMP area
            lis     r28, TAB_MC_STACK_DUMP@h
            ori     r28, r28, TAB_MC_STACK_DUMP@l
            ; Set the number of loop steps (2 GPRs are copied each step so nb = 0x100 / (2 * 4))
            li      r29, 32
            mtctr   r29
            ; Set the initialization value
            lis     r30, 0x00000000@h
            ori     r30, r30, 0x00000000@l
            lis     r31, 0x00000000@h
            ori     r31, r31, 0x00000000@l
            ; Loop to set the initial value
            loop_init_iram_dump:
                stmw    r30, 0(r28)
                addi    r28, r28, 8
                bdnz    loop_init_iram_dump
       
        ; Write new line character on RS
        li    r3,0xd
        bl    SendChar_A
        
        ; Write carriage return character on RS
        li    r3,0xa
        bl    SendChar_A
        
        ; Get the address of beginning of stack frame in r15
        addi    r15,r1,0xC8
        
        ; Get the address of beginning of the internal SRAM stack dump area
        lis     r14, TAB_MC_STACK_DUMP@h
        ori     r14, r14, TAB_MC_STACK_DUMP@l

        ; DO
DefaultHandlerDump1:
        ; Load the content of stack frame word
        lwzx    r3,r0,r15

            ; Write the content of stack in the internal SRAM
            stw     r3, 0(r14)

        ; Write the content of stack frame word on RS
        li    r4,8
        bl    SendNumber_A
            
        ; Write space character on RS
        li    r3,0x20
        bl    SendChar_A
            
        ; Get the address of beginning of stack frame in r15
        ; Skip to the next stack frame word
        addi    r15,r15,-4
            
            ; Skip to the next internal RAM frame word
            addi    r14, r14, +4

        ; WHILE end of stack frame is not reached
        cmp    r15,r1
        bge    DefaultHandlerDump1

        ; Load the content of user_reset_source
        lis     r4, user_reset_source@h
        ori     r4, r4, user_reset_source@l
        lwz     r3, 0(r4)

        ; Write the content of user_reset_source in the internal SRAM
        stw     r3, 0(r14)

        ; Write the content of user_reset_source on RS
        li      r4, 8
        bl      SendNumber_A
        
        ; Write carriage return character on RS
        li    r3,0xd
        bl    SendChar_A
        ; Write new line character on RS
        li    r3,0xa
        bl    SendChar_A    
        
    ; Start infinite loop
DefaultHandlerLoop:
    b   DefaultHandlerLoop
