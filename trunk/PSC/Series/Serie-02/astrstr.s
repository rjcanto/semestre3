/**
 * Segunda série de exercícios - Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 2:
 * Esta implementação é a representação equivalente em assembly do nosso
 * código em C.
 * Utilizamos os registos ESI e EDI como registos que contem os valores 
 * a serem indexados, tornando-se no mnemonica mais simples de lembrar na
 * implementação do código.
 * Utilizamos o registo EAX como endereço base para fazer a indexação e 
 * posteriormente conter o retorno final, poupando uma instrução MOV no
 * fim do código.
 * O registo EBX, ECX e EDX contem o endereço base da string a procurar, 
 * o caracter da 1a. string a ser comparado e o caracter da 2a. string 
 * respectivamente.
 */ 
 
.intel_syntax noprefix
.text
.global astrstr

astrstr:
	push ebp
	mov ebp, esp
	push ebx
	push esi
	push edi
	
	mov eax, [ebp + 8] /* char * str1 */
	mov ebx, [ebp + 12] /* const char * str2 */
	xor esi, esi
	xor edi, edi
	
	mov dl, byte ptr[ebx + esi]
	test dl,dl
	je fim
	
ciclo:
	mov cl, byte ptr[eax + edi]
	test cl, cl
	jz null
	
	se:
		mov dl, byte ptr[ebx + esi]
		cmp cl, dl
		jne senao
		inc esi
		mov dl, byte ptr[ebx + esi]
		test dl, dl
		jnz end_ciclo
		sub edi,esi
		inc edi
		add eax,edi

		jmp fim
	senao:
		sub edi,esi
		xor esi, esi
		
end_ciclo:
	inc edi
	jmp ciclo

null:
	xor eax ,eax
	
fim:

	pop edi
	pop esi
	pop ebx
	pop ebp
	
	ret
