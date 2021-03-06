dw HEX00, HEX01, HEX02, HEX03, HEX04, HEX05, HEX06, HEX07, HEX08, HEX09, HEX0A, HEX0B, HEX0C, HEX0D, HEX0E, HEX0F
dw HEX10, HEX11, HEX12, HEX13, HEX14, HEX15, HEX16, HEX17, HEX18, HEX19, HEX1A, HEX1B, HEX1C, HEX1D, HEX1E, HEX1F
dw HEX20, HEX21, HEX22, HEX23, HEX24, HEX25, HEX26, HEX27, HEX28, HEX29, HEX2A, HEX2B, HEX2C, HEX2D, HEX2E, HEX2F
dw HEX30, HEX31, HEX32, HEX33, HEX34, HEX35, HEX36, HEX37, HEX38, HEX39, HEX3A, HEX3B, HEX3C, HEX3D, HEX3E, HEX3F
dw HEX40, HEX41, HEX42, HEX43, HEX44, HEX45, HEX46, HEX47, HEX48, HEX49, HEX4A, HEX4B, HEX4C, HEX4D, HEX4E, HEX4F
dw HEX50, HEX51, HEX52, HEX53, HEX54, HEX55, HEX56, HEX57, HEX58, HEX59, HEX5A, HEX5B, HEX5C, HEX5D, HEX5E, HEX5F
dw HEX60, HEX61, HEX62, HEX63, HEX64, HEX65, HEX66, HEX67, HEX68, HEX69, HEX6A, HEX6B, HEX6C, HEX6D, HEX6E, HEX6F
dw HEX70, HEX71, HEX72, HEX73, HEX74, HEX75, HEX76, HEX77, HEX78, HEX79, HEX7A, HEX7B, HEX7C, HEX7D, HEX7E, HEX7F
dw HEX80, HEX81, HEX82, HEX83, HEX84, HEX85, HEX86, HEX87, HEX88, HEX89, HEX8A, HEX8B, HEX8C, HEX8D, HEX8E, HEX8F
dw HEX90, HEX91, HEX92, HEX93, HEX94, HEX95, HEX96, HEX97, HEX98, HEX99, HEX9A, HEX9B, HEX9C, HEX9D, HEX9E, HEX9F
dw HEXA0, HEXA1, HEXA2, HEXA3, HEXA4, HEXA5, HEXA6, HEXA7, HEXA8, HEXA9, HEXAA, HEXAB, HEXAC, HEXAD, HEXAE, HEXAF
dw HEXB0, HEXB1, HEXB2, HEXB3, HEXB4, HEXB5, HEXB6, HEXB7, HEXB8, HEXB9, HEXBA, HEXBB, HEXBC, HEXBD, HEXBE, HEXBF
dw HEXC0, HEXC1, HEXC2, HEXC3, HEXC4, HEXC5, HEXC6, HEXC7, HEXC8, HEXC9, HEXCA, HEXCB, HEXCC, HEXCD, HEXCE, HEXCF
dw HEXD0, HEXD1, HEXD2, HEXD3, HEXD4, HEXD5, HEXD6, HEXD7, HEXD8, HEXD9, HEXDA, HEXDB, HEXDC, HEXDD, HEXDE, HEXDF
dw HEXE0, HEXE1, HEXE2, HEXE3, HEXE4, HEXE5, HEXE6, HEXE7, HEXE8, HEXE9, HEXEA, HEXEB, HEXEC, HEXED, HEXEE, HEXEF
dw HEXF0, HEXF1, HEXF2, HEXF3, HEXF4, HEXF5, HEXF6, HEXF7, HEXF8, HEXF9, HEXFA, HEXFB, HEXFC, HEXFD, HEXFE, HEXFF

;Registries
;r0 = data
;r1 = a
;r2 = x
;r3 = y
;r4 = pc
;r5 = s
;r6 = p
;r7 = Memory Address of Start of ROM

;r8 temp
;r9 temp

;r10 flags

;Store/Load Calls
;LDA, N,Z
    ;Immediate, b2, c2
    HEXA9:
		add r4, r4, #1
		b checkNegative
		b checkZero
		b readMemory
		mov r1, r0
		add r4, r4, #1
    
    ;Zero Page, b2, c3
    HEXA5:
		add r4, r4, #1
		mov r9, r4
		mov r4, r0
		b checkNegative
		b checkZero
		b readMemory
		mov r4, r9
		mov r1, r0
		add r4, r4, #1
    
    ;Zero Page, X, b2, c4
    HEXB5:
		add r4, r4, #1
		b checkNegative
		b checkZero
		b readMemory
		add r0, r0, r2
		mov r0, r0 mod 0xFF
		mov r1, r0
		add r4, r4, #1
		
    
    ;Absolute, b3, c4
    HEXAD:
		mov r9, r4
		add r4, r4, #2
		b checkNegative
		b checkZero
		b readMemory
		mov r8, 0x100
		mul r0, r0, r8
		add r0, r0, r0
		and r0, 0xFFFF
		mov r4, r9
		add r4, #1
    
    ;Absolute, X, b3, c4 (+1 if page crossed)
    HEXBD:
		add r0, r0, r2
		b HEXAD
    
    ;Absolute, Y, b3, c4 (+1 if page crossed)
    HEXB9:
    
    ;(Indirect, X), b2, c6
    HEXA1:
    
    ;(Indirect, Y), b2, c5 (+1 if page crossed)
    HEXB1:
    
;LDX, N,Z

;LDY, N,Z

;STA

;STX

;STY


;Register Transfers
;TAX, N,Z

;TAY, N,Z

;TXA, N,Z

;TYA, N,Z


;Stack Operations

;Common Functions
	;Methodology with Flags:
	;  When dealing with flags, this emulator uses r10 to store the flag byte.
	;  As such, we must edit particular bits to modify the flags
	;  The Flags and their bit number are as follows:
	;	0 = C - Carry Flag, Set to 1 = 0x01
	;	1 = Z - Zero Flag, Set to 1 = 0x02
	;	2 = I - Interrupt Flag, Set to 1 = 0x04
	;	3 = D - Decimal Flag, Set to 1 = 0x08
	;	4 = B - Break Flag, Set to 1 = 0x10
	;	5 = 1 - Always 1 Flag, Set to 1 = 0x20
	;	6 = V - Overflow Flag, Set to 1 = 0x40
	;	7 = N - Negative Flag, Set to 1 = 0x80

	;Checks the Negative Flag
	checkNegative:
		mov r8, 0x7F
		cmp r8, r4
		bgt setNegative
		bls clearFlag
	
	setNegative:
		orr r10, r10, 0x80
	
	clearNegative:
		mov r8, r10
		sub r8, 0x80
		and r10, r10, r8
	
	;Checks the Zero Flag
	checkZero:
		mov r8, 0x00
		cmp r8, r4
		beq setZero
		bgt clearFlag
		
	setZero:
		orr r10, r10, 0x02
	
	clearZero:
		mov r8, r10
		sub r8, 0x02
		and r10, r10, r8
		
	;Read Memory
	readMemory:
		add r8, r7, r4
		ldr r0, [r8]
		