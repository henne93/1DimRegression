
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdint.h>
#include "../regression/reg.h"

static PyObject* py_linear_regression_uint16(PyObject* self, PyObject* args) {
    PyObject* input_obj;
    if (!PyArg_ParseTuple(args, "O", &input_obj)) {
        return NULL;
    }
    if (!PyList_Check(input_obj)) {
        PyErr_SetString(PyExc_TypeError, "Input must be a list of integers.");
        return NULL;
    }
    Py_ssize_t len = PyList_Size(input_obj);
    if (len < 2) {
        // Return zero-filled LineFit
        PyObject* out = PyDict_New();
        PyDict_SetItemString(out, "m_num", PyLong_FromLong(0));
        PyDict_SetItemString(out, "m_den", PyLong_FromLong(0));
        PyDict_SetItemString(out, "b_num", PyLong_FromLong(0));
        PyDict_SetItemString(out, "b_den", PyLong_FromLong(0));
        return out;
    }
    uint16_t* y = (uint16_t*)malloc(len * sizeof(uint16_t));
    if (y == NULL) {
        PyErr_SetString(PyExc_MemoryError, "Failed to allocate memory for input array.");
        return NULL;
    }
    for (Py_ssize_t i = 0; i < len; ++i) {
        PyObject* item = PyList_GetItem(input_obj, i);
        long val = PyLong_AsLong(item);
        if (val < 0 || val > 65535) {
            free(y);
            PyErr_SetString(PyExc_ValueError, "All elements must be uint16_t (0..65535).");
            return NULL;
        }
        y[i] = (uint16_t)val;
    }
    LineFit result = linear_regression_uint16(y, (uint32_t)len);
    free(y);
    // Return a Python dict with the regression results
    PyObject* out = PyDict_New();
    PyDict_SetItemString(out, "m_num", PyLong_FromLong(result.m_num));
    PyDict_SetItemString(out, "m_den", PyLong_FromLong(result.m_den));
    PyDict_SetItemString(out, "b_num", PyLong_FromLong(result.b_num));
    PyDict_SetItemString(out, "b_den", PyLong_FromLong(result.b_den));
    return out;
}

static PyMethodDef RegMethods[] = {
    {"linear_regression_uint16", py_linear_regression_uint16, METH_VARARGS, "Perform linear regression on a list of uint16_t values (length >= 2)."},
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
