package structures

import "fmt"

type QNode struct {
	Data string
	Next *QNode
}

type Queue struct {
	Head *QNode
	Tail *QNode
	Size int
}

func (q *Queue) Push(value string) {
	newNode := &QNode{Data: value}
	if q.Tail == nil {
		q.Head = newNode
		q.Tail = newNode
	} else {
		q.Tail.Next = newNode
		q.Tail = newNode
	}
	q.Size++
}

func (q *Queue) Pop() string {
	if q.Head == nil {
		return ""
	}
	val := q.Head.Data
	q.Head = q.Head.Next
	if q.Head == nil {
		q.Tail = nil
	}
	q.Size--
	return val
}

func (q *Queue) Peek() string {
	if q.Head == nil {
		return ""
	}
	return q.Head.Data
}

func (q *Queue) IsEmpty() bool {
	return q.Head == nil
}

func (q *Queue) Print() {
	temp := q.Head
	for temp != nil {
		fmt.Print(temp.Data, " ")
		temp = temp.Next
	}
	fmt.Println()
}

func (q *Queue) Clear() {
	q.Head = nil
	q.Tail = nil
	q.Size = 0
}
