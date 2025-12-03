package structures

import "fmt"

type LNode struct {
	Data string
	Next *LNode
	Prev *LNode
}

type DoublyLinkedList struct {
	Head *LNode
	Tail *LNode
	Size int
}

func (list *DoublyLinkedList) PushFront(value string) {
	newNode := &LNode{Data: value, Next: list.Head, Prev: nil}
	if list.Head != nil {
		list.Head.Prev = newNode
	}
	list.Head = newNode
	if list.Tail == nil {
		list.Tail = list.Head
	}
	list.Size++
}

func (list *DoublyLinkedList) PushBack(value string) {
	if list.Tail == nil {
		list.PushFront(value)
		return
	}
	newNode := &LNode{Data: value, Next: nil, Prev: list.Tail}
	list.Tail.Next = newNode
	list.Tail = newNode
	list.Size++
}

func (list *DoublyLinkedList) PopFront() {
	if list.Head == nil {
		return
	}
	list.Head = list.Head.Next
	if list.Head != nil {
		list.Head.Prev = nil
	} else {
		list.Tail = nil
	}
	list.Size--
}

func (list *DoublyLinkedList) PopBack() {
	if list.Tail == nil {
		return
	}
	list.Tail = list.Tail.Prev
	if list.Tail != nil {
		list.Tail.Next = nil
	} else {
		list.Head = nil
	}
	list.Size--
}

func (list *DoublyLinkedList) RemoveValue(value string) {
	current := list.Head
	for current != nil {
		if current.Data == value {
			if current.Prev != nil {
				current.Prev.Next = current.Next
			} else {
				list.Head = current.Next
			}
			if current.Next != nil {
				current.Next.Prev = current.Prev
			} else {
				list.Tail = current.Prev
			}
			list.Size--
			return
		}
		current = current.Next
	}
}

func (list *DoublyLinkedList) Print() {
	temp := list.Head
	for temp != nil {
		fmt.Print(temp.Data, " <-> ")
		temp = temp.Next
	}
	fmt.Println("NULL")
}

func (list *DoublyLinkedList) PrintBackward() {
	temp := list.Tail
	for temp != nil {
		fmt.Print(temp.Data, " <-> ")
		temp = temp.Prev
	}
	fmt.Println("NULL")
}

func (list *DoublyLinkedList) Find(value string) *LNode {
	temp := list.Head
	for temp != nil {
		if temp.Data == value {
			return temp
		}
		temp = temp.Next
	}
	return nil
}

func (list *DoublyLinkedList) InsertAfter(target, value string) bool {
	targetNode := list.Find(target)
	if targetNode == nil {
		return false
	}
	newNode := &LNode{Data: value, Next: targetNode.Next, Prev: targetNode}
	if targetNode.Next != nil {
		targetNode.Next.Prev = newNode
	} else {
		list.Tail = newNode
	}
	targetNode.Next = newNode
	list.Size++
	return true
}

func (list *DoublyLinkedList) InsertBefore(target, value string) bool {
	targetNode := list.Find(target)
	if targetNode == nil {
		return false
	}
	if targetNode == list.Head {
		list.PushFront(value)
		return true
	}
	newNode := &LNode{Data: value, Next: targetNode, Prev: targetNode.Prev}
	targetNode.Prev.Next = newNode
	targetNode.Prev = newNode
	list.Size++
	return true
}

func (list *DoublyLinkedList) DeleteAfter(target string) bool {
	targetNode := list.Find(target)
	if targetNode == nil || targetNode.Next == nil {
		return false
	}
	nodeToDelete := targetNode.Next
	targetNode.Next = nodeToDelete.Next
	if nodeToDelete.Next != nil {
		nodeToDelete.Next.Prev = targetNode
	} else {
		list.Tail = targetNode
	}
	list.Size--
	return true
}

func (list *DoublyLinkedList) DeleteBefore(target string) bool {
	targetNode := list.Find(target)
	if targetNode == nil || targetNode.Prev == nil {
		return false
	}
	nodeToDelete := targetNode.Prev
	targetNode.Prev = nodeToDelete.Prev
	if nodeToDelete.Prev != nil {
		nodeToDelete.Prev.Next = targetNode
	} else {
		list.Head = targetNode
	}
	list.Size--
	return true
}

func (list *DoublyLinkedList) Clear() {
	list.Head = nil
	list.Tail = nil
	list.Size = 0
}

func (list *DoublyLinkedList) IsEmpty() bool {
	return list.Head == nil
}
