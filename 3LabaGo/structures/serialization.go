package structures

import (
	"bufio"
	"encoding/binary"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

// ===================== DYNAMIC ARRAY =====================

func (da *DynamicArray) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d\n", da.size)
	for i := 0; i < da.size; i++ {
		fmt.Fprintf(writer, "%s\n", da.data[i])
	}
	return writer.Flush()
}

func (da *DynamicArray) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil {
		return err
	}

	da.data = make([]string, size*2+1)
	da.capacity = size*2 + 1
	da.size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		da.PushBack(strings.TrimSuffix(line, "\n"))
	}
	return nil
}

func (da *DynamicArray) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(da.size)); err != nil {
		return err
	}
	for i := 0; i < da.size; i++ {
		if err := writeString(file, da.data[i]); err != nil {
			return err
		}
	}
	return nil
}

func (da *DynamicArray) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var size int32
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	da.data = make([]string, size*2+1)
	da.capacity = int(size*2 + 1)
	da.size = 0

	for i := 0; i < int(size); i++ {
		str, err := readString(file)
		if err != nil {
			return err
		}
		da.PushBack(str)
	}
	return nil
}

// ===================== SINGLY LINKED LIST =====================

func (list *SinglyLinkedList) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d\n", list.Size)
	temp := list.Head
	for temp != nil {
		fmt.Fprintf(writer, "%s\n", temp.Key)
		temp = temp.Next
	}
	return writer.Flush()
}

func (list *SinglyLinkedList) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil {
		return err
	}

	list.Head = nil
	list.Size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		list.PushBack(strings.TrimSuffix(line, "\n"))
	}
	return nil
}

func (list *SinglyLinkedList) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(list.Size)); err != nil {
		return err
	}
	temp := list.Head
	for temp != nil {
		if err := writeString(file, temp.Key); err != nil {
			return err
		}
		temp = temp.Next
	}
	return nil
}

func (list *SinglyLinkedList) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var size int32
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	list.Head = nil
	list.Size = 0

	for i := 0; i < int(size); i++ {
		str, err := readString(file)
		if err != nil {
			return err
		}
		list.PushBack(str)
	}
	return nil
}

// ===================== DOUBLY LINKED LIST =====================

func (list *DoublyLinkedList) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d\n", list.Size)
	temp := list.Head
	for temp != nil {
		fmt.Fprintf(writer, "%s\n", temp.Data)
		temp = temp.Next
	}
	return writer.Flush()
}

func (list *DoublyLinkedList) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil {
		return err
	}

	list.Head = nil
	list.Tail = nil
	list.Size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		list.PushBack(strings.TrimSuffix(line, "\n"))
	}
	return nil
}

func (list *DoublyLinkedList) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(list.Size)); err != nil {
		return err
	}
	temp := list.Head
	for temp != nil {
		if err := writeString(file, temp.Data); err != nil {
			return err
		}
		temp = temp.Next
	}
	return nil
}

func (list *DoublyLinkedList) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var size int32
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	list.Head = nil
	list.Tail = nil
	list.Size = 0

	for i := 0; i < int(size); i++ {
		str, err := readString(file)
		if err != nil {
			return err
		}
		list.PushBack(str)
	}
	return nil
}

// ===================== STACK =====================

func (s *Stack) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var items []string
	temp := s.Top
	for temp != nil {
		items = append(items, temp.Data)
		temp = temp.Next
	}

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d\n", len(items))
	for i := len(items) - 1; i >= 0; i-- {
		fmt.Fprintf(writer, "%s\n", items[i])
	}
	return writer.Flush()
}

func (s *Stack) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil {
		return err
	}

	s.Top = nil
	s.Size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		s.Push(strings.TrimSuffix(line, "\n"))
	}
	return nil
}

func (s *Stack) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var items []string
	temp := s.Top
	for temp != nil {
		items = append(items, temp.Data)
		temp = temp.Next
	}

	if err := binary.Write(file, binary.LittleEndian, int32(len(items))); err != nil {
		return err
	}
	for i := len(items) - 1; i >= 0; i-- {
		if err := writeString(file, items[i]); err != nil {
			return err
		}
	}
	return nil
}

func (s *Stack) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var size int32
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	s.Top = nil
	s.Size = 0

	for i := 0; i < int(size); i++ {
		str, err := readString(file)
		if err != nil {
			return err
		}
		s.Push(str)
	}
	return nil
}

// ===================== QUEUE =====================

func (q *Queue) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d\n", q.Size)
	temp := q.Head
	for temp != nil {
		fmt.Fprintf(writer, "%s\n", temp.Data)
		temp = temp.Next
	}
	return writer.Flush()
}

func (q *Queue) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil {
		return err
	}

	q.Head = nil
	q.Tail = nil
	q.Size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		q.Push(strings.TrimSuffix(line, "\n"))
	}
	return nil
}

func (q *Queue) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(q.Size)); err != nil {
		return err
	}
	temp := q.Head
	for temp != nil {
		if err := writeString(file, temp.Data); err != nil {
			return err
		}
		temp = temp.Next
	}
	return nil
}

func (q *Queue) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var size int32
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	q.Head = nil
	q.Tail = nil
	q.Size = 0

	for i := 0; i < int(size); i++ {
		str, err := readString(file)
		if err != nil {
			return err
		}
		q.Push(str)
	}
	return nil
}

// ===================== HASH TABLE (CHAINING) =====================

func (ht *HashTable) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d\n", ht.Size)

	for i := 0; i < TableSize; i++ {
		temp := ht.Buckets[i].Head
		for temp != nil {
			fmt.Fprintf(writer, "%s\n", temp.Key)
			temp = temp.Next
		}
	}
	return writer.Flush()
}

func (ht *HashTable) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	size, err := strconv.Atoi(strings.TrimSpace(line))
	if err != nil {
		return err
	}

	for i := 0; i < TableSize; i++ {
		ht.Buckets[i] = &SinglyLinkedList{}
	}
	ht.Size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		ht.Insert(strings.TrimSuffix(line, "\n"), "")
	}
	return nil
}

func (ht *HashTable) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(ht.Size)); err != nil {
		return err
	}

	for i := 0; i < TableSize; i++ {
		temp := ht.Buckets[i].Head
		for temp != nil {
			if err := writeString(file, temp.Key); err != nil {
				return err
			}
			temp = temp.Next
		}
	}
	return nil
}

func (ht *HashTable) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var size int32
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	for i := 0; i < TableSize; i++ {
		ht.Buckets[i] = &SinglyLinkedList{}
	}
	ht.Size = 0

	for i := 0; i < int(size); i++ {
		str, err := readString(file)
		if err != nil {
			return err
		}
		ht.Insert(str, "")
	}
	return nil
}

// ===================== HASH TABLE OPEN =====================

func (ht *HashTableOpen) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	fmt.Fprintf(writer, "%d %d\n", ht.Capacity, ht.Size)

	for i := 0; i < ht.Capacity; i++ {
		if ht.Table[i].Status == OCCUPIED {
			fmt.Fprintf(writer, "%s\t%s\n", ht.Table[i].Key, ht.Table[i].Value)
		}
	}
	return writer.Flush()
}

func (ht *HashTableOpen) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	line, err := reader.ReadString('\n')
	if err != nil {
		return err
	}
	parts := strings.Fields(strings.TrimSpace(line))
	if len(parts) < 2 {
		return fmt.Errorf("invalid format")
	}
	capacity, _ := strconv.Atoi(parts[0])
	size, _ := strconv.Atoi(parts[1])

	ht.Table = make([]HashEntry, capacity)
	ht.Capacity = capacity
	ht.Size = 0

	for i := 0; i < size; i++ {
		line, err := reader.ReadString('\n')
		if err != nil && err != io.EOF {
			return err
		}
		line = strings.TrimSuffix(line, "\n")
		parts := strings.SplitN(line, "\t", 2)
		key := parts[0]
		value := ""
		if len(parts) > 1 {
			value = parts[1]
		}
		ht.Insert(key, value)
	}
	return nil
}

func (ht *HashTableOpen) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	if err := binary.Write(file, binary.LittleEndian, int32(ht.Capacity)); err != nil {
		return err
	}
	if err := binary.Write(file, binary.LittleEndian, int32(ht.Size)); err != nil {
		return err
	}

	for i := 0; i < ht.Capacity; i++ {
		if ht.Table[i].Status == OCCUPIED {
			if err := writeString(file, ht.Table[i].Key); err != nil {
				return err
			}
			if err := writeString(file, ht.Table[i].Value); err != nil {
				return err
			}
		}
	}
	return nil
}

func (ht *HashTableOpen) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	var capacity, size int32
	if err := binary.Read(file, binary.LittleEndian, &capacity); err != nil {
		return err
	}
	if err := binary.Read(file, binary.LittleEndian, &size); err != nil {
		return err
	}

	ht.Table = make([]HashEntry, capacity)
	ht.Capacity = int(capacity)
	ht.Size = 0

	for i := 0; i < int(size); i++ {
		key, err := readString(file)
		if err != nil {
			return err
		}
		value, err := readString(file)
		if err != nil {
			return err
		}
		ht.Insert(key, value)
	}
	return nil
}

// ===================== BINARY SEARCH TREE =====================

func (bst *BinarySearchTree) SaveToText(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)
	saveTreeToText(writer, bst.Root)
	return writer.Flush()
}

func saveTreeToText(writer *bufio.Writer, node *TreeNode) {
	if node == nil {
		fmt.Fprintf(writer, "#\n")
		return
	}
	fmt.Fprintf(writer, "%d\n", node.Key)
	saveTreeToText(writer, node.Left)
	saveTreeToText(writer, node.Right)
}

func (bst *BinarySearchTree) LoadFromText(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	reader := bufio.NewReader(file)
	bst.Root = loadTreeFromText(reader)
	return nil
}

func loadTreeFromText(reader *bufio.Reader) *TreeNode {
	line, err := reader.ReadString('\n')
	if err != nil {
		return nil
	}
	line = strings.TrimSuffix(line, "\n")
	if line == "#" {
		return nil
	}
	key, err := strconv.Atoi(line)
	if err != nil {
		return nil
	}
	node := &TreeNode{Key: key}
	node.Left = loadTreeFromText(reader)
	node.Right = loadTreeFromText(reader)
	return node
}

func (bst *BinarySearchTree) SaveToBinary(filename string) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	return saveTreeToBinary(file, bst.Root)
}

func saveTreeToBinary(file *os.File, node *TreeNode) error {
	if node == nil {
		return binary.Write(file, binary.LittleEndian, int32(-1))
	}
	if err := binary.Write(file, binary.LittleEndian, int32(1)); err != nil {
		return err
	}
	if err := binary.Write(file, binary.LittleEndian, int32(node.Key)); err != nil {
		return err
	}
	if err := saveTreeToBinary(file, node.Left); err != nil {
		return err
	}
	return saveTreeToBinary(file, node.Right)
}

func (bst *BinarySearchTree) LoadFromBinary(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	bst.Root = loadTreeFromBinary(file)
	return nil
}

func loadTreeFromBinary(file *os.File) *TreeNode {
	var marker int32
	if err := binary.Read(file, binary.LittleEndian, &marker); err != nil {
		return nil
	}
	if marker == -1 {
		return nil
	}

	var key int32
	if err := binary.Read(file, binary.LittleEndian, &key); err != nil {
		return nil
	}

	node := &TreeNode{Key: int(key)}
	node.Left = loadTreeFromBinary(file)
	node.Right = loadTreeFromBinary(file)
	return node
}

// ===================== HELPER FUNCTIONS =====================

func writeString(file *os.File, s string) error {
	data := []byte(s)
	if err := binary.Write(file, binary.LittleEndian, int32(len(data))); err != nil {
		return err
	}
	_, err := file.Write(data)
	return err
}

func readString(file *os.File) (string, error) {
	var length int32
	if err := binary.Read(file, binary.LittleEndian, &length); err != nil {
		return "", err
	}
	data := make([]byte, length)
	if _, err := io.ReadFull(file, data); err != nil {
		return "", err
	}
	return string(data), nil
}
