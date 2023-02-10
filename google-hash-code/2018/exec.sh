g++ main.cpp -O2
g++ validate.cpp -o validate

./a.out < input/a_example.in > output/output_a
./a.out < input/b_should_be_easy.in > output/output_b
./a.out < input/c_no_hurry.in > output/output_c
./a.out < input/d_metropolis.in > output/output_d
./a.out < input/e_high_bonus.in > output/output_e

./validate