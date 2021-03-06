#include <stdio.h>
#include <time.h>
#include "util.h"

// column major matrices
#define IDX2C(i,j,ld) (((j)*(ld))+(i))

void new_float_matrix(float* &x, long height, long width)
{
    x = new float[height * width];
    for (long j = 0; j < width; ++j) {
        for (long i = 0; i < height; ++i) {
            x[IDX2C(i, j, height)] = ((i*j) % 10) / 10.0f;
        }
    }
}

void new_double_matrix(double* &x, long height, long width)
{
    x = new double[height * width];
    for (long j = 0; j < width; ++j) {
        for (long i = 0; i < height; ++i) {
            x[IDX2C(i, j, height)] = ((i*j) % 10) / 10.0;
        }
    }
}

void delete_float_matrix(float* &x)
{
    delete[] x;
}

void delete_double_matrix(double* &x)
{
    delete[] x;
}

void pr_array(float *x, int ld)
{
    for (int j = 0; j < 8; ++j) {
        for (int i = 0; i < 8; ++i) {
            printf("%7.5f ", x[IDX2C(i, j, ld)]);
        }
        printf("...[snip]...\n");
    }
    printf("...[snip]...\n");
}

void pr_array(double *x, int ld)
{
    for (int j = 0; j < 8; ++j) {
        for (int i = 0; i < 8; ++i) {
            printf("%7.5f ", x[IDX2C(i, j, ld)]);
        }
        printf("...[snip]...\n");
    }
    printf("...[snip]...\n");
}

void summarize_output(double timer_seconds, double data_bytes, double flops, bool csv_output)
{
    if(csv_output) {
        printf(",%f,%.1f,%.1f,%.1f,%.1f",
               timer_seconds,
               data_bytes / 1e9,
               data_bytes / timer_seconds / 1e9,
               flops / 1e9,
               flops / timer_seconds / 1e9);
    } else {
        printf("seconds:     %f\n", timer_seconds);
        printf("Gigabytes:   %.1f\n", data_bytes / 1e9);
        printf("Gigabytes/s: %.1f\n", data_bytes / timer_seconds / 1e9);
        printf("Gigaflops:   %.1f\n", flops / 1e9);
        printf("Gigaflops/s: %.1f\n", flops / timer_seconds / 1e9);
    }
}

// the total number of floating point operations for a typical *GEMM call
// is approximately 2MNK.
void summarize_sgemm(float *c, int loops, int M, int N, int K, float alpha, float beta, clock_t start, clock_t stop, bool csv_output)
{
    double data_bytes = (double)(M*K + K*N + M*N) * sizeof(float) * loops;
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    double flops = 2.0*M*N*K*loops;
    if(!csv_output) {
        printf("Result:\n");
        pr_array(c, M);
        printf("SGEMM: [%dx%d] * [%dx%d] * %.2f + [%dx%d] * %.2f\n", M, K, K, N, alpha, M, N, beta);
    }
    summarize_output(timer_seconds, data_bytes, flops, csv_output);
}

void summarize_dgemm(double *c, int loops, int M, int N, int K, double alpha, double beta, clock_t start, clock_t stop, bool csv_output)
{
    double data_bytes = (double)(M*K + K*N + M*N) * sizeof(double) * loops;
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    double flops = 2.0*M*N*K*loops;
    if(!csv_output) {
        printf("Result:\n");
        pr_array(c, M);
        printf("DGEMM: [%dx%d] * [%dx%d] * %.2f + [%dx%d] * %.2f\n", M, K, K, N, alpha, M, N, beta);
    }
    summarize_output(timer_seconds, data_bytes, flops, csv_output);
}

void summarize_ssyrkgemm(float *c, int loops, int M, int N, int K, float alpha, float beta, clock_t start, clock_t stop, bool csv_output)
{
    double data_bytes = (double)(M*K + K*N + M*N) * sizeof(float) * loops;
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    double flops = 4.0*M*N*K*loops;
    if(!csv_output) {
        printf("Result:\n");
        pr_array(c, M);
        printf("SSYRKGEMM: [%dx%d] * [%dx%d] * %.2f + [%dx%d] * %.2f\n", M, K, K, M, alpha, M, N, beta);
        printf("           [%dx%d] * [%dx%d] * %.2f + [%dx%d] * %.2f\n", M, K, K, N, alpha, M, N, beta);
    }
    summarize_output(timer_seconds, data_bytes, flops, csv_output);
}

void summarize_dsyrkgemm(double *c, int loops, int M, int N, int K, double alpha, double beta, clock_t start, clock_t stop, bool csv_output)
{
    double data_bytes = (double)(M*K + K*N + M*N) * sizeof(float);
    double timer_seconds = ((double)(stop - start)) / CLOCKS_PER_SEC;
    double flops = 4.0*M*N*K*loops;
    if(!csv_output) {
        printf("Result:\n");
        pr_array(c, M);
        printf("DSYRKGEMM: [%dx%d] * [%dx%d] * %.2f + [%dx%d] * %.2f\n", M, K, K, M, alpha, M, N, beta);
        printf("         : [%dx%d] * [%dx%d] * %.2f + [%dx%d] * %.2f\n", M, K, K, N, alpha, M, N, beta);
    }
    summarize_output(timer_seconds, data_bytes, flops, csv_output);
}
