cmd_Release/obj.target/awslambda.node := g++ -shared -pthread -rdynamic -m64 -L/local/p4clients/pkgbuild-vb5_8/workspace/build/LambdaSandboxNodeJs/LambdaSandboxNodeJs-1.0.106.0/AL2012/DEV.STD.PTHREAD/build/private/tmp/brazil-path/lib.libfarm/lib -llambdaio -llambdaruntime -llambdaipc -llambdalog  -Wl,-soname=awslambda.node -o Release/obj.target/awslambda.node -Wl,--start-group Release/obj.target/awslambda/src/awslambda.o -Wl,--end-group 