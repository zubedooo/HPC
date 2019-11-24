#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BLOCK_SIZE 3
#define WA 3
#define HA 3
#define WB 3
#define HB 3
#define WC 3
#define HC 3

void Init(float * data ,int size)
{
	for(int i = 0; i < size; ++i)
    	data[i] = i;
}

__global__ void matrixMul(float* A,float* B,float* C,int wA,int wB)
{
int tx = threadIdx.x;
int ty = threadIdx.y;

float value = 0;
for(int i = 0; i < wA; ++i)
{
float elementA = A[ty * wA + i];
float elementB = B[i * wB + tx];
value  +=  elementA * elementB;
}
//  write to device mem
C[ty * wA + tx] = value;
}

int main(int argc ,char** argv)
{

srand(2006);

unsigned  int size_A = WA * HA;
unsigned  int mem_size_A =sizeof(float) * size_A;
float* h_A = (float*)  malloc(mem_size_A);

unsigned  int size_B = WB * HB;
unsigned  int mem_size_B =sizeof(float) * size_B;
float * h_B = (float*)  malloc(mem_size_B);

unsigned  int size_C = WC * HC;
unsigned  int mem_size_C =sizeof(float) * size_C;
float * h_C = (float *)  malloc(mem_size_C);

Init(h_A, size_A);
Init(h_B, size_B);

printf("\n\nMatrix A\n");
for(int i = 0; i < size_A; i++)
{
printf("%f ", h_A[i]);
if(((i + 1) % WA) == 0)
printf("\n");
}

printf("\n\nMatrix B\n");
for(int i = 0; i < size_B; i++)
{
printf
("%f ", h_B[i]);
if(((i + 1) % WB) == 0)
printf("\n");
}

float* d_A;
float* d_B;
float* d_C;

cudaMalloc((void**) &d_A, mem_size_A);
cudaMalloc((void**) &d_B, mem_size_B);
cudaMalloc((void**) &d_C, mem_size_C);

cudaMemcpy(d_A, h_A,mem_size_A ,cudaMemcpyHostToDevice);
cudaMemcpy(d_B, h_B,mem_size_B ,cudaMemcpyHostToDevice);


dim3  threads(BLOCK_SIZE , BLOCK_SIZE);
dim3  grid(WC / threads.x, HC / threads.y);

matrixMul<<< grid , threads  >>>(d_A,d_B, d_C, WA, WB);
cudaMemcpy(h_C, d_C, mem_size_C ,cudaMemcpyDeviceToHost);

printf("\n\nMatrix C (Results) \n");
for(int i = 0;i<size_C; i ++){
	printf("%f ",h_C[i]);
	if(((i+ 1) % WC) == 0)
    	printf("\n");
}
printf("\n");

cudaFree(d_A);
cudaFree(d_B);
cudaFree(d_C);

free(h_A);
free(h_B);
free(h_C);

}
