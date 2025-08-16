# 1DimRegression

This repository provides a C and Python implementation for performing linear regression on 1-dimensional data arrays of length 32. The core algorithm is implemented in C for performance and wrapped for Python usage, allowing easy integration and testing.

## Features
- Linear regression for 32-point data arrays
- C implementation for speed and efficiency
- Python wrapper for usability and testing
- Unit tests for validation

## Structure
- `src/` — C source code for regression and wrapper
- `python/` — Python setup, wrapper, and tests
- `build/` — Build artifacts (ignored in git)
- `run_tests.sh` — Script to build and test the project

## Usage
1. Build the C extension and run tests:
   ```bash
   ./run_tests.sh
   ```
2. Use the Python wrapper for regression tasks in your own scripts.

## License
This project is licensed under the MIT License. See `LICENSE` for details.
