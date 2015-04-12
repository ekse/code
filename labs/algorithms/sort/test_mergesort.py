#!/usr/bin/env python
import unittest
from mergesort import mergesort

class TestMergeSort(unittest.TestCase):
    
    def test_sort(self):
        self.assertEqual(mergesort([3,1,2]), [1,2,3])
        self.assertEqual(mergesort([]), [])
        self.assertEqual(mergesort([1,2,3,4]), [1,2,3,4])
        self.assertEqual(mergesort([2,1,3,4]), [1,2,3,4])


if __name__ == '__main__':
    unittest.main()

