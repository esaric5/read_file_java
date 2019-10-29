%module demop
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nicslu.h"
#include "nicslu_util.h"
%}

%typemap(jstype) real__t "double"
%typemap(jtype) real__t "double"
%typemap(jni) real__t "jdouble"
%typemap(javain) real__t "$javainput"
%typemap(javaout) real__t { return $jnicall; }

%typemap(in) real__t {
     $1 = (real__t)$input;
}

%typemap(out) real__t {
     $result = (jdouble)$1;
}

%typemap(jstype) uint__t "int"
%typemap(jtype) uint__t "int"
%typemap(jni) uint__t "jint"
%typemap(javain) uint__t "$javainput"
%typemap(javaout) uint__t { return $jnicall; }

%typemap(in) uint__t {
     $1 = (uint__t)$input;
}

%typemap(out) uint__t {
     $result = (jint)$1;
}

%typemap(jstype) bool__t "boolean"
%typemap(jtype) bool__t "boolean"
%typemap(jni) bool__t "jboolean"
%typemap(javain) bool__t "$javainput"
%typemap(javaout) bool__t { return $jnicall; }

%typemap(in) bool__t {
     $1 = (bool__t)$input;
}

%typemap(out) bool__t {
     $result = (jboolean)$1;
}

%include "carrays.i"
%array_class(uint__t, uintArray);
%array_class(real__t, doubleArray);

%include "nicslu.h"

extern int callResidual(uint__t n, real__t *ax, uint__t *ai, uint__t *ap, real__t *x, real__t *b, \
					real__t *err, int norm, int mode);

extern int solveMatrix(uint__t *n, uint__t *nnz, uint__t *ai, uint__t *ap, real__t *ax, real__t *x, real__t *b);
