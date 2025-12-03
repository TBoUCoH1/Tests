package structures

import (
	"fmt"
	"math/rand"
	"testing"
	"time"

	"github.com/stretchr/testify/assert"
)

func randomString(n int) string {
	var letters = []rune("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
	b := make([]rune, n)
	for i := range b {
		b[i] = letters[rand.Intn(len(letters))]
	}
	return string(b)
}

func init() {
	rand.Seed(time.Now().UnixNano())
}

func TestDynamicArray_Basic(t *testing.T) {
	da := NewDynamicArray(2)
	da.PushBack("A")
	da.PushBack("B")
	da.PushBack("C")

	assert.Equal(t, 3, da.Size())
	assert.Equal(t, "C", da.Get(2))

	da.RemoveAt(0)
	assert.Equal(t, "B", da.Get(0))
	assert.Equal(t, 2, da.Size())
	assert.Equal(t, "", da.Get(99))
	da.Insert(10, "fail")
	assert.Equal(t, 2, da.Size())
}

func TestDynamicArray_Random(t *testing.T) {
	da := NewDynamicArray(4)
	refSlice := []string{}

	for i := 0; i < 1000; i++ {
		op := rand.Intn(3)
		val := randomString(5)

		if op == 0 {
			da.PushBack(val)
			refSlice = append(refSlice, val)
		} else if op == 1 {
			if len(refSlice) > 0 {
				idx := rand.Intn(len(refSlice))
				assert.Equal(t, refSlice[idx], da.Get(idx))
			}
		} else {
			if len(refSlice) > 0 {
				idx := rand.Intn(len(refSlice))
				da.RemoveAt(idx)
				refSlice = append(refSlice[:idx], refSlice[idx+1:]...)
			}
		}
		assert.Equal(t, len(refSlice), da.Size())
	}
}

func BenchmarkDynamicArray_Push(b *testing.B) {
	for i := 0; i < b.N; i++ {
		da := NewDynamicArray(4)
		for j := 0; j < 1000; j++ {
			da.PushBack("test")
		}
	}
}

func TestSinglyList(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushFront("A")
	list.PushBack("B")

	assert.NotNil(t, list.Find("A"))
	assert.NotNil(t, list.Find("B"))

	list.PopFront()
	assert.Nil(t, list.Find("A"))

	list.RemoveValue("B")
	assert.Nil(t, list.Find("B"))
}

func BenchmarkSinglyList_PushFront(b *testing.B) {
	for i := 0; i < b.N; i++ {
		list := &SinglyLinkedList{}
		for j := 0; j < 1000; j++ {
			list.PushFront("val")
		}
	}
}

func TestStack(t *testing.T) {
	s := &Stack{}
	s.Push("1")
	s.Push("2")
	assert.Equal(t, "2", s.Peek())
	assert.Equal(t, "2", s.Pop())
	assert.Equal(t, "1", s.Pop())
	assert.True(t, s.IsEmpty())
}

func BenchmarkStack_Push(b *testing.B) {
	for i := 0; i < b.N; i++ {
		s := &Stack{}
		for j := 0; j < 1000; j++ {
			s.Push("data")
		}
	}
}

func TestQueue(t *testing.T) {
	q := &Queue{}
	q.Push("1")
	q.Push("2")
	assert.Equal(t, "1", q.Peek())
	assert.Equal(t, "1", q.Pop())
	assert.Equal(t, "2", q.Pop())
	assert.True(t, q.IsEmpty())
}

func BenchmarkQueue_Push(b *testing.B) {
	for i := 0; i < b.N; i++ {
		q := &Queue{}
		for j := 0; j < 1000; j++ {
			q.Push("data")
		}
	}
}

func TestHashTableOpen(t *testing.T) {
	ht := NewHashTableOpen(10)
	ht.Insert("apple", "red")
	ht.Insert("banana", "yellow")

	assert.Equal(t, "red", ht.Get("apple"))
	ht.Insert("apple", "green")
	assert.Equal(t, "green", ht.Get("apple"))

	ht.Remove("apple")
	assert.Equal(t, "", ht.Get("apple"))
}

func TestBST_CoverageHard(t *testing.T) {
	bst := &BinarySearchTree{}
	bst.Insert(10)
	bst.Insert(20)
	bst.Remove(10)
	assert.False(t, bst.Contains(10))
	assert.True(t, bst.Contains(20))

	bst2 := &BinarySearchTree{}
	bst2.Insert(10)
	bst2.Insert(5)
	bst2.Remove(10)
	assert.False(t, bst2.Contains(10))
	assert.True(t, bst2.Contains(5))

	bst3 := &BinarySearchTree{}
	bst3.Insert(50)
	bst3.Insert(30)
	bst3.Insert(70)
	bst3.Insert(20)
	bst3.Insert(40)

	bst3.Remove(30)
	assert.False(t, bst3.Contains(30))
	assert.True(t, bst3.Contains(20))
	assert.True(t, bst3.Contains(40))

	bst3.Print()
}

func TestDynamicArray_Coverage(t *testing.T) {
	da := NewDynamicArray(-5)
	assert.Equal(t, 4, da.capacity)

	da.Insert(-1, "fail")
	da.Insert(100, "fail")
	assert.Equal(t, 0, da.Size())

	da.RemoveAt(-1)
	da.RemoveAt(100)
	assert.Equal(t, 0, da.Size())

	assert.Equal(t, "", da.Get(-1))
	assert.Equal(t, "", da.Get(100))

	daSmall := NewDynamicArray(1)
	daSmall.Insert(0, "A")
	daSmall.Insert(0, "B")
	assert.Equal(t, 2, daSmall.Size())
	assert.Equal(t, "B", daSmall.Get(0))
	assert.Equal(t, "A", daSmall.Get(1))

	daSmall.Print()
}

func TestSinglyList_Coverage(t *testing.T) {
	list := &SinglyLinkedList{}

	list.PopFront()
	list.RemoveValue("A")
	list.PushBack("Head")

	list.PushBack("Mid")
	list.PushBack("Tail")

	list.RemoveValue("Head")
	assert.Equal(t, "Mid", list.Head.Key)

	list.RemoveValue("Tail")
	assert.Nil(t, list.Find("Tail"))

	list.RemoveValue("Ghost")

	list.Print()
}

func TestDoublyList_Coverage(t *testing.T) {
	dl := &DoublyLinkedList{}

	dl.PopFront()
	dl.PopBack()
	dl.PushBack("A")
	dl.PopBack()
	assert.Nil(t, dl.Head)
	assert.Nil(t, dl.Tail)

	dl.PushFront("A")
	dl.PopFront()
	assert.Nil(t, dl.Head)

	dl.PushBack("A")
	dl.PushBack("B")
	dl.PushBack("C")

	dl.RemoveValue("A")
	assert.Equal(t, "B", dl.Head.Data)
	assert.Nil(t, dl.Head.Prev)

	dl.RemoveValue("C")
	assert.Equal(t, "B", dl.Tail.Data)
	assert.Nil(t, dl.Tail.Next)

	dl.PushBack("C")
	dl.PushBack("D")
	dl.RemoveValue("C")
	assert.Equal(t, "D", dl.Tail.Data)
	assert.Equal(t, "B", dl.Tail.Prev.Data)

	dl.RemoveValue("Z")

	dl.Print()
}

func TestStack_Coverage(t *testing.T) {
	s := &Stack{}
	assert.Equal(t, "", s.Pop())
	assert.Equal(t, "", s.Peek())
}

func TestQueue_Coverage(t *testing.T) {
	q := &Queue{}
	assert.Equal(t, "", q.Pop())
	assert.Equal(t, "", q.Peek())

	q.Push("A")
	q.Pop()
	assert.True(t, q.IsEmpty())
	assert.Nil(t, q.Tail)
}

func TestHashTableOpen_Coverage(t *testing.T) {
	ht := NewHashTableOpen(0)
	assert.Equal(t, 101, ht.Capacity)

	htSmall := NewHashTableOpen(5)

	htSmall.Insert("A", "valA")
	htSmall.Insert("F", "valF")

	assert.Equal(t, "valA", htSmall.Get("A"))
	assert.Equal(t, "valF", htSmall.Get("F"))

	htSmall.Insert("F", "valF_New")
	assert.Equal(t, "valF_New", htSmall.Get("F"))

	htSmall.Remove("A")
	assert.Equal(t, "valF_New", htSmall.Get("F"))
	assert.Equal(t, "", htSmall.Get("A"))

	assert.Equal(t, "", htSmall.Get("Z"))
	htSmall.Remove("Z")

	htFull := NewHashTableOpen(2)
	htFull.Insert("A", "1")
	htFull.Insert("B", "2")
	assert.Equal(t, "", htFull.Get("C"))
}

func TestHashTable_Coverage(t *testing.T) {
	ht := NewHashTable()

	ht.Insert("A", "ignored")
	assert.True(t, ht.Contains("A"))
	assert.False(t, ht.Contains("B"))

	for i := 0; i < 200; i++ {
		key := fmt.Sprintf("key%d", i)
		ht.Insert(key, "")
	}

	for i := 0; i < 200; i++ {
		key := fmt.Sprintf("key%d", i)
		assert.True(t, ht.Contains(key))
	}

	ht.Remove("A")
	assert.False(t, ht.Contains("A"))

	ht.Remove("Z")

	htEmpty := NewHashTable()
	assert.False(t, htEmpty.Contains("A"))
	htEmpty.Remove("A")
}

func TestDynamicArray_Serialization(t *testing.T) {
	da := NewDynamicArray(4)
	da.PushBack("Hello")
	da.PushBack("World")
	da.PushBack("Test")

	da.SaveToText("test_array.txt")
	da2 := NewDynamicArray(1)
	da2.LoadFromText("test_array.txt")
	assert.Equal(t, da.Size(), da2.Size())
	for i := 0; i < da.Size(); i++ {
		assert.Equal(t, da.Get(i), da2.Get(i))
	}

	da.SaveToBinary("test_array.bin")
	da3 := NewDynamicArray(1)
	da3.LoadFromBinary("test_array.bin")
	assert.Equal(t, da.Size(), da3.Size())
	for i := 0; i < da.Size(); i++ {
		assert.Equal(t, da.Get(i), da3.Get(i))
	}
}

func TestSinglyList_Serialization(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack("A")
	list.PushBack("B")
	list.PushBack("C")

	list.SaveToText("test_singly.txt")
	list2 := &SinglyLinkedList{}
	list2.LoadFromText("test_singly.txt")
	assert.Equal(t, list.Size, list2.Size)
	assert.NotNil(t, list2.Find("A"))
	assert.NotNil(t, list2.Find("B"))
	assert.NotNil(t, list2.Find("C"))

	list.SaveToBinary("test_singly.bin")
	list3 := &SinglyLinkedList{}
	list3.LoadFromBinary("test_singly.bin")
	assert.Equal(t, list.Size, list3.Size)
	assert.NotNil(t, list3.Find("A"))
	assert.NotNil(t, list3.Find("B"))
	assert.NotNil(t, list3.Find("C"))
}

func TestDoublyList_Serialization(t *testing.T) {
	dl := &DoublyLinkedList{}
	dl.PushBack("X")
	dl.PushBack("Y")
	dl.PushBack("Z")

	dl.SaveToText("test_doubly.txt")
	dl2 := &DoublyLinkedList{}
	dl2.LoadFromText("test_doubly.txt")
	assert.Equal(t, dl.Size, dl2.Size)
	assert.Equal(t, "X", dl2.Head.Data)
	assert.Equal(t, "Z", dl2.Tail.Data)

	dl.SaveToBinary("test_doubly.bin")
	dl3 := &DoublyLinkedList{}
	dl3.LoadFromBinary("test_doubly.bin")
	assert.Equal(t, dl.Size, dl3.Size)
	assert.Equal(t, "X", dl3.Head.Data)
	assert.Equal(t, "Z", dl3.Tail.Data)
}

func TestStack_Serialization(t *testing.T) {
	s := &Stack{}
	s.Push("1")
	s.Push("2")
	s.Push("3")

	s.SaveToText("test_stack.txt")
	s2 := &Stack{}
	s2.LoadFromText("test_stack.txt")
	assert.Equal(t, s.Size, s2.Size)
	assert.Equal(t, "3", s2.Pop())
	assert.Equal(t, "2", s2.Pop())
	assert.Equal(t, "1", s2.Pop())

	s3 := &Stack{}
	s3.Push("1")
	s3.Push("2")
	s3.Push("3")
	s3.SaveToBinary("test_stack.bin")
	s4 := &Stack{}
	s4.LoadFromBinary("test_stack.bin")
	assert.Equal(t, s3.Size, s4.Size)
	assert.Equal(t, "3", s4.Pop())
	assert.Equal(t, "2", s4.Pop())
	assert.Equal(t, "1", s4.Pop())
}

func TestQueue_Serialization(t *testing.T) {
	q := &Queue{}
	q.Push("A")
	q.Push("B")
	q.Push("C")

	q.SaveToText("test_queue.txt")
	q2 := &Queue{}
	q2.LoadFromText("test_queue.txt")
	assert.Equal(t, q.Size, q2.Size)
	assert.Equal(t, "A", q2.Pop())
	assert.Equal(t, "B", q2.Pop())
	assert.Equal(t, "C", q2.Pop())

	q3 := &Queue{}
	q3.Push("A")
	q3.Push("B")
	q3.Push("C")
	q3.SaveToBinary("test_queue.bin")
	q4 := &Queue{}
	q4.LoadFromBinary("test_queue.bin")
	assert.Equal(t, q3.Size, q4.Size)
	assert.Equal(t, "A", q4.Pop())
	assert.Equal(t, "B", q4.Pop())
	assert.Equal(t, "C", q4.Pop())
}

func TestHashTable_Serialization(t *testing.T) {
	ht := NewHashTable()
	ht.Insert("apple", "")
	ht.Insert("banana", "")
	ht.Insert("cherry", "")

	ht.SaveToText("test_hashtable.txt")
	ht2 := NewHashTable()
	ht2.LoadFromText("test_hashtable.txt")
	assert.True(t, ht2.Contains("apple"))
	assert.True(t, ht2.Contains("banana"))
	assert.True(t, ht2.Contains("cherry"))

	ht.SaveToBinary("test_hashtable.bin")
	ht3 := NewHashTable()
	ht3.LoadFromBinary("test_hashtable.bin")
	assert.True(t, ht3.Contains("apple"))
	assert.True(t, ht3.Contains("banana"))
	assert.True(t, ht3.Contains("cherry"))
}

func TestHashTableOpen_Serialization(t *testing.T) {
	ht := NewHashTableOpen(10)
	ht.Insert("key1", "value1")
	ht.Insert("key2", "value2")
	ht.Insert("key3", "value3")

	ht.SaveToText("test_hashtable_open.txt")
	ht2 := NewHashTableOpen(10)
	ht2.LoadFromText("test_hashtable_open.txt")
	assert.Equal(t, "value1", ht2.Get("key1"))
	assert.Equal(t, "value2", ht2.Get("key2"))
	assert.Equal(t, "value3", ht2.Get("key3"))

	ht.SaveToBinary("test_hashtable_open.bin")
	ht3 := NewHashTableOpen(10)
	ht3.LoadFromBinary("test_hashtable_open.bin")
	assert.Equal(t, "value1", ht3.Get("key1"))
	assert.Equal(t, "value2", ht3.Get("key2"))
	assert.Equal(t, "value3", ht3.Get("key3"))
}

func TestBST_Serialization(t *testing.T) {
	bst := &BinarySearchTree{}
	bst.Insert(50)
	bst.Insert(30)
	bst.Insert(70)
	bst.Insert(20)
	bst.Insert(40)

	bst.SaveToText("test_bst.txt")
	bst2 := &BinarySearchTree{}
	bst2.LoadFromText("test_bst.txt")
	assert.True(t, bst2.Contains(50))
	assert.True(t, bst2.Contains(30))
	assert.True(t, bst2.Contains(70))
	assert.True(t, bst2.Contains(20))
	assert.True(t, bst2.Contains(40))

	bst.SaveToBinary("test_bst.bin")
	bst3 := &BinarySearchTree{}
	bst3.LoadFromBinary("test_bst.bin")
	assert.True(t, bst3.Contains(50))
	assert.True(t, bst3.Contains(30))
	assert.True(t, bst3.Contains(70))
	assert.True(t, bst3.Contains(20))
	assert.True(t, bst3.Contains(40))
}

func TestDynamicArray_AdditionalMethods(t *testing.T) {
	da := NewDynamicArray(4)
	da.PushBack("A")
	da.PushBack("B")
	da.PushBack("C")

	assert.Equal(t, 4, da.Capacity())

	da.Set(1, "X")
	assert.Equal(t, "X", da.Get(1))

	da.Set(-1, "fail")
	da.Set(100, "fail")
	assert.Equal(t, 3, da.Size())

	da.Clear()
	assert.Equal(t, 0, da.Size())
	assert.Equal(t, 4, da.Capacity())
}

func TestSinglyList_AdditionalMethods(t *testing.T) {
	list := &SinglyLinkedList{}
	list.PushBack("A")
	list.PushBack("B")
	list.PushBack("C")

	list.PopBack()
	assert.Nil(t, list.Find("C"))
	assert.Equal(t, 2, list.Size)

	list.PopBack()
	list.PopBack()
	assert.True(t, list.IsEmpty())

	list.PopBack()
	assert.True(t, list.IsEmpty())

	list.PushBack("A")
	list.PushBack("B")
	list.PushBack("C")

	assert.True(t, list.InsertAfter("A", "X"))
	assert.Equal(t, "X", list.Head.Next.Key)

	assert.True(t, list.InsertBefore("C", "Y"))
	assert.NotNil(t, list.Find("Y"))

	assert.False(t, list.InsertAfter("Z", "fail"))
	assert.False(t, list.InsertBefore("Z", "fail"))

	assert.True(t, list.DeleteAfter("A"))
	assert.Nil(t, list.Find("X"))

	assert.True(t, list.DeleteBefore("C"))
	assert.Nil(t, list.Find("Y"))

	assert.False(t, list.DeleteAfter("Z"))
	assert.False(t, list.DeleteBefore("A"))

	list.Clear()
	assert.True(t, list.IsEmpty())
	assert.Equal(t, 0, list.Size)
}

func TestDoublyList_AdditionalMethods(t *testing.T) {
	dl := &DoublyLinkedList{}

	assert.True(t, dl.IsEmpty())

	dl.PushBack("A")
	dl.PushBack("B")
	dl.PushBack("C")

	assert.NotNil(t, dl.Find("B"))
	assert.Nil(t, dl.Find("Z"))

	assert.True(t, dl.InsertAfter("A", "X"))
	assert.Equal(t, "X", dl.Head.Next.Data)

	assert.True(t, dl.InsertBefore("C", "Y"))
	assert.NotNil(t, dl.Find("Y"))

	assert.False(t, dl.InsertAfter("Z", "fail"))
	assert.False(t, dl.InsertBefore("Z", "fail"))

	assert.True(t, dl.DeleteAfter("A"))
	assert.Nil(t, dl.Find("X"))

	assert.True(t, dl.DeleteBefore("C"))
	assert.Nil(t, dl.Find("Y"))

	assert.False(t, dl.DeleteAfter("Z"))
	assert.False(t, dl.DeleteBefore("A"))

	dl.PrintBackward()

	dl.Clear()
	assert.True(t, dl.IsEmpty())
	assert.Nil(t, dl.Head)
	assert.Nil(t, dl.Tail)
}

func TestStack_AdditionalMethods(t *testing.T) {
	s := &Stack{}
	s.Push("A")
	s.Push("B")
	s.Push("C")

	s.Print()

	s.Clear()
	assert.True(t, s.IsEmpty())
	assert.Equal(t, 0, s.Size)
}

func TestQueue_AdditionalMethods(t *testing.T) {
	q := &Queue{}
	q.Push("A")
	q.Push("B")
	q.Push("C")

	q.Print()

	q.Clear()
	assert.True(t, q.IsEmpty())
	assert.Equal(t, 0, q.Size)
	assert.Nil(t, q.Head)
	assert.Nil(t, q.Tail)
}

func TestHashTable_AdditionalMethods(t *testing.T) {
	ht := NewHashTable()
	ht.Insert("A", "")
	ht.Insert("B", "")
	ht.Insert("C", "")

	ht.Clear()
	assert.False(t, ht.Contains("A"))
	assert.False(t, ht.Contains("B"))
	assert.False(t, ht.Contains("C"))
	assert.Equal(t, 0, ht.Size)
}

func TestHashTableOpen_AdditionalMethods(t *testing.T) {
	ht := NewHashTableOpen(10)
	ht.Insert("key1", "val1")
	ht.Insert("key2", "val2")
	ht.Insert("key3", "val3")

	ht.Print()
	ht.PrintStats()

	keys := ht.GetAllKeys()
	assert.Equal(t, 3, len(keys))

	ht.Clear()
	assert.Equal(t, 0, ht.Size)
	assert.Equal(t, "", ht.Get("key1"))

	keys = ht.GetAllKeys()
	assert.Equal(t, 0, len(keys))
}

func TestBST_AdditionalMethods(t *testing.T) {
	bst := &BinarySearchTree{}

	assert.True(t, bst.IsEmpty())

	bst.Insert(50)
	bst.Insert(30)
	bst.Insert(70)

	assert.False(t, bst.IsEmpty())

	bst.Clear()
	assert.True(t, bst.IsEmpty())
	assert.False(t, bst.Contains(50))
}
