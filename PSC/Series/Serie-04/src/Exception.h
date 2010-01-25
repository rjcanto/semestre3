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

#define TRY jmp_buf jmp; switch (setjmp(jmp)){case 0:
#define CATCH(e) break;case e:
#define THROW(e) longjmp(jmp,e);


#endif
