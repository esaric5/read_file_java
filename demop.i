%module demop
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nicslu.h"
#include "nicslu_util.h"
%}

%include "nicslu.h"
extern int solveMatrix(int argc);
