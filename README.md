# 1DimRegression

This repository provides a C implementation for performing linear regression on 1-dimensional data arrays of length 32. The core algorithm is written entirely in C for performance and efficiency. Python is used exclusively for unit testing and validation of the C implementation.

## Features
- Linear regression for 32-point data arrays
- C implementation for speed and efficiency
- Python-based unit tests for validation
- Suitable for integration in embedded systems (e.g., ARM microcontrollers)

## Structure
- `src/` — C source code for regression and wrapper
- `python/` — Python setup and unit tests
- `build/` — Build artifacts (ignored in git)
- `run_tests.sh` — Script to build and test the project

## Dependencies
- **Linux shell tools**: bash
- **C compiler**: gcc (or compatible)
- **Python 3**: for running unit tests
- **Python modules**: unittest (standard library), os, sys, random
- **Python package**: setuptools

## Usage
1. Build the C extension and run tests (Linux only):
   ```bash
   ./run_tests.sh
   ```
2. Use the C implementation for regression tasks in your own projects.

> **Platform:** This project is intended for Linux users. Compatibility with other operating systems is not guaranteed.

## Example Usage
The C implementation is suitable for embedded targets, such as ARM microcontrollers. You can integrate the regression function into your firmware to process sensor data or other univariate signals in real time.

### C Example
```c
#include "reg.h"
uint16_t data[] = {1, 2, 3, 4, 5};
uint32_t len = sizeof(data) / sizeof(data[0]);
LineFit fit = linear_regression_uint16(data, len);
// Use fit.m_num, fit.m_den, fit.b_num, fit.b_den

## Contributing
Contributions are welcome! Please open issues or submit pull requests for improvements, bug fixes, or new features.
## Contact
For questions or support, open an issue on GitHub or contact the repository owner.

## License
This project is licensed under the MIT License. See [LICENSE](LICENSE).

> **Note:** This project was created with the assistance of an AI programming agent.