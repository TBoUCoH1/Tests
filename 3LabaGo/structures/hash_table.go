package structures

const TableSize = 101

type HashTable struct {
	Buckets [TableSize]*SinglyLinkedList
	Size    int
}

func NewHashTable() *HashTable {
	ht := &HashTable{}
	for i := 0; i < TableSize; i++ {
		ht.Buckets[i] = &SinglyLinkedList{}
	}
	return ht
}

func (ht *HashTable) hashFunction(key string) int {
	hash := 0
	for i := 0; i < len(key); i++ {
		hash = (hash*31 + int(key[i])) % TableSize
	}
	return hash
}

func (ht *HashTable) Insert(key string, value string) {
	index := ht.hashFunction(key)
	ht.Buckets[index].PushBack(key)
	ht.Size++
}

func (ht *HashTable) Contains(key string) bool {
	index := ht.hashFunction(key)
	return ht.Buckets[index].Find(key) != nil
}

func (ht *HashTable) Remove(key string) {
	index := ht.hashFunction(key)
	ht.Buckets[index].RemoveValue(key)
	ht.Size--
}

func (ht *HashTable) Clear() {
	for i := 0; i < TableSize; i++ {
		ht.Buckets[i].Clear()
	}
	ht.Size = 0
}
