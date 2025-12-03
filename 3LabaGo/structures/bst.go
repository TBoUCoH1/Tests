package structures

import "fmt"

type TreeNode struct {
	Key   int
	Left  *TreeNode
	Right *TreeNode
}

type BinarySearchTree struct {
	Root *TreeNode
}

func (bst *BinarySearchTree) Insert(key int) {
	bst.Root = insertRec(bst.Root, key)
}

func insertRec(node *TreeNode, key int) *TreeNode {
	if node == nil {
		return &TreeNode{Key: key}
	}
	if key < node.Key {
		node.Left = insertRec(node.Left, key)
	} else if key > node.Key {
		node.Right = insertRec(node.Right, key)
	}
	return node
}

func (bst *BinarySearchTree) Contains(key int) bool {
	return findRec(bst.Root, key) != nil
}

func findRec(node *TreeNode, key int) *TreeNode {
	if node == nil || node.Key == key {
		return node
	}
	if key < node.Key {
		return findRec(node.Left, key)
	}
	return findRec(node.Right, key)
}

func (bst *BinarySearchTree) Remove(key int) {
	bst.Root = removeRec(bst.Root, key)
}

func findMin(node *TreeNode) *TreeNode {
	current := node
	for current != nil && current.Left != nil {
		current = current.Left
	}
	return current
}

func removeRec(node *TreeNode, key int) *TreeNode {
	if node == nil {
		return node
	}
	if key < node.Key {
		node.Left = removeRec(node.Left, key)
	} else if key > node.Key {
		node.Right = removeRec(node.Right, key)
	} else {
		if node.Left == nil {
			return node.Right
		} else if node.Right == nil {
			return node.Left
		}
		temp := findMin(node.Right)
		node.Key = temp.Key
		node.Right = removeRec(node.Right, temp.Key)
	}
	return node
}

func (bst *BinarySearchTree) Print() {
	printInOrder(bst.Root)
	fmt.Println()
}

func printInOrder(node *TreeNode) {
	if node != nil {
		printInOrder(node.Left)
		fmt.Print(node.Key, " ")
		printInOrder(node.Right)
	}
}

func (bst *BinarySearchTree) Clear() {
	bst.Root = nil
}

func (bst *BinarySearchTree) IsEmpty() bool {
	return bst.Root == nil
}
