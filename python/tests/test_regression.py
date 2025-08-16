import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '../..')))

import unittest
import reg_wrapper

class TestRegression(unittest.TestCase):
    def test_identity(self):
        data = [i for i in range(32)]
        result = reg_wrapper.linear_regression_32(data)
        self.assertAlmostEqual(result['m_num']/result['m_den'], 1.0, places=6)
        self.assertAlmostEqual(result['b_num']/result['b_den'], 0.0, places=6)

    def test_constant(self):
        data = [5 for _ in range(32)]
        result = reg_wrapper.linear_regression_32(data)
        self.assertAlmostEqual(result['m_num']/result['m_den'], 0.0, places=6)
        self.assertAlmostEqual(result['b_num']/result['b_den'], 5.0, places=6)

    def test_negative_slope(self):
        data = [31 - i for i in range(32)]
        result = reg_wrapper.linear_regression_32(data)
        self.assertAlmostEqual(result['m_num']/result['m_den'], -1.0, places=6)
        self.assertAlmostEqual(result['b_num']/result['b_den'], 31.0, places=6)

    def test_offset_line(self):
        data = [2 * i + 3 for i in range(32)]
        result = reg_wrapper.linear_regression_32(data)
        self.assertAlmostEqual(result['m_num']/result['m_den'], 2.0, places=6)
        self.assertAlmostEqual(result['b_num']/result['b_den'], 3.0, places=6)

    def test_random(self):
        import random
        random.seed(0)
        data = [random.randint(0, 100) for _ in range(32)]
        result = reg_wrapper.linear_regression_32(data)
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
        result = reg_wrapper.linear_regression_32(data)
        # Slope should not be exactly 1, intercept not exactly 0
        self.assertNotAlmostEqual(result['m_num']/result['m_den'], 1.0, places=6)
        self.assertNotAlmostEqual(result['b_num']/result['b_den'], 0.0, places=6)

if __name__ == "__main__":
    unittest.main()
