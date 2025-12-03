package structures

import "fmt"

type DynamicArray struct {
	data     []string
	size     int
	capacity int
}

func NewDynamicArray(initialCapacity int) *DynamicArray {
	if initialCapacity <= 0 {
		initialCapacity = 4
	}
	return &DynamicArray{
		data:     make([]string, initialCapacity),
		size:     0,
		capacity: initialCapacity,
	}
}

func (da *DynamicArray) resize() {
	newCapacity := da.capacity * 2
	newData := make([]string, newCapacity)
	copy(newData, da.data)
	da.data = newData
	da.capacity = newCapacity
}

func (da *DynamicArray) PushBack(value string) {
	if da.size >= da.capacity {
		da.resize()
	}
	da.data[da.size] = value
	da.size++
}

func (da *DynamicArray) Insert(index int, value string) {
	if index < 0 || index > da.size {
		return
	}
	if da.size >= da.capacity {
		da.resize()
	}
	for i := da.size; i > index; i-- {
		da.data[i] = da.data[i-1]
	}
	da.data[index] = value
	da.size++
}

func (da *DynamicArray) Get(index int) string {
	if index < 0 || index >= da.size {
		return ""
	}
	return da.data[index]
}

func (da *DynamicArray) RemoveAt(index int) {
	if index < 0 || index >= da.size {
		return
	}
	for i := index; i < da.size-1; i++ {
		da.data[i] = da.data[i+1]
	}
	da.size--
}

func (da *DynamicArray) Size() int {
	return da.size
}

func (da *DynamicArray) Capacity() int {
	return da.capacity
}

func (da *DynamicArray) Set(index int, value string) {
	if index < 0 || index >= da.size {
		return
	}
	da.data[index] = value
}

func (da *DynamicArray) Clear() {
	da.data = make([]string, 4)
	da.size = 0
	da.capacity = 4
}

func (da *DynamicArray) Print() {
	for i := 0; i < da.size; i++ {
		fmt.Print(da.data[i], " ")
	}
	fmt.Println()
}
