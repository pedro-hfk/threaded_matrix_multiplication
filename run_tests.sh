OUTPUT_FILE="results.csv"

echo "matrix_size,num_threads,parallel_time,sequential_time,speedup_rate" > $OUTPUT_FILE

for matrix_size in $(seq 96 96 960); do
    for num_threads in 2 4 8 12; do
        make matrix_size=$matrix_size num_threads=$num_threads

        OUTPUT=$(./main)

        parallel_time=$(echo "$OUTPUT" | grep "Parallel time" | awk '{print $3}')
        sequential_time=$(echo "$OUTPUT" | grep "Sequential time" | awk '{print $3}')
        speedup_rate=$(echo "$OUTPUT" | grep "Speedup Rate" | awk '{print $3}')

        echo "$matrix_size,$num_threads,$parallel_time,$sequential_time,$speedup_rate" >> $OUTPUT_FILE
    done
done

make clean
