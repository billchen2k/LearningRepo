all: build

build: tsp1 tsp2
	echo "Building.."
	export TMPDIR=/tmp

tsp1:
	mpic++ tsp1.cpp -o tsp1.out
	echo "TSP1 Built."

tsp2:
	mpic++ tsp2.cpp -o tsp2.out
	echo "TSP2 Built."

run:
	mpirun tsp1.out

clean:
	rm *.out