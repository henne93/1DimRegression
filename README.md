# 1DimRegression

> **Platform:** This project is intended for Linux users. Compatibility with other operating systems is not guaranteed.

This repository provides a C implementation for performing linear regression on 1-dimensional data arrays of length 32. The core algorithm is written entirely in C for performance and efficiency. Python is used exclusively for unit testing and validation of the C implementation.

> **Note:** This project was created with the assistance of an AI programming agent.

## Features
- Linear regression for 32-point data arrays
- C implementation for speed and efficiency
- Python-based unit tests for validation

## Structure
- `src/` — C source code for regression and wrapper
- `python/` — Python setup and unit tests
- `build/` — Build artifacts (ignored in git)
- `run_tests.sh` — Script to build and test the project

## Usage
1. Build the C extension and run tests:
   ```bash
   ./run_tests.sh
   ```
2. Use the C implementation for regression tasks in your own projects.

## License
This project is licensed under the MIT License. See