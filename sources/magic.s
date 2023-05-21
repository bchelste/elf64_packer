bits 64
default rel
global _start

_start:
			cdq											; convert double to quad, 8 bite
			imul	eax, 0

			mov		edi, 1								; RDI, arg #1: fd
			lea		rsi, [rel message]					; RSI, arg #2: char *
			mov		edx, 14								; RDX, arg #3: len
			add		eax, 1								; RAX, arg #4 or #number of system call (== write())
			syscall

			lea		rax, [original_entry]
			add		rax, qword [original_entry]
			sub		rax, qword [encrypted_entry]		; QWORD [PTR]: the address expression will have the size of a 4-word (8 bytes)
			sub		rax, original_entry
			push	rax

			lea		rdi, [encrypted_code]
			add		rdi, qword [encrypted_code]
			sub		rdi, qword [encrypted_entry]
			sub		rdi, encrypted_code

			mov		rcx, qword [encrypted_size]

			mov		rax, qword [key]

decrypt_code:	
			xor		byte [rdi], al						; xor of RDI and last 8 bits of EAX
			ror		rax, 1								; rotate right 1 bit
			add		rdi, 1								; increment of RDI 1 step
			loop	decrypt_code						; loop
			mul		ecx									; counter from rcx
			ret											; return

message			db '....WOODY....',10					; determine bite
original_entry	dq 0x1000111001111111					; determine 8 bites
encrypted_code	dq 0x1000011001110011
encrypted_size	dq 0x1001001001001100
key				dq 0x1001100001001100
encrypted_entry	dq 0x1111111111110011
