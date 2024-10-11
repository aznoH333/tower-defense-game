#!/bin/bash
target_files=""
output_directory="./out"
declare -a compile_paths=("." "./glib")

function compile_file() {
    file_name="${1/.\//}"
    target_name=$(basename $file_name)
    target_name=./$target_name
    target_files+=" ${target_name/.c/.o}"
    
    gcc -c $file_name -I ./glib
}

for p in "${compile_paths[@]}"; do 
    for f in $p/*.c; do
        compile_file $f
    done
done


gcc $target_files -o $output_directory/a.out -I ./glib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
rm *.o
valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes $output_directory/a.out 
rm $output_directory/*.out
