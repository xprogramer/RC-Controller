Print_T
	; 0x01, 0x01, 0x7f, 0x01, 0x01 = T
	movlw 0x01
	call LCD_Send_Data
	movlw 0x01
	call LCD_Send_Data
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x01
	call LCD_Send_Data
	movlw 0x01
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_h	
	; 0x7f, 0x08, 0x04, 0x04, 0x78 = h
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x78
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
	
Print_r	
	; 0x7c, 0x08, 0x04, 0x04, 0x08 = r
	movlw 0x7C
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_o	
	; 0x38, 0x44, 0x44, 0x44, 0x38 = o
	movlw 0x38
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x38
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_t	
	; 0x04, 0x3f, 0x44, 0x40, 0x20 = t
	movlw 0x04
	call LCD_Send_Data
	movlw 0x3F
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x40
	call LCD_Send_Data
	movlw 0x20
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_l	
	; 0x00, 0x41, 0x7f, 0x40, 0x00 = l
	movlw 0x00
	call LCD_Send_Data
	movlw 0x41
	call LCD_Send_Data
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x40
	call LCD_Send_Data
	movlw 0x00
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_e
	; 0x38, 0x54, 0x54, 0x54, 0x18 = e
	movlw 0x38
	call LCD_Send_Data
	movlw 0x54
	call LCD_Send_Data
	movlw 0x54
	call LCD_Send_Data
	movlw 0x54
	call LCD_Send_Data
	movlw 0x18
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_P
	; 0x7F, 0x09, 0x09, 0x09, 0x06 = P
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x09
	call LCD_Send_Data
	movlw 0x09
	call LCD_Send_Data
	movlw 0x09
	call LCD_Send_Data
	movlw 0x06
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_i
	; 0x00, 0x44, 0x7D, 0x40, 0x00 = i
	movlw 0x00
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x7D
	call LCD_Send_Data
	movlw 0x40
	call LCD_Send_Data
	movlw 0x00
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_c
	; 0x38, 0x44, 0x44, 0x44, 0x20 = c
	movlw 0x38
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x20
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_R
	; 0x7F, 0x09, 0x19, 0x29, 0x46 = R
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x09
	call LCD_Send_Data
	movlw 0x19
	call LCD_Send_Data
	movlw 0x29
	call LCD_Send_Data
	movlw 0x46
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_Y
	; 0x03, 0x04, 0x78, 0x04, 0x03 = Y
	movlw 0x03
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x78
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x03
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_a
	; 0x20, 0x54, 0x54, 0x54, 0x78 = a
	movlw 0x20
	call LCD_Send_Data
	movlw 0x54
	call LCD_Send_Data
	movlw 0x54
	call LCD_Send_Data
	movlw 0x54
	call LCD_Send_Data
	movlw 0x78
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_w
	; 0x3C, 0x40, 0x30, 0x40, 0x3C = w
	movlw 0x3C
	call LCD_Send_Data
	movlw 0x40
	call LCD_Send_Data
	movlw 0x30
	call LCD_Send_Data
	movlw 0x40
	call LCD_Send_Data
	movlw 0x3C
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_d
	; 0x38, 0x44, 0x44, 0x48, 0x7F = d
	movlw 0x38
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	movlw 0x48
	call LCD_Send_Data
	movlw 0x7F
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_x
	; 0x44, 0x28, 0x10, 0x28, 0x44 = x
	movlw 0x44
	call LCD_Send_Data
	movlw 0x28
	call LCD_Send_Data
	movlw 0x10
	call LCD_Send_Data
	movlw 0x28
	call LCD_Send_Data
	movlw 0x44
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_G
	; 0x3E, 0x41, 0x41, 0x51, 0x32 = G
	movlw 0x3E
	call LCD_Send_Data
	movlw 0x41
	call LCD_Send_Data
	movlw 0x41
	call LCD_Send_Data
	movlw 0x51
	call LCD_Send_Data
	movlw 0x32
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_M
	; 0x7F, 0x02, 0x04, 0x02, 0x7F = M
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x02
	call LCD_Send_Data
	movlw 0x04
	call LCD_Send_Data
	movlw 0x02
	call LCD_Send_Data
	movlw 0x7F
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_0
	; 0x3E, 0x51, 0x49, 0x45, 0x3E = 0
	movlw 0x3E
	call LCD_Send_Data
	movlw 0x51
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x45
	call LCD_Send_Data
	movlw 0x3E
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_1
	; 0x00, 0x42, 0x7F, 0x40, 0x00 = 1
	movlw 0x00
	call LCD_Send_Data
	movlw 0x42
	call LCD_Send_Data
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x40
	call LCD_Send_Data
	movlw 0x00
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_2
	; 0x42, 0x61, 0x51, 0x49, 0x46 = 2
	movlw 0x42
	call LCD_Send_Data
	movlw 0x61
	call LCD_Send_Data
	movlw 0x51
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x46
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_3
	; 0x21, 0x41, 0x45, 0x4B, 0x31 = 3
	movlw 0x21
	call LCD_Send_Data
	movlw 0x41
	call LCD_Send_Data
	movlw 0x45
	call LCD_Send_Data
	movlw 0x4B
	call LCD_Send_Data
	movlw 0x31
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_4
	; 0x18, 0x14, 0x12, 0x7F, 0x10 = 4
	movlw 0x18
	call LCD_Send_Data
	movlw 0x14
	call LCD_Send_Data
	movlw 0x12
	call LCD_Send_Data
	movlw 0x7F
	call LCD_Send_Data
	movlw 0x10
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_5
	; 0x27, 0x45, 0x45, 0x45, 0x39 = 5
	movlw 0x27
	call LCD_Send_Data
	movlw 0x45
	call LCD_Send_Data
	movlw 0x45
	call LCD_Send_Data
	movlw 0x45
	call LCD_Send_Data
	movlw 0x39
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_6
	; 0x3C, 0x4A, 0x49, 0x49, 0x30 = 6
	movlw 0x3C
	call LCD_Send_Data
	movlw 0x4A
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x30
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_7
	; 0x01, 0x71, 0x09, 0x05, 0x03 = 7
	movlw 0x01
	call LCD_Send_Data
	movlw 0x71
	call LCD_Send_Data
	movlw 0x09
	call LCD_Send_Data
	movlw 0x05
	call LCD_Send_Data
	movlw 0x03
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_8
	; 0x36, 0x49, 0x49, 0x49, 0x36 = 8
	movlw 0x36
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x36
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return
	
Print_9
	; 0x06, 0x49, 0x49, 0x29, 0x1E = 9
	movlw 0x06
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x49
	call LCD_Send_Data
	movlw 0x29
	call LCD_Send_Data
	movlw 0x1E
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return

Print_minus
	; 0x08, 0x08, 0x08, 0x08, 0x08 = -
	movlw 0x08
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return

Print_plus
	; 0x08, 0x08, 0x36, 0x08, 0x08 = +
	movlw 0x08
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x36
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	movlw 0x08
	call LCD_Send_Data
	clrw
	call LCD_Send_Data
	return