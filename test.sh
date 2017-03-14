#!/bin/bash
script_dir=$(dirname $0)
for filename in $script_dir/test/*.in; do
    echo ..................................................$filename;
		$script_dir/compiler --lexical $filename >$script_dir/test/$(basename "$filename" .in).out;
		diff $script_dir/test/$(basename "$filename" .in).out $script_dir/test/$(basename "$filename" .in).std && rm -f $script_dir/test/$(basename "$filename" .in).out;
done
total=$(find $script_dir/test/*.in 2>/dev/null | wc -l)
failed=$(find $script_dir/test/*.out 2>/dev/null | wc -l)
passed=`expr $total - $failed`
echo $passed of $total tests passed