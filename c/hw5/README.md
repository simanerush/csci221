Griddle Pi results
------------------

* 10: 2.92
* 100: 3.1156
* 1,000: 3.13916
* 10,000: 3.14136

Complexity
==========

O(n^2)


Timing
======

* 10: 0.00s user 0.00s system 55% cpu 0.006 total
* 100: 0.00s user 0.00s system 2% cpu 0.129 total
* 1,000: 0.01s user 0.00s system 4% cpu 0.174 total
* 10,000: 0.56s user 0.01s system 80% cpu 0.706 total

Constexpr Timing
================

* 10: 0.00s user 0.00s system 0% cpu 0.323 total
* 100: 0.00s user 0.00s system 1% cpu 0.168 total
* 1,000: 0.01s user 0.00s system 6% cpu 0.137 total
* 10,000: 0.54s user 0.01s system 78% cpu 0.687 total


From the measurements, we can see the pattern that the computation gets slower
when we use larger n, but since the timing is 0 on smaller values, it is not clear
whether the increase in execution time is n^2 or not.

The constexpr seems not to give any improvement in timing, although it is slightly faster.
Also, trying npoints >= 1000 gives an error about the step limit, and does not compile.
s
