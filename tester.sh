#!/bin/bash

find . -type f -name "*.o" > tester.tmp

while read -r line; do
    nm "$line" >> real_nm_res
    ./ft_nm "$line" >> my_nm_res
done < "./tester.tmp"

diff real_nm_res my_nm_res

if [ $? == 0 ]; then
    echo "No diff between real nm and ft_nm"
fi

rm -rf tester.tmp my_nm_res real_nm_res 