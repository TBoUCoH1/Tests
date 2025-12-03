package structures

import "fmt"

type EntryStatus int

const (
	EMPTY EntryStatus = iota
	OCCUPIED
	DELETED
)

type HashEntry struct {
	Key    string
	Value  string
	Status EntryStatus
}

type HashTableOpen struct {
	Table    []HashEntry
	Size     int
	Capacity int
}

func NewHashTableOpen(capacity int) *HashTableOpen {
	if capacity <= 0 {
		capacity = 101
	}
	return &HashTableOpen{
		Table:    make([]HashEntry, capacity),
		Size:     0,
		Capacity: capacity,
	}
}

func (ht *HashTableOpen) hashFunction(key string) int {
	hash := 0
	for i := 0; i < len(key); i++ {
		hash = (hash*31 + int(key[i])) % ht.Capacity
	}
	return hash
}

func (ht *HashTableOpen) Insert(key, value string) {
	index := ht.hashFunction(key)
	originalIndex := index
	i := 1

	for ht.Table[index].Status == OCCUPIED {
		if ht.Table[index].Key == key {
			ht.Table[index].Value = value
			return
		}
		index = (originalIndex + i*i) % ht.Capacity
		i++
	}

	ht.Table[index] = HashEntry{Key: key, Value: value, Status: OCCUPIED}
	ht.Size++
}

func (ht *HashTableOpen) Get(key string) string {
	index := ht.hashFunction(key)
	originalIndex := index
	i := 1

	for ht.Table[index].Status != EMPTY {
		if ht.Table[index].Status == OCCUPIED && ht.Table[index].Key == key {
			return ht.Table[index].Value
		}
		index = (originalIndex + i*i) % ht.Capacity
		i++
		if i > ht.Capacity {
			break
		}
	}
	return ""
}

func (ht *HashTableOpen) Remove(key string) {
	index := ht.hashFunction(key)
	originalIndex := index
	i := 1

	for ht.Table[index].Status != EMPTY {
		if ht.Table[index].Status == OCCUPIED && ht.Table[index].Key == key {
			ht.Table[index].Status = DELETED
			ht.Size--
			return
		}
		index = (originalIndex + i*i) % ht.Capacity
		i++
	}
}

func (ht *HashTableOpen) Print() {
	for i := 0; i < ht.Capacity; i++ {
		if ht.Table[i].Status == OCCUPIED {
			fmt.Printf("[%d] %s => %s\n", i, ht.Table[i].Key, ht.Table[i].Value)
		}
	}
}

func (ht *HashTableOpen) PrintStats() {
	fmt.Printf("Size: %d, Capacity: %d, Load Factor: %.2f\n", ht.Size, ht.Capacity, float64(ht.Size)/float64(ht.Capacity))
}

func (ht *HashTableOpen) Clear() {
	for i := 0; i < ht.Capacity; i++ {
		ht.Table[i].Status = EMPTY
		ht.Table[i].Key = ""
		ht.Table[i].Value = ""
	}
	ht.Size = 0
}

func (ht *HashTableOpen) GetAllKeys() []string {
	keys := []string{}
	for i := 0; i < ht.Capacity; i++ {
		if ht.Table[i].Status == OCCUPIED {
			keys = append(keys, ht.Table[i].Key)
		}
	}
	return keys
}
