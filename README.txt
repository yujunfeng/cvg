cvg - CPU vs. GPU SGEMM performance test
by Roger Allen & Rick Wirch
Feb 29, 2016

This is just a toy perf app for developers.  

I wanted a simple way to compare CPU vs. GPU SGEMM performance using Intel MKL, NVIDIA CUBLAS & CUBLAS-XT libraries.  
It started out simple, but like so many things, got a bit more complex over time...  Since this is for developers,
please just read the code to see what it is doing.

NOTE: built assuming Intel MKL V11.3

Example usage & output:

usage:
 cvg <options>
options:
 -t g|s   : test type: GEMM, SYRK+GEMM (default GEMM)
 -s c|g|x : API select: CPU (Intel MKL), GPU (CUBLAS), GPU (CUBLAS-XT)
 -p s|d   : test precision: single (default) or double
 -l #     : loops of the algorithm (default 1)
 -m #     : matrix M dimension (default 1024)
 -n #     : matrix N dimension (default 1024)
 -k #     : matrix K dimension (default 2048)
 -b #     : CUBLAS-XT block_dim (default 1024)
 -A #     : alpha GEMM parameter (default 1.11)
 -B #     : beta GEMM parameter (default 0.91)
 -g #     : [CUBLAS-XT only] gpu id(s) to use. can specify multiple -g options. (default=0)

================================================================================
CPU SGEMM:
================================================================================

> x64/Debug/cvg.exe -s c -l 4 -m 6400 -n 6400 -k 26000
Intel MKL sgemm: loops=4 M=6400 N=6400 K=26000
Result:
0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 ...[snip]...
0.00000 28719.44922 22169.48633 22673.35742 20154.22656 12596.54492 20154.33008 22673.64648 ...[snip]...
0.00000 22169.48633 24184.95898 20154.36719 20154.42969 10076.95996 20154.09180 20154.15234 ...[snip]...
0.00000 22673.35742 20154.36719 28719.94336 18138.64063 12596.54395 22169.84375 16627.07617 ...[snip]...
0.00000 20154.22656 20154.42969 18138.64063 24185.12891 10076.95898 16123.51660 22169.87695 ...[snip]...
0.00000 12596.54492 10076.95996 12596.54395 10076.95898 12596.49316 10076.95898 12596.54492 ...[snip]...
0.00000 20154.33008 20154.09180 22169.84375 16123.51660 10076.95898 24185.12891 18138.64258 ...[snip]...
0.00000 22673.64648 20154.15234 16627.07617 22169.87695 12596.54492 18138.64258 28719.93555 ...[snip]...
...[snip]...
SGEMM: [6400x26000] * [26000x6400] + [6400x6400]
seconds:     24.031000
Gigabytes:   1.5
Gigaflops:   8519.7
Gigaflops/s: 354.5

================================================================================
GPU CUBLAS SGEMM:
================================================================================

> x64/Debug/cvg.exe -s g -l 4 -m 6400 -n 6400 -k 26000
NVIDIA CUBLAS sgemm: loops=4 M=6400 N=6400 K=26000 alpha=1.110000 beta=0.910000
Device Number: 0
  Device name: GeForce GTX 960
  Memory Clock Rate (KHz): 3505000
  Memory Bus Width (bits): 128
  Peak Memory Bandwidth (GB/s): 112.160000

Result:
0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 ...[snip]...
0.00000 28720.24805 22170.63477 22672.59961 20156.65430 12596.54688 20155.56250 22672.87500 ...[snip]...
0.00000 22170.63477 24186.18359 20156.79102 20155.93164 10076.96289 20155.51758 20155.42578 ...[snip]...
0.00000 22672.59961 20156.79102 28720.79492 18140.14648 12596.54688 22171.04297 16626.54688 ...[snip]...
0.00000 20156.65430 20155.93164 18140.14648 24186.32227 10076.96289 16121.77734 22171.04492 ...[snip]...
0.00000 12596.54688 10076.96289 12596.54688 10076.96289 12596.54688 10076.96289 12596.54590 ...[snip]...
0.00000 20155.56250 20155.51758 22171.04297 16121.77734 10076.96289 24186.32422 18140.14844 ...[snip]...
0.00000 22672.87500 20155.42578 16626.54688 22171.04492 12596.54590 18140.14844 28720.79492 ...[snip]...
...[snip]...
SGEMM: [6400x26000] * [26000x6400] * 1.11 + [6400x6400] * 0.91
seconds:     4.842000
Gigabytes:   1.5
Gigaflops:   8519.7
Gigaflops/s: 1759.5
ON DEVICE TIME:Result:
0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 ...[snip]...
0.00000 28720.24805 22170.63477 22672.59961 20156.65430 12596.54688 20155.56250 22672.87500 ...[snip]...
0.00000 22170.63477 24186.18359 20156.79102 20155.93164 10076.96289 20155.51758 20155.42578 ...[snip]...
0.00000 22672.59961 20156.79102 28720.79492 18140.14648 12596.54688 22171.04297 16626.54688 ...[snip]...
0.00000 20156.65430 20155.93164 18140.14648 24186.32227 10076.96289 16121.77734 22171.04492 ...[snip]...
0.00000 12596.54688 10076.96289 12596.54688 10076.96289 12596.54688 10076.96289 12596.54590 ...[snip]...
0.00000 20155.56250 20155.51758 22171.04297 16121.77734 10076.96289 24186.32422 18140.14844 ...[snip]...
0.00000 22672.87500 20155.42578 16626.54688 22171.04492 12596.54590 18140.14844 28720.79492 ...[snip]...
...[snip]...
SGEMM: [6400x26000] * [26000x6400] * 1.11 + [6400x6400] * 0.91
seconds:     3.328000
Gigabytes:   1.5
Gigaflops:   8519.7
Gigaflops/s: 2560.0

================================================================================
GPU CUBLASXT SGEMM
================================================================================

> x64/Debug/cvg.exe -s x -l 4 -m 6400 -n 6400 -k 26000 -b 8192
NVIDIA CUBLASXT sgemm: loops=4 M=6400 N=6400 K=26000 block_dim=8192
Device Number: 0
  Device name: GeForce GTX 960
  Memory Clock Rate (KHz): 3505000
  Memory Bus Width (bits): 128
  Peak Memory Bandwidth (GB/s): 112.160000

Result:
0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 0.00000 ...[snip]...
0.00000 28719.88281 22169.25781 22673.02734 20154.70898 12596.54688 20154.59180 22673.30469 ...[snip]...
0.00000 22169.25781 24185.44727 20154.84766 20153.60938 10076.96289 20153.19922 20154.45313 ...[snip]...
0.00000 22673.02734 20154.84766 28720.43359 18138.39258 12596.54590 22169.67188 16626.87891 ...[snip]...
0.00000 20154.70898 20153.60938 18138.39258 24185.58398 10076.96289 16123.07813 22169.67383 ...[snip]...
0.00000 12596.54688 10076.96289 12596.54590 10076.96289 12596.54590 10076.96289 12596.54590 ...[snip]...
0.00000 20154.59180 20153.19922 22169.67188 16123.07813 10076.96289 24185.58008 18138.39063 ...[snip]...
0.00000 22673.30469 20154.45313 16626.87891 22169.67383 12596.54590 18138.39063 28720.43750 ...[snip]...
...[snip]...
SGEMM: [6400x26000] * [26000x6400] + [6400x6400]
seconds:     5.296000
Gigabytes:   1.5
Gigaflops:   8519.7
Gigaflops/s: 1608.7