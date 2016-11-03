RF24_write_reg macro reg,val
	bcf RF24_CSN
	movlw reg
	call RF24_SPI_send ; REG
	movlw val
	call RF24_SPI_send ; VAL
	bsf RF24_CSN
	endm

RF24_write_reg_buffer macro reg,c1,c2,c3,c4,c5
	bcf RF24_CSN
	movlw reg
	call RF24_SPI_send ; REG
	movlw c1
	call RF24_SPI_send ; VAL
	movlw c2
	call RF24_SPI_send ; VAL
	movlw c3
	call RF24_SPI_send ; VAL
	movlw c4
	call RF24_SPI_send ; VAL
	movlw c5
	call RF24_SPI_send ; VAL
	bsf RF24_CSN
	endm



;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO TRANSMIT DATA
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RF24_Transmit
	; Power up
	;RF24_write_reg 0x20,0x1E

	 ; Flush TX
	bcf RF24_CSN
	movlw 0xE1
	call RF24_SPI_send
	bsf RF24_CSN

	 ; Write in the payload
	bcf RF24_CSN
	movlw 0xA0
	call RF24_SPI_send
	movfw Throttle ; send Throttle
	call RF24_SPI_send
	movfw Pitch ; send Pitch
	call RF24_SPI_send
	movfw Roll ; send Roll
	call RF24_SPI_send
	movfw Yaw ; send Yaw
	call RF24_SPI_send
	movfw leftButtons ; send left commands
	call RF24_SPI_send
	movfw rightButtons ; send right commands
	call RF24_SPI_send
	bsf RF24_CSN

	; Start transmission
	bsf RF24_CE
	call delay_ms_100
	;call delay_us_50
	bcf RF24_CE
	call delay_ms_100

	; Power down
	RF24_write_reg 0x20,0x1C 
	; Clear STATUS flags
	RF24_write_reg 0x27,0x70
	; Power up
	RF24_write_reg 0x20,0x1E
	; Flush RX and TX buffers
	RF24_write_reg 0xE2,0xE1
	return

	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO CONFIGURE THE DEVICE AS TRANSMITTER
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RF24_Config_TX
	bcf RF24_CE
	bsf RF24_CSN

	; Clear STATUS flags
	RF24_write_reg 0x27,0x70

	; Configure the device as transmitter
	RF24_write_reg 0x20,0x1C

	; Write RX address (Pipe 0) 9A:FE:BF:ED:0C
	RF24_write_reg_buffer 0x2A,0x9A,0xFE,0xBF,0xED,0x0C

	; Write TX address 9A:FE:BF:ED:0C
	RF24_write_reg_buffer 0x30,0x9A,0xFE,0xBF,0xED,0x0C

	; Set the address width to 5
	RF24_write_reg 0x23,0x03

	; Set the radio channel to CHANNEL
	RF24_write_reg 0x25,CHANNEL

	; Set the retries to 4000us and 15
	RF24_write_reg 0x24,0xFF

	; Set the device debit as 0dBm and 250 kbps
	RF24_write_reg 0x26,0x26

	; Set the PAYLOAD size to 7
	RF24_write_reg 0x31,0x07

	; Disable Dynamic Payload
	RF24_write_reg 0x1C,0x00

	; Power up the device as transmitter
	RF24_write_reg 0x20,0x1E

	; Flush RX and TX buffers
	RF24_write_reg 0xE2,0xE1

	return


	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; FUNCTION TO SEND AND READ DATA VIA SPI BUS (MSBFirst)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
RF24_SPI_send
	movwf outByte
	movlw 0x08
	movwf bits_counter
	clrf inByte
RF24_SPI_loop 
	; send data bits
	btfss outByte,7
	bcf RF24_MOSI
	btfsc outByte,7
	bsf RF24_MOSI
	bsf RF24_SCK
	; read data bits
	btfsc RF24_MISO
	bsf inByte,0
	btfss RF24_MISO
	bcf inByte,0
	bcf RF24_SCK
	decfsz bits_counter,f
	goto RF24_next_bit
	goto RF24_end_sending
RF24_next_bit
	; move to next bit
	rlf outByte,f
	rlf inByte,f
	goto RF24_SPI_loop
RF24_end_sending
	movfw inByte
	return