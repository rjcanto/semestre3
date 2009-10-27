/**
 * Segunda série de exercícios – Inverno de 2009/10
 * Grupo 1:
 * -> 30896: Ricardo Canto
 * -> 31401: Nuno Cancelo
 * -> 33595: Nuno Sousa
 * 
 * Exercicio 1:
 * Escreva, em assembly IA-32, a função xend, que converte um valor a 32 bits, passado como argumento, de 
 * formato big-endian para little-endian ou vice-versa.
 * 		unsigned int xend(unsigned int val);
 *
 * O objectivo foi tentar exectuar uma função que pudesse facilmente ser alterada no caso do argumento
 * passado tivesse mais ou menos do que 4 bytes. Vamos ler o primeiro byte enquanto não atingirmos o 
 * nº de bytes do argumento fazemos o shift para a esquerda e introduzimos o byte seguinte.
 * Apenas será necessário alterar o nº de bytes na linha assinalada abaixo.
 */

.intel_syntax noprefix
.text
.global xend

xend:
	/* Preambulo */
	push ebp
	mov ebp, esp	
	/**/
	
	xor eax,eax
	mov ecx, 4 		/* nº de bytes do argumento a tranformar: alterar para o desejado*/
	mov edx, [ebp+8]

ciclo:
	mov al, dl
	dec ecx
	jz fim
	shld eax,eax, 8
	shrd edx,edx, 8
	jmp ciclo
fim:
	mov [ebp+8], eax

	/* Epílogo */
	pop ebp
	ret
	/**/
