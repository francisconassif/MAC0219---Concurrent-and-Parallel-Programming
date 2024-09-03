MiniE03 - MAC0219 - Concurrent and Parallel Programming
Student: Francisco Nassif
Professor: Alfredo Goldman

Description: The objective of this MiniEP is to detect efficiency problems in the code and optimize mini_ep3.c, reducing its execution time. After analyzing with gprof, it was observed that 71% of the execution time was spent in slowsort() and 29% in fibonacci(). The strategies to improve the code were:
 - Replacing slowsort with quicksort
 - Replacing the recursive Fibonacci calculation with a matrix-based approach
 
After these two modifications, the execution time dropped from 10.248 seconds to 0.003 seconds. There was an attempt to run gprof again to check if there were any other slow sections, but gprof only measures up to 2 hundredths of a second. Since the total time was 0.3 hundredths of a second, it could not detect which part of the code was the most time-consuming.

Adding the compilation flags from MiniE02 did not result in significant changes in execution time, so the flags from the original Makefile were kept.
