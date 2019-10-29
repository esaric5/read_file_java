#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nicslu.h"
#include "nicslu_util.h"

int callResidual(uint__t n, real__t *ax, uint__t *ai, uint__t *ap, real__t *x, \
	real__t *b, 	real__t *err, int norm, int mode) {
	real__t myerr;
	int ret=NicsLU_Residual(n, ax, ai, ap, x, b, &myerr, norm, mode);
	printf("%lf\n", myerr);
	err=&myerr;
	return ret;
}


int solveMatrix(uint__t *n, uint__t *nnz, uint__t *ai, uint__t *ap, real__t *ax, real__t *x, real__t *b)
{
	int ret;
	uint__t i;
	SNicsLU *nicslu;
	real__t err;
	uint__t *Ap, *Ai;
	real__t *Ax, *B, *X;

	/*
	if (argc == 1)
	{
		printf("usage: demop <#threads>\n");
		return -1;
	}*/

	Ax = NULL;
	Ai = NULL;
	Ap = NULL;
	X = NULL;
	B = NULL;
	/*
	nicslu = (SNicsLU *)malloc(sizeof(SNicsLU));
	NicsLU_Initialize(nicslu);*/

	ret = NicsLU_ReadTripletColumnToSparse("ASIC_100k.mtx", n, nnz, &Ax, &Ai, &Ap);
	if (ret != NICS_OK) {
		printf("%d", ret);
		return 0;
	}

	for (int i=0;i<*nnz;i++) {
		ax[i]=Ax[i];
		ai[i]=Ai[i];
		if (i<=*n) ap[i]=Ap[i];
	}

	x = (real__t *)malloc(sizeof(real__t)*(*n+*n));
	b = x + *n;
	for (i=0; i<*n+*n; ++i) x[i] = 1.;

	return 1;
	/*
	NicsLU_CreateMatrix(nicslu, n, nnz, ax, ai, ap);
	nicslu->cfgf[0] = 1.;
	printf("%u\n", nicslu->n);

	NicsLU_Analyze(nicslu);
	printf("analysis time: %.8g\n", nicslu->stat[0]);

	ret = NicsLU_CreateScheduler(nicslu);
	printf("time of creating scheduler: %.8g\n", nicslu->stat[4]);
	printf("suggestion: %s.\n", ret==0?"parallel":"sequential");

	NicsLU_CreateThreads(nicslu, argc, TRUE);
	printf("total cores: %d, threads created: %d\n", (int)(nicslu->stat[9]), (int)(nicslu->cfgi[5]));

	NicsLU_BindThreads(nicslu, FALSE);

	NicsLU_Factorize_MT(nicslu);
	printf("factorization time: %.8g\n", nicslu->stat[1]);

	NicsLU_ReFactorize_MT(nicslu, ax);
	printf("re-factorization time: %.8g\n", nicslu->stat[2]);

	NicsLU_Solve(nicslu, x);
	printf("substitution time: %.8g\n", nicslu->stat[3]);

	NicsLU_Residual(n, ax, ai, ap, x, b, &err, 1, 0);
	printf("Ax-b (1-norm): %.8g\n", err);
	NicsLU_Residual(n, ax, ai, ap, x, b, &err, 2, 0);
	printf("Ax-b (2-norm): %.8g\n", err);
	NicsLU_Residual(n, ax, ai, ap, x, b, &err, 0, 0);
	printf("Ax-b (infinite-norm): %.8g\n", err);

	printf("NNZ(L+U-I): %ld\n", nicslu->lu_nnz);

	NicsLU_Flops(nicslu, NULL);
	NicsLU_Throughput(nicslu, NULL);
	NicsLU_ConditionNumber(nicslu, NULL);
	printf("flops: %.8g\n", nicslu->stat[5]);
	printf("throughput (bytes): %.8g\n", nicslu->stat[12]);
	printf("condition number: %.8g\n", nicslu->stat[6]);
	NicsLU_MemoryUsage(nicslu, NULL);
	printf("memory (Mbytes): %.8g\n", nicslu->stat[21]/1024./1024.);*/
/*
EXIT:
	NicsLU_Destroy(nicslu);
	free(ax);
	free(ai);
	free(ap);
	free(nicslu);
	free(x);
	return 0;*/
}
