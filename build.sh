echo "-> Building project"
cmake ./ -B ./out
cmake --build ./out --target all -- -j8
echo "" 

