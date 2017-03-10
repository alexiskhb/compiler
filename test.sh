#!/bin/bash
script_dir=$(dirname $0)
for filename in $script_dir/test/*.in; do
    echo ..................................................$filename;
		$script_dir/compiler --lexical $filename >$script_dir/test/$(basename "$filename" .in).out;
		diff $script_dir/test/$(basename "$filename" .in).out $script_dir/test/$(basename "$filename" .in).std;
done
