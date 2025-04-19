#!/bin/bash

find . -type f -name "*.o" > tester.tmp
echo "ft_nm" >> tester.tmp

while read -r line; do
    nm "$line" >> real_nm_res
    # nm -a "$line" >> real_nm_res
    nm -g "$line" >> real_nm_res
    nm -u "$line" >> real_nm_res
    nm -r "$line" >> real_nm_res
    nm -p "$line" >> real_nm_res
    ./ft_nm "$line" >> my_nm_res
    # ./ft_nm -a "$line" >> my_nm_res
    ./ft_nm -g "$line" >> my_nm_res
    ./ft_nm -u "$line" >> my_nm_res
    ./ft_nm -r "$line" >> my_nm_res
    ./ft_nm -p "$line" >> my_nm_res
done < "./tester.tmp"

diff real_nm_res my_nm_res

if [ $? == 0 ]; then
    echo "No diff between real nm and ft_nm"
    rm -rf tester.tmp my_nm_res real_nm_res 
fi
