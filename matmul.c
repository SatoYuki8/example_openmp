#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/time.h>
#include <omp.h>

//行列の幅（正方行列）
#define N 1024
//配列アクセスのためのマクロ
#define MR(mt,c,r) mt[c*N+r]

double second();

//行列積計算を行う関数
void mult(float a[], float b[], float c[]){
  int i, j, k;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      for(k = 0; k < N; k++){
	MR(c,i,j) += MR(a,i,k) * MR(b,k,j);
      }
    }
  }
}

int main(){
  float *a, *b, *c;
  double n = 0.0;
  int i, j;

  double cpu, cpu0, cpu1;

  a = (float*)malloc(N*N*sizeof(float));
  b = (float*)malloc(N*N*sizeof(float));
  c = (float*)malloc(N*N*sizeof(float));

  srand(539);

  //データの生成
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      MR(a,i,j) = (float)rand()/RAND_MAX/2;
      MR(b,i,j) = (float)rand()/RAND_MAX/2;
      MR(c,i,j) = 0.0; // 初期化
    }
  }

  //時間取得の関数
  cpu0 = second();

  //行列積の計算
  mult(a, b, c);

  cpu1 = second();
  cpu = cpu1 - cpu0;

  //チェックサム算出
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      n += MR(c,i,j);
    }
  }

  printf("N:%d\nchecksum:%.16f\ntime:%f\n", N, n, cpu);

  free(a);
  free(b);
  free(c);

  return 0;
}

/*******時間測定*******/
double second()
{

  struct timeval tm;
  double t ;

  static int base_sec = 0,base_usec = 0;

  gettimeofday(&tm, NULL);
  
  if(base_sec == 0 && base_usec == 0)
    {
      base_sec = tm.tv_sec;
      base_usec = tm.tv_usec;
      t = 0.0;
    } else {
    t = (double) (tm.tv_sec-base_sec) + 
      ((double) (tm.tv_usec-base_usec))/1.0e6 ;
  }

  return t ;
}
