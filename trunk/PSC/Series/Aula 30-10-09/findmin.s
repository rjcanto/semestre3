
  .intel_syntax noprefix
 
  .text
  
  .global findmin, _findmin
findmin:
_findmin:
  push ebp
  mov  ebp, esp
  push ebx
  push edi

  xor  edi, edi
  mov  ecx, [ebp + 16]
  test ecx, ecx
  jz   fim

  mov  ebx, [ebp + 8]
  mov  edi, ebx

  dec  ecx
  test ecx, ecx
  jz   fim
  
  add  ebx, [ebp + 12]

  push [ebp + 20]
  push ecx
  push [ebp + 12]
  push ebx
  call findmin
  add  esp, 16

  mov  ebx, eax
  push ebx
  push edi
  call [ebp + 20]
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
