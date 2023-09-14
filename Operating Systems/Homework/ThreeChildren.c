#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <sys/wait.h>

int main(int argc, char *argv[])
{
int fd[2]; //creates pipe fd
pipe(fd);

int fd2[2]; //creates pipe fd2
pipe(fd2);

int fd3[2]; //creates pipe fd3
pipe(fd3);

int t,t1,t2,t3; 
t=atoi(argv[1]);
int array[10];

printf("number of children: %d\n", t); 

if(t==1){
t1 = atoi(argv[2]);

 printf("I am Parent with pid: (pid:%d) sending %d to one of my children\n", (int) getpid(),t1);
    int rc = fork();
    if (rc < 0) {
       // fork failed; exit
        fprintf(stderr, "fork failed\n");
         exit(1);
        
        } else if (rc == 0) {
        array[0] = 0;
        array[1] = 1;
        close(fd[0]);
           
         
        int i;
        for(i=2; i<t1; i++){  
          array[i] = array[i - 1] + array[i-2];
         }
          write(fd[1], &array[t1-1], sizeof(array[t1-1]));
          printf("I am child with pid: (pid:%d), sending %d to my parent\n", (int) getpid(),  array[t1-1]);
         close(fd[1]);
        exit(0);
    }
   else {
        int sum1;
        int final=0;
        close(fd[1]);
        read(fd[0], &sum1, sizeof(sum1));
        final = sum1;
        close(fd[0]);
        printf("I am parent with (pid:%d) receiving %d, the sum is %d\n" , (int) getpid(),sum1, final);
    }
}

if(t==2){
t1 = atoi(argv[2]);
t2 = atoi(argv[3]);

 printf("I am Parent with pid: (pid:%d) sending %d to one of my children, %d to one of my children\n", (int) getpid(),t1,t2);
    int rc0 = fork();
    if (rc0 < 0) {
       // fork failed; exit
        fprintf(stderr, "fork failed\n");
         exit(1);
        
        } else if (rc0 == 0) {
        array[0] = 0;
        array[1] = 1;
        close(fd[0]);
           
        int i;
        for(i=2; i<t1; i++){  
          array[i] = array[i - 1] + array[i-2];
         }
          write(fd[1], &array[t1-1], sizeof(array[t1-1]));
          printf("I am child with pid: (pid:%d), sending %d to my parent\n", (int) getpid(),  array[t1-1]);
         close(fd[1]);
        exit(0);
    }
    int rc1=fork();
    if (rc1==0){
        array[0] = 0;
        array[1] = 1;
        close(fd2[0]);

        int k;
        for(k=2; k<t2; k++){  
          array[k] = array[k - 1] + array[k-2];
         }
          write(fd2[1], &array[t2-1], sizeof(array[t2-1]));
          printf("I am child with pid: (pid:%d), sending %d to my parent\n", (int) getpid(),  array[t2-1]);
         close(fd2[1]);
        exit(0);
   }
   else {
        int sum1, sum2;
        int final=0;
        close(fd[1]);
        read(fd[0], &sum1, sizeof(sum1));
        final = sum1;

        close(fd2[1]);
        read(fd2[0], &sum2, sizeof(sum2));
        final = final +sum2;

        close(fd[0]);
        close(fd2[0]);
        printf("I am parent with (pid:%d) receiving %d and %d, the sum is %d \n" , (int) getpid(),sum1,sum2, final);
    }
}

if(t==3){
t1 = atoi(argv[2]);
t2 = atoi(argv[3]);
t3 = atoi(argv[4]);

 printf("I am Parent with pid: (pid:%d) sending %d to one of my children, %d to one of my children,  %d to one of my children\n", (int) getpid(),t1,t2,t3);
    int rc2 = fork();
    if (rc2 < 0) {
       // fork failed; exit
        fprintf(stderr, "fork failed\n");
         exit(1);
        
        } else if (rc2 == 0) {
        array[0] = 0;
        array[1] = 1;
        close(fd[0]);
           
        int i;
        for(i=2; i<t1; i++){  
          array[i] = array[i - 1] + array[i-2];
         }
          write(fd[1], &array[t1-1], sizeof(array[t1-1]));
          printf("I am child with pid: (pid:%d), sending %d to my parent\n", (int) getpid(),  array[t1-1]);
         close(fd[1]);
        exit(0);
    }
    int rc3=fork();
    if (rc3==0){
        array[0] = 0;
        array[1] = 1;
        close(fd2[0]);

        int k;
        for(k=2; k<t2; k++){  
          array[k] = array[k - 1] + array[k-2];
         }
          write(fd2[1], &array[t2-1], sizeof(array[t2-1]));
          printf("I am child with pid: (pid:%d), sending %d to my parent\n", (int) getpid(),  array[t2-1]);
         close(fd2[1]);
        exit(0);
   }
    int rc4=fork();
    if (rc4==0){
        array[0] = 0;
        array[1] = 1;
        close(fd3[0]);

        int l;
        for(l=2; l<t3; l++){  
          array[l] = array[l-1] + array[l-2];
         }
          write(fd3[1], &array[t3-1], sizeof(array[t3-1]));
          printf("I am child with pid: (pid:%d), sending %d to my parent\n", (int) getpid(),  array[t3-1]);
         close(fd3[1]);
        exit(0);
   }
   else {
        int sum1, sum2, sum3;

        int final=0;
        close(fd[1]);
        read(fd[0], &sum1, sizeof(sum1));
        final = sum1;

        close(fd2[1]);
        read(fd2[0], &sum2, sizeof(sum2));
        final = final +sum2;

        close(fd3[1]);
        read(fd3[0], &sum3, sizeof(sum3));
        final = final +sum3;

        close(fd[0]);
        close(fd2[0]);
        close(fd3[0]);
        printf("I am parent with (pid:%d) receiving %d, %d, and %d, the sum is %d \n" , (int) getpid(),sum1,sum2,sum3, final);
    }
}
    return 0;
}
