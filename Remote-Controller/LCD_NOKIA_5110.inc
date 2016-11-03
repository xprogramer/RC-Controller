#include "Print_Chars.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO SETUP AND INITIALIZE THE LCD SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_SETUP
	bsf LCD_RST
	bsf LCD_SCE
	bcf LCD_RST
	call delay_ms_100
	bsf LCD_RST
	; Extended instruction set control (H=1)
	movlw 0x21
	call LCD_Send_Cmd
	; Bias system (1:48)
	movlw 0x13
	call LCD_Send_Cmd
	; Default Vop (3.06 + 66 * 0.06 = 7V)
	movlw 0xC2
	call LCD_Send_Cmd
	; Extended instruction set control (H=0)
	movlw 0x20
	call LCD_Send_Cmd
	; All display segments on
	movlw 0x09
	call LCD_Send_Cmd
	; Clear the screen
	call LCD_Clear
	; Activate the LCD
	; Dilay blanksp
	movlw 0x08
	call LCD_Send_Cmd
	; Normal mode (0x0d = inverse mode)
	movlw 0x0C
	call LCD_Send_Cmd
	call delay_ms_100
	; Set the cursor at the origin (0,0)
	call LCD_Set_Cursor
	return

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO CLEAR THE WHOLE SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Clear
	call LCD_Set_Cursor ; Set the cursor to the initial position
	movlw 0x10
	movwf tmp1
lcd_clear_1
	movlw 0x48
	movwf tmp2
lcd_clear_2
	clrw
	call LCD_Send_Data
	decfsz tmp2,f
	goto lcd_clear_2
	decfsz tmp1,f
	goto lcd_clear_1
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO SET THE CURSOR TO A GIVEN POSITION (X and Y)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Set_Cursor
	movfw column
	iorlw 0x80
	call LCD_Send_Cmd
	movfw line
	iorlw 0x40
	call LCD_Send_Cmd
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO SEND COMMAND VIA SPI BUS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Send_Cmd
	bcf LCD_DC
	call LCD_SPI_send
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO SEND DATA VIA SPI BUS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Send_Data
	bsf LCD_DC
	call LCD_SPI_send
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO SEND AND READ DATA VIA SPI BUS (MSBFirst)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_SPI_send
	movwf outByte
	movlw 0x08
	movwf bits_counter
	clrf inByte
	bcf LCD_SCE
LCD_SPI_loop ; prepare the bit to clock
	bcf LCD_CLK ; prepare the bit to be clocked
	btfss outByte,7
	bcf LCD_SDA
	btfsc outByte,7
	bsf LCD_SDA
	bsf LCD_CLK ; clock the bit
	decfsz bits_counter,f
	goto LCD_next_bit
	goto LCD_end_sending
LCD_next_bit
	; move to next bit
	rlf outByte,f
	goto LCD_SPI_loop
LCD_end_sending
	bsf LCD_SCE
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO PRINT NUMBER IN THE SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Print_Number
	movfw b1
	sublw 0x00
	btfsc STATUS,Z
	call Print_0
	movfw b1
	sublw 0x01
	btfsc STATUS,Z
	call Print_1
	movfw b1
	sublw 0x02
	btfsc STATUS,Z
	call Print_2
	movfw b1
	sublw 0x03
	btfsc STATUS,Z
	call Print_3
	movfw b1
	sublw 0x04
	btfsc STATUS,Z
	call Print_4
	movfw b1
	sublw 0x05
	btfsc STATUS,Z
	call Print_5
	movfw b1
	sublw 0x06
	btfsc STATUS,Z
	call Print_6
	movfw b1
	sublw 0x07
	btfsc STATUS,Z
	call Print_7
	movfw b1
	sublw 0x08
	btfsc STATUS,Z
	call Print_8
	movfw b1
	sublw 0x09
	btfsc STATUS,Z
	call Print_9
	return
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO PRINT STRING LABELS IN THE SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Print_Strings
	; Throttle
	call LCD_Set_Cursor
	call Print_T
	call Print_h
	call Print_r
	call Print_o
	call Print_t
	call Print_t
	call Print_l
	call Print_e
	; Pitch
	movlw 0x01
	movwf line
	call LCD_Set_Cursor
	call Print_P
	call Print_i
	call Print_t
	call Print_c
	call Print_h
	; Roll
	movlw 0x02
	movwf line
	call LCD_Set_Cursor
	call Print_R
	call Print_o
	call Print_l
	call Print_l
	; Yaw
	movlw 0x03
	movwf line
	call LCD_Set_Cursor
	call Print_Y
	call Print_a
	call Print_w
	; led

	; xProGraMer
	movlw 0x08
	movwf column
	movlw 0x05
	movwf line
	call LCD_Set_Cursor
	call Print_x
	call Print_minus
	call Print_P
	call Print_r
	call Print_o
	call Print_G
	call Print_r
	call Print_a
	call Print_M
	call Print_e
	call Print_r
	return
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO PRINT A VALUE IN THE SCREEN
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
LCD_Print_Value
	clrf b1
	clrf b2
	movwf tmp1
	sublw 0x00
	btfss tmp1,7
	goto _plus
	goto _minus
_plus
	call Print_plus
	goto continue
_minus
	call Print_minus
	bcf tmp1,7
continue
	movfw tmp1
v_loop_2
	addlw -0A ; tmp1 - 10
	btfss STATUS,C
	goto next_nb_2
	incf b1,f
	goto v_loop_2
next_nb_2
	addlw 0x0A
	movwf b2
	call LCD_Print_Number
	movfw b2
	movwf b1
	call LCD_Print_Number
	return