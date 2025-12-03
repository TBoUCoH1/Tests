package structures

import "fmt"

type SNode struct {
	Data string
	Next *SNode
}

type Stack struct {
	Top  *SNode
	Size int
}

func (s *Stack) Push(value string) {
	s.Top = &SNode{Data: value, Next: s.Top}
	s.Size++
}

func (s *Stack) Pop() string {
	if s.Top == nil {
		return ""
	}
	val := s.Top.Data
	s.Top = s.Top.Next
	s.Size--
	return val
}

func (s *Stack) Peek() string {
	if s.Top == nil {
		return ""
	}
	return s.Top.Data
}

func (s *Stack) IsEmpty() bool {
	return s.Top == nil
}

func (s *Stack) Print() {
	temp := s.Top
	for temp != nil {
		fmt.Println(temp.Data)
		temp = temp.Next
	}
}

func (s *Stack) Clear() {
	s.Top = nil
	s.Size = 0
}
