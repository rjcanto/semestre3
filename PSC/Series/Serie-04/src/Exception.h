/* ========================================================================== */
/*                                                                            */
/*   Exceptions.h                                                             */
/*   (c) 2010 Grupo1                                                          */
/*                                                                            */
/*   Description                                                              */
/*                                                                            */
/* ========================================================================== */

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <setjmp.h>

#define TRY jmp_buf jmp; switch (setjmp(jmp)){case0:
#define CATCH(E) break;case e;
#define THROW(E) longjmp(jmp,e);


#endif