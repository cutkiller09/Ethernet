;**************************************************************
; FUNCTION : interrupt handlers table, boot the target        *
;                                                             *
; ENVIRONMENT : PPC5554                                       *
;**************************************************************

        .file    "boot.s"

        .section .header_assembly_area
        .long _BAM_RCHW_WORD
        .long _INTERNAL_STARTUP_ADDR
        .long _SW_SIZE_BSP

        .section .crc32
        .long _CRC32
        
        .section .text

        .global _IVPR_VALUE
;**************************************************************
;                                                             *
;                     LOCAL CONSTANTS                         *
;                                                             *
;**************************************************************



;**************************************************************
;                                                             *
;                      GLOBAL FUNCTIONS                       *
;                                                             *
;**************************************************************
        .global    Boot
Boot:

    ;****************************************
    ; MSR - PPC5554
    ;****************************************
    ;  UCLE   = 0
    ;  SPE    = 1 (SPE APU activated)
    ;  WE     = 0 (Power management disable)
    ;  CE     = 1 (Critical interrupt enable)
    ;  EE     = 0 (External interrupt disable)
    ;  PR     = 0 (Supervisor mode)
    ;  FP     = 0 (floating point  - not used by e200z6)
    ;  ME     = 1 (machine check enabled)
    ;  FE0    = 0 (floating point precise mode - not used by e200z6)
    ;  DE     = 1 (Debug interrupt APU)
    ;  FE1    = 0 (floating point precise mode - not used by e200z6)
    ;  IS     = 0
    ;  DS     = 0
    ;****************************************
    lis    r11,0x02021200@h
    ori    r11,r11,0x02021200@l
    sync
    mtmsr    r11
    isync
    
    ;****************************************
    ; TIME BASE initialization
    ;****************************************
    ; TBU = 0x00000000
    ; TBL = 0x00000000
    ;****************************************

    ; INITIALIZE TIME BASE TO 0
    ; Load immediate data of 0 to r4
    li     r4, 0
    ; Move r4 to TBU and TBL
    mttbu  r4
    mttbl  r4

    ; ENABLE TIME BASE
    ; Move from spr HID0 to r5 (copies HID0)
    mfhid0 r5
    ; Load immed. data of 0x4000 to r4
    li     r4, 0x4000
    ; OR r4 (0x0000 4000) with r4 (HID0 value)
    or     r5, r4, r5
    ; Move result to HID0
    mthid0 r5

    ;****************************************
    ; DEC = 0xFFFFFFFF
    ;****************************************
    lis    r11,0xFFFFFFFF@h
    ori    r11,r11,0xFFFFFFFF@l
    mtdec    r11

    ;****************************************
    ; Initialize Exceptions handlers
    ;****************************************
    ; Set the IVPR to the Software Handlers memory area defined in the cmd file 
    lis     r0, _IVPR_VALUE@h
    ori     r0, r0, _IVPR_VALUE@l
    mtspr  63, r0
    
    ; Configure the IVOR registers        
    ; IVORx registers are "hard-wired" in the e200z0 and z0h cores 
    ; IVOR0 Critical input (SPR 400)
    lis     r0, Ivor0Handler@h
    ori     r0, r0, Ivor0Handler@l    
    mtspr 400, r0
    ; IVOR1 Machine check interrupt (SPR 401)
    lis     r0, Ivor1Handler@h
    ori     r0, r0, Ivor1Handler@l    
    mtspr 401, r0
    ; IVOR2 Data storage interrupt (SPR 402)
    lis     r0, Ivor2Handler@h
    ori     r0, r0, Ivor2Handler@l    
    mtspr 402, r0
    ; IVOR3 Instruction storage interrupt (SPR 403)
    lis     r0, Ivor3Handler@h
    ori     r0, r0, Ivor3Handler@l    
    mtspr 403, r0
    ; IVOR4 External input interrupt (SPR 404)
    lis     r0, ExternalIntHandler@h
    ori     r0, r0, ExternalIntHandler@l    
    mtspr 404, r0
    ; IVOR5 Alignment interrupt (SPR 405)
    lis     r0, Ivor5Handler@h
    ori     r0, r0, Ivor5Handler@l    
    mtspr 405, r0
    ; IVOR6 Program interrupt (SPR 406)
    lis     r0, Ivor6Handler@h
    ori     r0, r0, Ivor6Handler@l    
    mtspr 406, r0
    ; IVOR7 Floating-point unavailable interrupt (SPR 407)
    lis     r0, Ivor7Handler@h
    ori     r0, r0, Ivor7Handler@l    
    mtspr 407, r0
    ; IVOR8 System call interrupt (SPR 408)
    lis     r0, Ivor8Handler@h
    ori     r0, r0, Ivor8Handler@l    
    mtspr 408, r0
    ; IVOR10 Decrementer interrupt (SPR 410)
    lis     r0, MainTaskHandler@h
    ori     r0, r0, MainTaskHandler@l    
    mtspr 410, r0        
    ; IVOR11 Fixed-interval timer interrupt (SPR 411)
    lis r0, DefaultHandler@h
    ori r0, r0, DefaultHandler@l
    mtspr 411, r0
    ; IVOR12 Watchdog timer interrupt (SPR 412)
    lis r0, DefaultHandler@h
    ori r0, r0, DefaultHandler@l
    mtspr 412, r0
    ; IVOR13 Data TLB error interrupt (SPR 413)
    lis     r0, Ivor13Handler@h
    ori     r0, r0, Ivor13Handler@l    
    mtspr 413, r0        
    ; IVOR14 Instruction TLB error interrupt (SPR 414)
    lis     r0, Ivor14Handler@h
    ori     r0, r0, Ivor14Handler@l    
    mtspr 414, r0  
    ; IVOR15 Debug interrupt (SPR 415)
    lis r0, DefaultHandler@h
    ori r0, r0, DefaultHandler@l
    mtspr 415, r0
    ; IVOR32 SPE APU unavailable interrupt (SPR 528)
    lis     r0, Ivor32Handler@h
    ori     r0, r0, Ivor32Handler@l    
    mtspr 528, r0 
    ; IVOR33 SPE floating-point data exception interrupt (SPR 529)
    lis     r0, Ivor33Handler@h
    ori     r0, r0, Ivor33Handler@l    
    mtspr 529, r0 
    ; IVOR34 SPE floating-point round exception interrupt (SPR 530)
    lis r0, DefaultHandler@h
    ori r0, r0, DefaultHandler@l
    mtspr 530, r0


    ; Initialize r1 (stack pointer) r2 (sdata2 pointer) and r13 (sdata pointer)
    ; according to the EABI of diab data compiler
    lis    r13,_SDA_BASE_@h
    ori    r13,r13,_SDA_BASE_@l
    lis    r2,_SDA2_BASE_@h
    ori    r2,r2,_SDA2_BASE_@l
    lis    r1,__SP_INIT@h
    ori    r1,r1,__SP_INIT@l

    ; Initialize r14 register to the BITE STACK ADDRESS (used to memorize the BITE stack pointer)
    lis r14,_BITE_STACK_END_ADDR@h
    ori r14,r14,_BITE_STACK_END_ADDR@l
    ; Initialize r15 register to 0 (used to memorize the Control stack pointer)
    li    r15,0x0
    ; Initialize r16 register to 0 (used to memorize the last number of the last exception raised)
    li    r16,0x0
    ; Initialize r17 register to 0 (used memorize the current INTC CPR priority value)
    li    r17,0x0
    ; Initialize r18 register to 0 (used to memorize if the stack pointer shall change to Control or BITE zone)
    li    r18,0x0

    ; Call InitializeHardware function to initialize all hardware functionnality
    bl    InitializeHardware

    ; Call BackgroundTask function to launch the background Task (software will never return)
    bl    BackgroundTask

    

; Specific section for BSP software services function
        .section .bsp_services

_LAN9250_Init:
        ba    LAN9250_Init
_LAN9250_Write:
        ba    LAN9250_Write
_LAN9250_Test:
        ba    LAN9250_Test
_LAN9250_Control:
        ba    LAN9250_Control
_LAN9250_Start:
        ba    LAN9250_Start
_LAN9250_Halt:
        ba    LAN9250_Halt

