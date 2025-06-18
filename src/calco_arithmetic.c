// calco_arithmetic.c
// Contains implementations for basic arithmetic operations (double precision).

#include "calco.h" // Include the main header for prototypes and definitions

// -----------------------------------------------------------------------------
// Basic Arithmetic Operations
// -----------------------------------------------------------------------------

// Removed 'static' keyword from function definitions to match non-static declarations in calco.h
PyObject* calco_add(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a + b);
}

// Removed 'static' keyword
PyObject* calco_subtract(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a - b);
}

// Removed 'static' keyword
PyObject* calco_multiply(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a * b);
}

// Removed 'static' keyword
PyObject* calco_divide(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    if (b == 0.0) {
        if (a == 0.0) {
            return Py_BuildValue("d", NAN);
        }
        return Py_BuildValue("d", (a > 0.0) ? INFINITY : -INFINITY);
    }
    return Py_BuildValue("d", a / b);
}

// Removed 'static' keyword
PyObject* calco_power(PyObject* self, PyObject* args) {
    double base, exponent;
    if (!PyArg_ParseTuple(args, "dd", &base, &exponent)) {
        return NULL;
    }
    return Py_BuildValue("d", pow(base, exponent));
}

// Removed 'static' keyword
PyObject* calco_square_root(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", sqrt(x));
}

// Removed 'static' keyword
PyObject* calco_cube_root(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", cbrt(x));
}

// Removed 'static' keyword
PyObject* calco_absolute_value(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", fabs(x));
}


PyObject* calco_float_modulo(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    if (y == 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", fmod(x, y));
}


PyObject* calco_hypotenuse(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", hypot(x, y));
}


PyObject* calco_positive_difference(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", fdim(x, y));
}


PyObject* calco_copy_sign_double(PyObject* self, PyObject* args) {
    double magnitude, sign_source;
    if (!PyArg_ParseTuple(args, "dd", &magnitude, &sign_source)) {
        return NULL;
    }
    return Py_BuildValue("d", copysign(magnitude, sign_source));
}

