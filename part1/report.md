# Part 1
For part 1, I copied the sample code,
then began modifying the program from there.

The threads objects are all stored in an array,
then iterated through to start them.
After spawning all the threads, the main thread
attempts to iteratively join all the child threads.

## No Mutexes
With no mutexes, I found that the program gave
inconsistent results.
With the command line parameter set to 1,
the program gave the expected final result of 20,
but with the command line parameter set higher,
there appeared to be overlap in reads and writes,
causing the final result to be inconsistent, and
less than expected.

Removal of usleep caused the program to consistently
had a final output of 20 at low input values.

## With Mutexes
With mutexes, the results where as expected for the range of
input values I tested.
At input value of 10000, the final output value was 200000.

Mutexes were implemented with a globally available mutex object,
which threads would lock before reading
and writing to the shared value.
After writing to the shared value, the thread would unlock the
mutex.