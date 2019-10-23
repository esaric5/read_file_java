%module nicslu_readfile
%{
#include "nicslu_util.h"
#include "nicslu.h"
#include <locale.h>
%}

#define ROW_LENGTH 1024
#define FAIL(code)	((code) < NICS_OK)

static int ReadHeader3(FILE *f, uint__t *m, uint__t *n, uint__t *nnz);
static int ReadHeader2(FILE *f, uint__t *m, uint__t *n, uint__t *nnz);
extern int NicsLU_ReadTripletColumnToSparse(char *file, uint__t *n, uint__t *nnz, real__t **ax, uint__t **ai, uint__t **ap);
extern int NicsLU_ReadTripletRowToSparse(char *file, uint__t *n, uint__t *nnz,  real__t **ax, uint__t **ai, uint__t **ap);
