# threaded_matrix_multiplication

## Running only one time:

Compile it by running the "make" command on terminal

You can add compilation flags to determine both the matrix size of multiplication and the number of threads:

* make matrix_size=96
* make num_threads=12
* make matrix_size=960 num_threads=8

The default values are: matrix_size=24 and num_threads=4

Make sure the matrix size parameter is a multiple of 24 for the algorithm to run smoothly

## Running the test script:

The test script run_tests.sh creates two loops, one for the size of the matrices and other for the number of threads

In order to compile it and run it, run the following commands:

* chmod +x run_tests.sh
* ./run_tests.sh

You'll see the output on the results.csv file