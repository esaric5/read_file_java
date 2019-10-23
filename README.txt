NOTE: Before you copy/paste commands below, make sure you add ASIC_100k.mtx to current folder and set own library paths.

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/esaric/Desktop/NICSLU-master/read_file_java
swig -java  -o nicslu_readfile_wrap.c nicslu_readfile.i
gcc -c -fPIC nicslu_readfile.c nicslu_readfile_wrap.c  -I"/usr/lib/jvm/java-11-openjdk-amd64/include" -I"/usr/lib/jvm/java-11-openjdk-amd64/include/linux"
gcc -shared   nicslu_readfile.o  nicslu_readfile_wrap.o -o libnicslu_readfile.so -lrt -lpthread -lm
swig -java  -o demop_wrap.c demop.i
gcc -c -fPIC demop.c demop_wrap.c  -I"/usr/lib/jvm/java-11-openjdk-amd64/include" -I"/usr/lib/jvm/java-11-openjdk-amd64/include/linux"
gcc -shared  demop.o  demop_wrap.o libnicslu_readfile.so -o libdemop.so -lrt -lpthread -lm
javac runme.java
java runme

