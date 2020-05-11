package main

import (
	"fmt"
	"runtime"
)

var global = make([]int, 1024 * 1024 * 1024)

func fill()  {
	for i := 0; i < len(global); i++ {
		global[i] = i + len(global)
	}
	fmt.Printf("%v\n", global[0])
	runtime.GC()
	fmt.Printf("%v\n", global[0])
}

func main()  {
	fill()
}