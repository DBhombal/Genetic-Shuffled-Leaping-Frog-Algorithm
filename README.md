Made in C - Final Project for a school course.
fork() is used so it must be run on Linux.

Compares the execution time between two different algorithms to get the same result.
These are done simultaneously, the shuffled algorithm will be done as a new process, while the genetic one will be done by the main process.

I also compared the time differences with different levels of precision needed for the frogs, screenshots will be included.

Shuffled Frog-Leaping Algorithm:
To find the best frog in every group of frogs in every generation.
Ends once a frog above a certain threshhold is born.
Will track the real life execution time, the generation and group of the frog.

Genetic frog algorithm: 
Same as SFLA, but includes 'crossovers' and 'mutations' to the frogs.
Execution times were usually faster.


Screenshots were taken for precision upto 5 and 7 decimal places. As the variance between the 5 decimal precision was neglible, I only included the screenshots for 7 decimal precision, and one anomalous case for the genetic algorithm.
