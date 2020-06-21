all: build

build: tsp1 tsp2 tspserial
	echo "Building.."
	export TMPDIR=/tmp

tspserial:
	g++ tsp_serial.cpp -o tsp_serial.out
	echo "TSP Serial Built."

tsp1:
	mpic++ tsp1.cpp -o tsp1.out
	echo "TSP1 Built."

tsp2:
	mpic++ tsp2.cpp -o tsp2.out
	echo "TSP2 Built."

runs:
	./tsp_serial.out graph12.in

run1:
	mpirun -np 12 tsp1.out graph12.in


run2:
	mpirun -np 12 tsp2.out graph12.in

clean:
	rm *.out