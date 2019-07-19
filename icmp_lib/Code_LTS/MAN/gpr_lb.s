;**************************************************************
; FUNCTION : basic functions link to Register management      *
;                                                             *
; ENVIRONMENT : PPC5554                                       *
;**************************************************************

        .file    "gpr_lb.s"
        .section .text
        
    .globl    _savegpr_19
    .globl    _savegpr_20, _savegpr_21, _savegpr_22
    .globl    _savegpr_23, _savegpr_24, _savegpr_25
    .globl    _savegpr_26, _savegpr_27, _savegpr_28
    .globl    _savegpr_29, _savegpr_30, _savegpr_31
                
;**************************************************************
; Global function : _savegpr_19                               *
;************************************************************** 
        .align    2
                ; Store r19 in address of (r11) - 52 
_savegpr_19:    stw    r19,-52(r11)
                ; Execute _savegpr_20
                
;**************************************************************
; Global function : _savegpr_20                               *
;************************************************************** 
        .align    2
                ; Store r20 in address of (r11) - 48 
_savegpr_20:    stw    r20,-48(r11)
                ; Execute _savegpr_21
                
;**************************************************************
; Global function : _savegpr_21                               *
;************************************************************** 
        .align    2
                ; Store r21 in address of (r11) - 44 
_savegpr_21:    stw    r21,-44(r11)
                ; Execute _savegpr_22
                
;**************************************************************
; Global function : _savegpr_22                               *
;************************************************************** 
        .align    2
                ; Store r22 in address of (r11) - 40 
_savegpr_22:    stw    r22,-40(r11)
                ; Execute _savegpr_23
                
;**************************************************************
; Global function : _savegpr_23                               *
;************************************************************** 
        .align    2
                ; Store r23 in address of (r11) - 36 
_savegpr_23:    stw    r23,-36(r11)
                ; Execute _savegpr_24
                
;**************************************************************
; Global function : _savegpr_24                               *
;************************************************************** 
        .align    2
                ; Store r24 in address of (r11) - 32 
_savegpr_24:    stw    r24,-32(r11)
                ; Execute _savegpr_25
                
;**************************************************************
; Global function : _savegpr_25                               *
;************************************************************** 
        .align    2
                ; Store r25 in address of (r11) - 28 
_savegpr_25:    stw    r25,-28(r11)
                ; Execute _savegpr_26
                
;**************************************************************
; Global function : _savegpr_26                               *
;************************************************************** 
        .align    2
                ; Store r26 in address of (r11) - 24 
_savegpr_26:    stw    r26,-24(r11)
                ; Execute _savegpr_27
                
;**************************************************************
; Global function : _savegpr_27                               *
;************************************************************** 
        .align    2
                ; Store r27 in address of (r11) - 20 
_savegpr_27:    stw    r27,-20(r11)
                ; Execute _savegpr_28
                
;**************************************************************
; Global function : _savegpr_28                               *
;************************************************************** 
        .align    2
                ; Store r28 in address of (r11) - 16 
_savegpr_28:    stw    r28,-16(r11)
                ; Execute _savegpr_29
                
;**************************************************************
; Global function : _savegpr_29                               *
;************************************************************** 
        .align    2
                ; Store r29 in address of (r11) - 12 
_savegpr_29:    stw    r29,-12(r11)
                ; Execute _savegpr_30
                
;**************************************************************
; Global function : _savegpr_30                               *
;************************************************************** 
        .align    2
                ; Store r30 in address of (r11) - 8 
_savegpr_30:    stw    r30,-8(r11)
                ; Execute _savegpr_31
                
;**************************************************************
; Global function : _savegpr_31                               *
;************************************************************** 
        .align    2
                ; Store r31 in address of (r11) - 4 
_savegpr_31:    stw    r31,-4(r11)
                ; Return to address stored in LR register           
                blr

    .globl    _restgpr_19
    .globl    _restgpr_20, _restgpr_21, _restgpr_22
    .globl    _restgpr_23, _restgpr_24, _restgpr_25
    .globl    _restgpr_26, _restgpr_27, _restgpr_28
    .globl    _restgpr_29, _restgpr_30, _restgpr_31
                
;**************************************************************
; Global function : _restgpr_19                               *
;************************************************************** 
        .align    2
                ; Restore r19 in address of (r11) - 52 
_restgpr_19:    lwz    r19,-52(r11)
                ; Execute _restgpr_20
                
;**************************************************************
; Global function : _restgpr_20                               *
;************************************************************** 
        .align    2
                ; Restore r20 in address of (r11) - 48 
_restgpr_20:    lwz    r20,-48(r11)
                ; Execute _restgpr_21
                
;**************************************************************
; Global function : _restgpr_21                               *
;************************************************************** 
        .align    2
                ; Restore r21 in address of (r11) - 44 
_restgpr_21:    lwz    r21,-44(r11)
                ; Execute _restgpr_22
                
;**************************************************************
; Global function : _restgpr_22                               *
;************************************************************** 
        .align    2
                ; Restore r22 in address of (r11) - 40 
_restgpr_22:    lwz    r22,-40(r11)
                ; Execute _restgpr_23
                
;**************************************************************
; Global function : _restgpr_23                               *
;************************************************************** 
        .align    2
                ; Restore r23 in address of (r11) - 36 
_restgpr_23:    lwz    r23,-36(r11)
                ; Execute _restgpr_24
                
;**************************************************************
; Global function : _restgpr_24                               *
;************************************************************** 
        .align    2
                ; Restore r24 in address of (r11) - 32 
_restgpr_24:    lwz    r24,-32(r11)
                ; Execute _restgpr_25
                
;**************************************************************
; Global function : _restgpr_25                               *
;************************************************************** 
        .align    2
                ; Restore r25 in address of (r11) - 28 
_restgpr_25:    lwz    r25,-28(r11)
                ; Execute _restgpr_26
                
;**************************************************************
; Global function : _restgpr_26                               *
;************************************************************** 
        .align    2
                ; Restore r26 in address of (r11) - 24 
_restgpr_26:    lwz    r26,-24(r11)
                ; Execute _restgpr_27
                
;**************************************************************
; Global function : _restgpr_27                               *
;************************************************************** 
        .align    2
                ; Restore r27 in address of (r11) - 20 
_restgpr_27:    lwz    r27,-20(r11)
                ; Execute _restgpr_28
                
;**************************************************************
; Global function : _restgpr_28                               *
;************************************************************** 
        .align    2
                ; Restore r28 in address of (r11) - 16 
_restgpr_28:    lwz    r28,-16(r11)
                ; Execute _restgpr_29
                
;**************************************************************
; Global function : _restgpr_29                               *
;************************************************************** 
        .align    2
                ; Restore r29 in address of (r11) - 12 
_restgpr_29:    lwz    r29,-12(r11)
                ; Execute _restgpr_30
                
;**************************************************************
; Global function : _restgpr_30                               *
;************************************************************** 
        .align    2
                ; Restore r30 in address of (r11) - 8 
_restgpr_30:    lwz    r30,-8(r11)
                ; Execute _restgpr_31
                
;**************************************************************
; Global function : _restgpr_31                               *
;************************************************************** 
        .align    2
                ; Restore r31 in address of (r11) - 4 
_restgpr_31:    lwz    r31,-4(r11)
                ; Return to address stored in LR register
                blr
                
