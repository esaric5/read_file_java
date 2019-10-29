import java.lang.Integer;

public class runme {
  static {
    System.loadLibrary("demop");
  }

  public static void main(String[] args) {
    int n=99340, nnz=954163;
    uintArray ap=new uintArray(n+1);
    uintArray ai=new uintArray(nnz);
    doubleArray ax=new doubleArray(nnz);
    doubleArray b=new doubleArray(n);
    doubleArray x=new doubleArray(n+n);
    uintArray N=new uintArray(1);
    uintArray NNZ=new uintArray(1);
    doubleArray err=new doubleArray(1);

    N.setitem(0, n);
    NNZ.setitem(0, nnz);

    int ret=demop.solveMatrix(N.cast(), NNZ.cast(), ai.cast(), ap.cast(), ax.cast(), x.cast(), b.cast());
    n=N.getitem(0);
    nnz=NNZ.getitem(0);

    SNicsLU nicslu =  new SNicsLU();
    ret= demop.NicsLU_Initialize(nicslu);

    ret=demop.NicsLU_CreateMatrix(nicslu, n, nnz, ax.cast(), ai.cast(), ap.cast());
    doubleArray cfgf=doubleArray.frompointer(nicslu.getCfgf());
    cfgf.setitem(0, 1.0);
    nicslu.setCfgf(cfgf.cast());

    demop.NicsLU_Analyze(nicslu);
    doubleArray stat=doubleArray.frompointer(nicslu.getStat());
    System.out.printf("Analysis time: %.8g\n", stat.getitem(0));

    ret=demop.NicsLU_CreateScheduler(nicslu);
    System.out.printf("Time of creating scheduler: %.8g\n", stat.getitem(4));
    System.out.printf("Suggestion: %s.\n", ret==0?"parallel":"sequential");

    uintArray cfgi=uintArray.frompointer(nicslu.getCfgi());

    demop.NicsLU_CreateThreads(nicslu, Integer.parseInt(args[0]), true);
    System.out.printf("Total cores: %d, threads created: %d\n", (int)stat.getitem(9), (int)cfgi.getitem(5));

    demop.NicsLU_BindThreads(nicslu, false);

    demop.NicsLU_Factorize_MT(nicslu);
    System.out.printf("Factorization time: %.8g\n", stat.getitem(1));

    demop.NicsLU_ReFactorize_MT(nicslu, ax.cast());
    System.out.printf("Re-factorization time: %.8g\n", stat.getitem(2));

    demop.NicsLU_Solve(nicslu, x.cast());
    System.out.printf("Substitution time: %.8g\n", stat.getitem(3));
    /*
    ret=demop.callResidual(n, ax.cast(), ai.cast(), ap.cast(), x.cast(), b.cast(), err.cast(), 1, 0);
    System.out.println(ret);
    System.out.printf("Ax-b (1-norm): %.8g\n", err.getitem(0));

    demop.NicsLU_Residual(n, ax.cast(), ai.cast(), ap.cast(), x.cast(), b.cast(), err.cast(), 2, 0);
    System.out.printf("Ax-b (2-norm): %.8g\n", err.getitem(0));*/
    demop.NicsLU_Flops(nicslu, null);
    demop.NicsLU_Throughput(nicslu, null);
    demop.NicsLU_ConditionNumber(nicslu, null);
    System.out.printf("Flops: %.8g\n", stat.getitem(5));
  	System.out.printf("Throughput (bytes): %.8g\n", stat.getitem(12));
  	System.out.printf("Condition number: %.8g\n", stat.getitem(6));
  	demop.NicsLU_MemoryUsage(nicslu, null);
  	System.out.printf("memory (Mbytes): %.8g\n", stat.getitem(21)/1024./1024.);

  }
}
