#!/usr/bin/env python
import unittest
from mergesort import mergesort, _sort, _merge

class TestMergeSort(unittest.TestCase):
    
    def test_sort(self):
        self.assertEqual(_sort([]), [])
        self.assertEqual(_sort([1]), [1])
        self.assertEqual(_sort([1,2]), [1,2])
        self.assertEqual(_sort([2,1]), [1,2])
        self.assertEqual(_sort([1,1]), [1,1])
        
        with self.assertRaises(Exception):
            _sort([1,2,3])


    def test_merge(self):
        self.assertEqual(_merge([], []), [])
        self.assertEqual(_merge([1], []), [1])
        self.assertEqual(_merge([], [1]), [1])
        self.assertEqual(_merge([1,2], [1]), [1,1,2])
        self.assertEqual(_merge([1], [2,3,4]), [1,2,3,4])
        self.assertEqual(_merge([2,3,4], [1]), [1,2,3,4])
    

    def test_mergesort(self):
        self.assertEqual(mergesort([]), [])
        self.assertEqual(mergesort([1]), [1])
        self.assertEqual(mergesort([1,1]), [1,1])
        self.assertEqual(mergesort([1,2]), [1,2])
        self.assertEqual(mergesort([2,1]), [1,2])
        self.assertEqual(mergesort([2,-1]), [-1,2])
        self.assertEqual(mergesort([3,1,2]), [1,2,3])
        self.assertEqual(mergesort([1,2,3,4]), [1,2,3,4])
        self.assertEqual(mergesort([2,1,3,4]), [1,2,3,4])
        self.assertEqual(mergesort([3,4,1,2]), [1,2,3,4])


if __name__ == '__main__':
    unittest.main()

