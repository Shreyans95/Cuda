package main

// #cgo CFLAGS: -I.
// #cgo LDFLAGS: -L. -lmaxmul_wrapper
// #include "maxmul_wrapper.h"
import "C"

import (
	"math/rand"
	"time"
)

func Maxmul(a []C.float, b []C.float, c []C.float, size int) {
	C.maxmul(&a[0], &b[0], &c[0], C.int(size))
}

func generateRandomMatrix(n int) []C.float {
	// Seed the random number generator with the current time
	rand.Seed(time.Now().UnixNano())

	matrix := make([]C.float, n)
	for i := 0; i < n; i++ {
		// Generate a random float number between 1 and 100
		matrix[i] = C.float(rand.Float64()*99 + 1)
	}
	return matrix
}

func main() {
	//in := []C.float{1.23, 4.56}
	//C.test(&in[0]) // C 1.230000 4.560000
	n := 100
	// a := []C.float{-1, 2, 4, 0, 5, 3, 6, 2, 1}
	// b := []C.float{3, 0, 2, 3, 4, 5, 4, 7, 2}

	var c []C.float = make([]C.float, n*n)
	a := generateRandomMatrix(n * n)
	b := generateRandomMatrix(n * n)
	// fmt.Println(a)
	Maxmul(a, b, c, n)
	// fmt.Println(c)
}
