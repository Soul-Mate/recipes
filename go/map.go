package main

import (
	"fmt"
	"log"
)

func main() {
	m := make(map[string]string)
	for i := 0; i < 100000; i++ {
		m[fmt.Sprintf("some_key_%d", i)] = "a"
	}

	v := m["some_key_100"]
	log.Println(v)
}
