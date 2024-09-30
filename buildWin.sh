#!/bin/sh

echo "${BASH_VERSION}"
target_files=
output_directory="./out"
#shit je fucked
#compile_paths = ("." "./glib")



function compile_file() {
    file_name="${1/.\//}"
    target_name=$(basename $file_name)
    target_name=./$target_name
    target_files="${target_files} ${target_name/.c/.o}"
    
    gcc -c $file_name -I ./glib
}


function beans(){
    for f in $1/*.c; do
        compile_file $f
    done
}

beans "."
beans "./glib"



gcc $target_files -o $output_directory/game.exe -I ./glib -lraylib -lgdi32 -lwinmm
rm ./*.o
$output_directory/game.exe
#rm $output_directory/*.exe






#target_files=


#for f in ./*.c; do
#    file_name="${f/.\//}"
#    gcc -c $file_name
#    target_files="${target_files} ${file_name/.c/.o}"
#
#done
#echo $target_files
#gcc -o game.exe $target_files -lraylib -lgdi32 -lwinmm
#rm *.o
#./game.exe
#rm *.exe
