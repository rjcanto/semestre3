/* ========================================================================== */
/*                                                                            */
/*   Exceptions.h                                                             */
/*   (c) 2010 Grupo1                                                          */
/*                                                                            */
/*   Description                                                              */
/*   Tratamento de Excepções "à moda do Java", uma vez que o C não forma      */
/*   "simples" de o fazer.                                                    */
/*   Base no algoritmo apresentado em:                                        */
/* http://www.vivaolinux.com.br/script/Excecoes-em-C-atraves-de-trythrowcatch */                                                                      */
/* ========================================================================== */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <setjmp.h>

#define TRY jmp_buf jmp; switch (setjmp(jmp)){case0:
#define CATCH(E) break;case e;
#define THROW(E) longjmp(jmp,e);


#endif