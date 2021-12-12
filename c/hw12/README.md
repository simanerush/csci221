# HW 12

Serafima Nerush

## Timing

* 1 thread: 0m48.423s
* 2 threads: 0m24.405s
* 4 threads: 0m12.305s
* 8 threads: 0m6.384s
* 16 threads: 0m3.306s
* 32 threads: 0m2.068s
* 64 threads: 0m1.568s

From the data, we can see that the timing decreases linearly depending on the number of threads. 

## Parameters for the best performer

* num_iter = 2'000'000
* pop_size = 1000
* mut_rate = 0.1
* nthread = 64

## Best distance

The best distance averages 7000.

## Best runtime comparing to one thread runtime

The best runtime is 1.5s, and one thread runtime is 48s, so roughly 32x increase in performance.