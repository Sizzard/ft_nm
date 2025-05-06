#!/bin/bash

for file in ./tests/*
do
    nm "$file" >> real_nm_res
    # nm -a "$file" >> real_nm_res
    nm -g "$file" >> real_nm_res
    nm -u "$file" >> real_nm_res
    nm -r "$file" >> real_nm_res
    nm -p "$file" >> real_nm_res
    ./ft_nm "$file" >> my_nm_res
    # ./ft_nm -a "$file" >> my_nm_res
    ./ft_nm -g "$file" >> my_nm_res
    ./ft_nm -u "$file" >> my_nm_res
    ./ft_nm -r "$file" >> my_nm_res
    ./ft_nm -p "$file" >> my_nm_res
done

diff real_nm_res my_nm_res

if [ $? == 0 ]; then
    echo "No diff between real nm and ft_nm"
    rm -rf tester.tmp my_nm_res real_nm_res 
fi
