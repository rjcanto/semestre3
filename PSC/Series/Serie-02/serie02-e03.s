/**
 * Segunda série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 3:
 * 
 */ 
 
.intel_syntax noprefix
.text
.global apply_if

apply_if:
	push ebp
	mov ebp, esp
	push edi
	push esi
	push ebx

	xor ebx, ebx			/*contador de vezes que action e' chamada*/
	mov esi, [ebp+0x8]		/*inicio da estrutura*/
	mov edi, [ebp+0x10]		/*num elementos*/
	test edi, edi
	jz fim
ciclo:
	push [ebp+0x14]		/*filter*/
	push esi
	call [ebp+0x18]
	add esp,8
	cmp eax,0x0
	je no_action	
	inc ebx
	push esi
	call [ebp+0x1c]
	add esp, 4
no_action:
	dec edi
	jz fim
	add esi, [ebp+0xc]
	jmp ciclo 
fim:
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
