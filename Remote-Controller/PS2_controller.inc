;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO COMPUTE Throttle, Yaw, Pitch and Roll
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PS2_Compute_Values
	; Throttle (y1);;;;;;;;;;;;;;;;;;;;;;;;;
	movlw 0x32
	movwf b2
	movfw leftJoystickY
	call Divide_Integer
	btfsc b4,0
	subwf Throttle,f
	btfss b4,0
	addwf Throttle,f
	btfsc Throttle,7 ; if Throttle < 0 then set it to 0
	clrf Throttle

	movfw Throttle
	sublw 0x63 ; 99 - Throttle
	btfsc STATUS,C
	goto __next_
	movlw 0x63
	movwf Throttle

__next_
	; Yaw (x1);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movlw 0x04
	movwf b2
	movfw leftJoystickX
	call Divide_Integer
	movwf Yaw
	sublw 0x1E ; 30 - Yaw
	btfsc STATUS,C
	goto yaw_sign
	movlw 0x1E
	movwf Yaw
yaw_sign
	btfsc b4,0
	bcf Yaw,7
	btfss b4,0
	bsf Yaw,7	
	; Pitch (y2);;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movlw 0x04
	movwf b2
	movfw rightJoystickY
	call Divide_Integer
	movwf Pitch
	sublw 0x1E ; 30 - Pitch
	btfsc STATUS,C
	goto pitch_sign
	movlw 0x1E
	movwf Pitch
pitch_sign
	btfsc b4,0
	bsf Pitch,7
	btfss b4,0
	bcf Pitch,7
	; Roll (x2);;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movlw 0x04
	movwf b2
	movfw rightJoystickX
	call Divide_Integer
	movwf Roll
	sublw 0x1E ; 30 - Roll
	btfsc STATUS,C
	goto roll_sign
	movlw 0x1E
	movwf Roll
roll_sign
	btfsc b4,0
	bcf Roll,7
	btfss b4,0
	bsf Roll,7
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO READ DATA FROM THE PS2 CONTROLLER
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PS2_Read_Data
	;************** start sending ******************
	bcf PS2_ATT
	call delay_us_50
	call delay_us_50

	; start signal
	movlw 0x01
	call PS2_SPI_send
	; request status
	movlw 0x42
	call PS2_SPI_send
	; get status
	movlw 0x00
	call PS2_SPI_send
	; get left side buttons
	movlw 0x00
	call PS2_SPI_send
	movwf leftButtons
	; get right side buttons
	movlw 0x00
	call PS2_SPI_send
	movwf rightButtons	
	; get right joystick X value
	movlw 0x00
	call PS2_SPI_send
	movwf rightJoystickX
	; get right joystick Y value
	movlw 0x00
	call PS2_SPI_send
	movwf rightJoystickY
	; get left joystick X value
	movlw 0x00
	call PS2_SPI_send
	movwf leftJoystickX
	; get left joystick Y value
	movlw 0x00
	call PS2_SPI_send
	movwf leftJoystickY

	call delay_us_50
	call delay_us_50
	bsf PS2_ATT
	;************** end sending ******************
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO INITIALIZE THE PS2 CONTROLLER
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PS2_Set_Analog_Mode
	;/////// Send Commands ///////
	bcf PS2_ATT
	call delay_us_50
	call delay_us_50
	movlw 0x01
	call PS2_SPI_send
	movlw 0x42
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	call delay_us_50
	call delay_us_50
	bsf PS2_ATT
	;/////// End Sending ///////
	;call delay_us_50
	;/////// Send Commands ///////
	bcf PS2_ATT
	call delay_us_50
	call delay_us_50
	movlw 0x01
	call PS2_SPI_send
	movlw 0x43
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x01
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	call delay_us_50
	call delay_us_50
	bsf PS2_ATT
	;/////// End Sending ///////
	;call delay_us_50
	;/////// Send Commands ///////
	bcf PS2_ATT
	call delay_us_50
	call delay_us_50
	movlw 0x01
	call PS2_SPI_send
	movlw 0x44
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x01
	call PS2_SPI_send
	movlw 0x03
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	call delay_us_50
	call delay_us_50
	bsf PS2_ATT
	;/////// End Sending ///////
	;call delay_us_50
	;/////// Send Commands ///////
	bcf PS2_ATT
	call delay_us_50
	call delay_us_50
	movlw 0x01
	call PS2_SPI_send
	movlw 0x43
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x00
	call PS2_SPI_send
	movlw 0x5A
	call PS2_SPI_send
	movlw 0x5A
	call PS2_SPI_send
	movlw 0x5A
	call PS2_SPI_send
	movlw 0x5A
	call PS2_SPI_send
	movlw 0x5A
	call PS2_SPI_send
	call delay_us_50
	call delay_us_50
	bsf PS2_ATT
	;/////// End Sending ///////
	return
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION FOR SENDING AND READING DATA VIA SPI BUS (LSBFirst)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
PS2_SPI_send
	movwf outByte
	movlw 0x08
	movwf bits_counter
	clrf inByte
PS2_SPI_loop ; prepare the bit to clock
	btfss outByte,0
	bcf PS2_CMD
	btfsc outByte,0
	bsf PS2_CMD
	bcf PS2_CLK ; generate clock pulse
	call delay_us_50
	; read the data bit
	btfsc PS2_DAT
	bsf inByte,7
	bsf PS2_CLK ; end clock pulse
	call delay_us_50
	decfsz bits_counter,f
	goto PS2_next_bit
	goto PS2_end_sending
PS2_next_bit
	; move to next bit
	rrf outByte,f
	rrf inByte,f
	goto PS2_SPI_loop
PS2_end_sending
	movfw inByte
	return
