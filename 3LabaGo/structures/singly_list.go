package structures

import "fmt"

type FNode struct {
	Key  string
	Next *FNode
}

type SinglyLinkedList struct {
	Head *FNode
	Size int
}

func (list *SinglyLinkedList) PushFront(key string) {
	newNode := &FNode{Key: key, Next: list.Head}
	list.Head = newNode
	list.Size++
}

func (list *SinglyLinkedList) PushBack(key string) {
	if list.Head == nil {
		list.PushFront(key)
		return
	}
	temp := list.Head
	for temp.Next != nil {
		temp = temp.Next
	}
	temp.Next = &FNode{Key: key, Next: nil}
	list.Size++
}

func (list *SinglyLinkedList) PopFront() {
	if list.Head == nil {
		return
	}
	list.Head = list.Head.Next
	list.Size--
}

func (list *SinglyLinkedList) RemoveValue(value string) {
	if list.Head == nil {
		return
	}
	if list.Head.Key == value {
		list.PopFront()
		return
	}
	current := list.Head
	for current.Next != nil && current.Next.Key != value {
		current = current.Next
	}
	if current.Next != nil {
		current.Next = current.Next.Next
		list.Size--
	}
}

func (list *SinglyLinkedList) Find(value string) *FNode {
	temp := list.Head
	for temp != nil {
		if temp.Key == value {
			return temp
		}
		temp = temp.Next
	}
	return nil
}

func (list *SinglyLinkedList) Print() {
	temp := list.Head
	for temp != nil {
		fmt.Printf("\"%s\" ", temp.Key)
		temp = temp.Next
	}
	fmt.Println()
}

func (list *SinglyLinkedList) PopBack() {
	if list.Head == nil {
		return
	}
	if list.Head.Next == nil {
		list.Head = nil
		list.Size--
		return
	}
	temp := list.Head
	for temp.Next.Next != nil {
		temp = temp.Next
	}
	temp.Next = nil
	list.Size--
}

func (list *SinglyLinkedList) InsertAfter(target, key string) bool {
	node := list.Find(target)
	if node == nil {
		return false
	}
	node.Next = &FNode{Key: key, Next: node.Next}
	list.Size++
	return true
}

func (list *SinglyLinkedList) InsertBefore(target, key string) bool {
	if list.Head == nil {
		return false
	}
	if list.Head.Key == target {
		list.PushFront(key)
		return true
	}
	prev := list.Head
	curr := list.Head.Next
	for curr != nil && curr.Key != target {
		prev = curr
		curr = curr.Next
	}
	if curr == nil {
		return false
	}
	prev.Next = &FNode{Key: key, Next: curr}
	list.Size++
	return true
}

func (list *SinglyLinkedList) DeleteAfter(target string) bool {
	node := list.Find(target)
	if node == nil || node.Next == nil {
		return false
	}
	node.Next = node.Next.Next
	list.Size--
	return true
}

func (list *SinglyLinkedList) DeleteBefore(target string) bool {
	if list.Head == nil || list.Head.Key == target {
		return false
	}
	var prevPrev *FNode = nil
	prev := list.Head
	curr := list.Head.Next
	for curr != nil && curr.Key != target {
		prevPrev = prev
		prev = curr
		curr = curr.Next
	}
	if curr == nil {
		return false
	}
	if prevPrev == nil {
		list.PopFront()
	} else {
		prevPrev.Next = curr
		list.Size--
	}
	return true
}

func (list *SinglyLinkedList) Clear() {
	list.Head = nil
	list.Size = 0
}

func (list *SinglyLinkedList) IsEmpty() bool {
	return list.Head == nil
}
