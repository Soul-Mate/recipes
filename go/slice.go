package main

import (
	"fmt"
)

func main() {
	//go http.ListenAndServe("0.0.0.0:6060", nil)
	v := make([]int, 0, 0)
	nKib := 1024 * 10

	fmt.Printf("allocate %d 1 kib data\n", nKib)
	for i := 0; i < nKib; i ++ {
		v = append(v, make([]int, 1024)...)
		//time.Sleep(time.Millisecond * 10)
	}
}
