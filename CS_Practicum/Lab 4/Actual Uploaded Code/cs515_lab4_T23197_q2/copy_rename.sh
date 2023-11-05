#!/bin/bash

target="output"
mkdir "$target"

for dir in "d"*
do
	for file_name in "$dir"/2*
	do
		if [ -f "$file_name" ]; then
			file_n="${file_name#*/}"
			cp "$file_name" "$target/$dir_$file_n"
		fi
	done
done

echo "Done"
