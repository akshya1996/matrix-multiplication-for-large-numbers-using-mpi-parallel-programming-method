# replace hello.c with your own source code file name
filename=hello.c
output=hello

p10=10.0.0.10
p15=10.0.0.15
p16=10.0.0.16
p18=10.0.0.18

# compile the source code
mpicc -o $output $filename 

# copy the executable file to other slaves
scp $output $USER@$p15:~/ 
scp $output $USER@$p16:~/ 
scp $output $USER@$p18:~/ 

# deploy the program to 26 processors
mpirun -n 26 --hostfile hostfile ./$output
