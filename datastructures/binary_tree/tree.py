import abc
import re


# abstract class for nodes. Gets a value of some type, 
# that needs to be specified in the implementation class.
class Node:
    # When the parent is None, then it is the root node.
    def __init__(self, value) -> None:
        self.value = value # Must implement the < operator
        self.parent = None
        self.right = None
        self.left = None

    def __repr__(self) -> str:
        return "Node: {}, left->{}, right->{}".format(
            self.value, 
            self.left.value if self.left is not None else "None",
            self.right.value if self.right is not None else "None")

class BinaryTree:
    def __init__(self) -> None:
        self.root = None
    
    def insert(self, node):
        if self.root is None:
            self.root = node
            self.root.parent = None # the root is the only without parent
        else:
            self._insert_from_root(node, self.root)

    def _insert_from_root(self, node, current_root):
        # Current root must always be not None
        if node.value <= current_root.value:
            if current_root.left is None:
                current_root.left = node
                current_root.left.parent = current_root
            else:
                self._insert_from_root(node, current_root.left)
        else:
            if current_root.right is None:
                current_root.right = node
                current_root.right.parent = current_root
            else:
                self._insert_from_root(node, current_root.right)

    # return the node with the value specified. If no node has the correct value,
    # return None.
    def search(self, value):
        if self.root is None:
            return None
        else:
            return self._search_from_root(value, self.root)

    def _search_from_root(self, value, current_root):
        if current_root is None:
            return None
        if current_root.value == value:
            # If there are multiple nodes with the same value, then return the one is the 
            # leftmost tree.
            left_search = self._search_from_root(value, current_root.left)
            if left_search != None and left_search.value == value:
                return left_search
            return current_root
        elif value < current_root.value:
            return self._search_from_root(value, current_root.left)
        elif value > current_root.value:
            return self._search_from_root(value, current_root.right)

    def search_first_larger(self, value):
        if self.root is None:
            return None
        else:
            return self._search_first_larger_from_root(value, self.root)

    def _search_first_larger_from_root(self, value, current_root):
        if current_root is None:
            return None
        if value >= current_root.value:
            return self._search_first_larger_from_root(value, current_root.right)
        else:
            recursive_large = self._search_first_larger_from_root(value, current_root.left)
            if recursive_large is None:
                return current_root
            else:
                if current_root.value < recursive_large.value:
                    return current_root
                else:
                    # In case of a tie, return the left child.
                    # In this way we are sure there are no left children
                    return recursive_large
    
    def delete(self, value):
        if self.root is not None:
            node_to_delete = self.search(value)
            if node_to_delete is not None:
                # First larger cannot have any left child!
                first_larger = self._search_first_larger_from_root(node_to_delete.value, node_to_delete)
                print(first_larger)
                assert first_larger is None or first_larger.left is None
                if first_larger is not None:
                    if first_larger.right is not None:
                        first_larger.right.parent = first_larger.parent
                        if first_larger.parent is not None:
                            if first_larger.parent.right == first_larger:
                                first_larger.parent.right = first_larger.right
                            else:
                                first_larger.parent.left = first_larger.right
                    
                    first_larger.parent = node_to_delete.parent
                    # If first_larger == node_to_delete.right, avoid first_larger.right to be itself!
                    first_larger.right = node_to_delete.right if node_to_delete.right != first_larger else first_larger.right
                    first_larger.left = node_to_delete.left
                if node_to_delete.parent is not None:
                    if node_to_delete.parent.right == node_to_delete:
                        node_to_delete.parent.right = first_larger
                    else:
                        node_to_delete.parent.left = first_larger
                if node_to_delete == self.root:
                    self.root = first_larger

    def scan(self):
        if self.root is None:
            return []
        else:
            return self._scan_from_node(self.root)

    def _scan_from_node(self, current_root):
        if current_root is None:
            return []
        else:
            left_list = self._scan_from_node(current_root.left)
            right_list = self._scan_from_node(current_root.right)
            return left_list + [current_root] + right_list
