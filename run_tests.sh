#!/bin/bash
# Build the C extension and run Python unit tests
set -e

# Build C extension
python3 python/setup.py build_ext --inplace

# Run unit tests and save verbose output to test_report.txt
python3 -m unittest discover -v -s python/tests > test_report.txt
