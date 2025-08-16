
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdint.h>
#include "../regression/reg.h"

static PyObject* py_linear_regression_32(PyObject* self, PyObject* args) {
    PyObject* input_obj;
    if (!PyArg_ParseTuple(args, "O", &input_obj)) {
        return NULL;
    }
    if (!PyList_Check(input_obj)) {
        PyErr_SetString(PyExc_TypeError, "Input must be a list of 32 integers.");
        return NULL;
    }
    if (PyList_Size(input_obj) != N) {
        PyErr_SetString(PyExc_ValueError, "Input list must have 32 elements.");
        return NULL;
    }
    uint16_t y[N];
    for (int i = 0; i < N; ++i) {
        PyObject* item = PyList_GetItem(input_obj, i);
        long val = PyLong_AsLong(item);
        if (val < 0 || val > 65535) {
            PyErr_SetString(PyExc_ValueError, "All elements must be uint16_t (0..65535).");
            return NULL;
        }
        y[i] = (uint16_t)val;
    }
    LineFit result = linear_regression_32(y);
    // Return a Python dict with the regression results
    PyObject* out = PyDict_New();
    PyDict_SetItemString(out, "m_num", PyLong_FromLong(result.m_num));
    PyDict_SetItemString(out, "m_den", PyLong_FromLong(result.m_den));
    PyDict_SetItemString(out, "b_num", PyLong_FromLong(result.b_num));
    PyDict_SetItemString(out, "b_den", PyLong_FromLong(result.b_den));
    return out;
}

static PyMethodDef RegMethods[] = {
    {"linear_regression_32", py_linear_regression_32, METH_VARARGS, "Perform linear regression on 32 uint16_t values."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef regmodule = {
    PyModuleDef_HEAD_INIT,
    "reg_wrapper",
    NULL,
    -1,
    RegMethods
};

PyMODINIT_FUNC PyInit_reg_wrapper(void) {
    return PyModule_Create(&regmodule);
}
