
  .intel_syntax noprefix
 
  .text
  
  .global findmin4, _findmin4
findmin4:
_findmin4:
  push ebp
  mov  ebp, esp
  push ebx
  push edi

  xor  edi, edi
  mov  ecx, [ebp + 12]
  test ecx, ecx
  jz   fim

  mov  ebx, [ebp + 8]
  mov  edi, [ebx]

  dec  ecx
  test ecx, ecx
  jz   fim
  
  add  ebx, 4

  push [ebp + 16]
  push ecx
  push ebx
  call findmin4
  add  esp, 12

  mov  ebx, eax
  push ebx
  push edi
  call [ebp + 16]
  add  esp, 8

  cmp  eax, 0
  jle  fim
  
  mov  edi, ebx
fim:
  mov  eax, edi
  pop  edi
  pop  ebx
  pop  ebp
  ret
