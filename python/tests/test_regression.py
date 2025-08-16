import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../..')))

import unittest
import reg_wrapper

class TestRegression(unittest.TestCase):
    def test_identity(self):
        # y = x
        data = [i for i in range(32)]
        result = reg_wrapper.linear_regression_uint16(data)
        m = result['m_num'] / result['m_den']
        b = result['b_num'] / result['b_den']
        for x, y in enumerate(data):
            self.assertAlmostEqual(y, m * x + b, places=6)

    def test_constant(self):
        # y = 5
        data = [5 for _ in range(32)]
        result = reg_wrapper.linear_regression_uint16(data)
        m = result['m_num'] / result['m_den']
        b = result['b_num'] / result['b_den']
        for x, y in enumerate(data):
            self.assertAlmostEqual(y, m * x + b, places=6)

    def test_negative_slope(self):
        # y = -x + 31
        data = [31 - i for i in range(32)]
        result = reg_wrapper.linear_regression_uint16(data)
        m = result['m_num'] / result['m_den']
        b = result['b_num'] / result['b_den']
        for x, y in enumerate(data):
            self.assertAlmostEqual(y, m * x + b, places=6)

    def test_offset_line(self):
        # y = 2x + 3
        data = [2 * i + 3 for i in range(32)]
        result = reg_wrapper.linear_regression_uint16(data)
        m = result['m_num'] / result['m_den']
        b = result['b_num'] / result['b_den']
        for x, y in enumerate(data):
            self.assertAlmostEqual(y, m * x + b, places=6)

    def test_random(self):
        import random
        random.seed(0)
        data = [random.randint(0, 100) for _ in range(32)]
        result = reg_wrapper.linear_regression_uint16(data)
        # Just check that result is a dict with expected keys and denominators are not zero
        self.assertIn('m_num', result)
        self.assertIn('m_den', result)
        self.assertIn('b_num', result)
        self.assertIn('b_den', result)
        self.assertNotEqual(result['m_den'], 0)
        self.assertNotEqual(result['b_den'], 0)

    def test_outlier(self):
        data = [i for i in range(32)]
        data[16] = 1000  # Add a single outlier
        result = reg_wrapper.linear_regression_uint16(data)
        # Slope should not be exactly 1, intercept not exactly 0
        self.assertNotAlmostEqual(result['m_num']/result['m_den'], 1.0, places=6)
        self.assertNotAlmostEqual(result['b_num']/result['b_den'], 0.0, places=6)
    def test_two_points(self):
        data = [1, 3]
        result = reg_wrapper.linear_regression_uint16(data)
        self.assertEqual(result['m_den'], 1)
        self.assertEqual(result['m_num'], 2)
        self.assertEqual(result['b_den'], 2)
        self.assertEqual(result['b_num'], 2)

    def test_one_point(self):
        data = [42]
        result = reg_wrapper.linear_regression_uint16(data)
        self.assertEqual(result['m_num'], 0)
        self.assertEqual(result['m_den'], 0)
        self.assertEqual(result['b_num'], 0)
        self.assertEqual(result['b_den'], 0)

    def test_empty(self):
        data = []
        result = reg_wrapper.linear_regression_uint16(data)
        self.assertEqual(result['m_num'], 0)
        self.assertEqual(result['m_den'], 0)
        self.assertEqual(result['b_num'], 0)
        self.assertEqual(result['b_den'], 0)

    def test_large(self):
        data = [i for i in range(1000)]
        result = reg_wrapper.linear_regression_uint16(data)
        self.assertAlmostEqual(result['m_num']/result['m_den'], 1.0, places=6)
        self.assertAlmostEqual(result['b_num']/result['b_den'], 0.0, places=6)

if __name__ == "__main__":
    unittest.main()
