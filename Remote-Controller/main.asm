	LIST p=16F84
	#include<p16F84.inc>

	__CONFIG _CP_OFF & _WDT_OFF & _PWRTE_ON & _HS_OSC

OPTIONVAL EQU H'0008'

BANK0 macro
	bcf STATUS,RP0
	endm

BANK1 macro
	bsf STATUS,RP0
	endm

#define CHANNEL 0x3B

#define LCD_SDA PORTB, 7
#define LCD_CLK PORTB, 0
#define LCD_RST PORTB, 1
#define LCD_SCE PORTB, 2
#define LCD_DC  PORTB, 3

#define PS2_CMD PORTB, 7 ; orange
#define PS2_DAT PORTB, 6 ; brown
#define PS2_CLK PORTB, 5 ; blue
#define PS2_ATT PORTB, 4 ; yellow


#define RF24_MISO PORTB,6

#define RF24_MOSI PORTA,0
#define RF24_SCK  PORTA,1
#define RF24_CE   PORTA,2
#define RF24_CSN  PORTA,3


	CBLOCK 0x00C
	b1             : 1
	b2             : 1
	b3             : 1
	b4             : 1
	b5             : 1
	bits_counter   : 1
	outByte        : 1
	inByte         : 1
	column         : 1
	line           : 1
	tmp1           : 1
	tmp2           : 1	
	Throttle 	   : 1
	Yaw 		   : 1
	Roll 		   : 1
	Pitch 		   : 1
	rightButtons   : 1
	leftButtons    : 1
	rightJoystickX : 1
	leftJoystickX  : 1
	rightJoystickY : 1
	leftJoystickY  : 1
	ENDC

	ORG 0x000
	goto init

init
	clrf PORTA
	clrf PORTB
	BANK1
	movlw OPTIONVAL
	movwf OPTION_REG
	movlw 0x0C
	movwf FSR
erase
	clrf INDF
	incf FSR,f
	btfss FSR,6
	goto erase
	btfss FSR,4
	goto erase
	;;;;
	clrf PORTB
	bsf PS2_DAT
	clrf PORTA
	bsf RF24_MISO
	BANK0
	bsf PS2_CLK
	clrf Throttle
	clrf Pitch
	clrf Roll
	clrf Yaw
	clrf column
	clrf line
	goto start


start
	; Setup the radio device
	call RF24_Config_TX

	; Setup the LCD device
	call LCD_SETUP
	; Print the string labels
	call LCD_Print_Strings

	; Setup the PS2 controller
	call PS2_Set_Analog_Mode

	goto loop

loop
	
	; read data from the PS2 controller
	call PS2_Read_Data
	call PS2_Compute_Values

	; print the Throttle value
	clrf line
	movlw 0x3C
	movwf column
	call LCD_Set_Cursor
	movfw Throttle
	call LCD_Print_Value

	; print the Pitch value
	movlw 0x1
	movwf line
	call LCD_Set_Cursor
	movfw Pitch
	call LCD_Print_Value

	; print the Roll value
	movlw 0x2
	movwf line
	call LCD_Set_Cursor
	movfw Roll
	call LCD_Print_Value

	; print the Yaw value
	movlw 0x3
	movwf line
	call LCD_Set_Cursor
	movfw Yaw
	call LCD_Print_Value


	; send the control values to the quadcopter
	call RF24_Transmit

	call delay_ms_100
	goto loop





#include "LCD_NOKIA_5110.inc"
#include "PS2_controller.inc"
#include "nRF24L01.inc"

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTIONS TO MAKE DELAY
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
delay_us_50
	movlw 0x0F ; 15x3+4 =  49us
	movwf tmp1
delay_50us_1
	decfsz tmp1,f
	goto delay_50us_1
	return


delay_ms_100
	movlw 0x64
	movwf tmp1
delay_100ms_1
	movlw 0xFA
	movwf tmp2
delay_100ms_2
	nop
	decfsz tmp2,f
	goto delay_100ms_2
	decfsz tmp1,f
	goto delay_100ms_1
	return


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTIONS TO DIVIDE TWO NUMBERS AND GET AN INTEGER RESULT
; b1 : dividend
; b2 : devisor
; b3 : quotient
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
Divide_Integer
	clrf b3
	movwf b1
	sublw 0x7B ; 123 - b1
	btfsc STATUS,Z
	goto div_end
	btfss STATUS,C
	goto t_sup
	goto t_inf
t_sup
	movlw 0x7B
	subwf b1,f
	bsf b4,0
	goto div_loop
t_inf
	movwf b1
	movwf b1
	bcf b4,0
div_loop
	movfw b2
	subwf b1,w ; b1 - b2
	btfss STATUS,C
	goto div_end
	movwf b1
	incf b3,f
	goto div_loop
div_end
	movfw b3
	return

	END