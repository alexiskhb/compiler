#!/bin/bash
script_dir=$(dirname $0)
ext=tree
for filename in ./*-02.std ; do
	to=./$(basename "$filename" -02.std)-01.std
	echo $to
	# to=./$(basename "$filename" .out).std
	# echo $filename $to
	cat $filename >$to
	# mv $filename $to
done
над неразрешенными вопросами можно думать сколько угодно, иначе они так и останутся неразрешеннымиа