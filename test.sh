#!bash

clean() {
    cd src
    make clean
    cd ..
    rm STLPriorityQueue/stl_priority_queue generator/generator input my_priority_queue.out stl_priority_queue.out
}

case "$1" in
    clean)
        clean
        exit 0;;
    
esac

cd src
make
cd ..

g++ -o STLPriorityQueue/stl_priority_queue STLPriorityQueue/stl_priority_queue.cpp

gcc -o generator/generator generator/generator.c

./generator/generator > input

./src/my_priority_queue < input > my_priority_queue.out
./STLPriorityQueue/stl_priority_queue < input > stl_priority_queue.out

diff my_priority_queue.out stl_priority_queue.out

if [ $? -eq 0 ] ; then
    echo "No Error!"
else
    echo "Error! Please check the log!"
fi

echo "Check finished!"