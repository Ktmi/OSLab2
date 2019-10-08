# Part 2
For Part 2, I copied the sample code,
then began modifying it from there.
I took some of the components I used to complete
Part 1 to complete Part 2.

To store the output, I opted to use an array stored in
global memory.
The calculation thread would get the previous 2 values from
the output array and add them together and store the result
in the output array.

Once the main thread detects that the calculation thread is complete
it iterates through the output thread and prints the results.