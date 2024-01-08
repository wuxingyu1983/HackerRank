#!/bin/bash

cnt=$2;

input_folder="$1/input";
output_folder="$1/output";

for((i=0;i<=$cnt;i++));
do
# 补齐 0
num=`echo $i | awk '{printf("%02d",$0)}'`;

input_file="$input_folder/input$num.txt";
output_file="$output_folder/output$num.txt";

result=`./main < $input_file`;
output=`head -n 1 $output_file`;

if [ $result = $output ]; then
  echo "testcase $i correct!";
else
  echo "testcase $i incorrect!";
fi

done 
