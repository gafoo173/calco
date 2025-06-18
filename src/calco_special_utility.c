// calco_special_utility.c
// Contains implementations for special functions and utility conversions (double only).

#include "calco.h" // Include the main header for prototypes

// -----------------------------------------------------------------------------
// Special/Advanced Functions
// -----------------------------------------------------------------------------

// Removed 'static' keyword from function definitions
PyObject* calco_gamma_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", tgamma(x));
}

// Removed 'static' keyword
PyObject* calco_log_gamma_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", lgamma(x));
}

// Removed 'static' keyword
PyObject* calco_error_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", erf(x));
}

// Removed 'static' keyword
PyObject* calco_complementary_error_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", erfc(x));
}

// Removed 'static' keyword
PyObject* calco_next_after_double(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", nextafter(x, y));
}

// Removed 'static' keyword
PyObject* calco_fused_multiply_add(PyObject* self, PyObject* args) {
    double a, b, c;
    if (!PyArg_ParseTuple(args, "ddd", &a, &b, &c)) {
        return NULL;
    }
    return Py_BuildValue("d", fma(a, b, c));
}

// -----------------------------------------------------------------------------
// Utility Functions and Conversions
// -----------------------------------------------------------------------------

// Removed 'static' keyword
PyObject* calco_degrees_to_radians(PyObject* self, PyObject* args) {
    double degrees;
    if (!PyArg_ParseTuple(args, "d", &degrees)) {
        return NULL;
    }
    return Py_BuildValue("d", degrees * (M_PI / 180.0));
}

// Removed 'static' keyword
PyObject* calco_radians_to_degrees(PyObject* self, PyObject* args) {
    double radians;
    if (!PyArg_ParseTuple(args, "d", &radians)) {
        return NULL;
    }
    return Py_BuildValue("d", radians * (180.0 / M_PI));
}

// Removed 'static' keyword
PyObject* calco_get_pi(PyObject* self, PyObject* args) {
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return Py_BuildValue("d", M_PI);
}

// Removed 'static' keyword
PyObject* calco_get_e(PyObject* self, PyObject* args) {
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return Py_BuildValue("d", M_E);
}

// Removed 'static' keyword
PyObject* calco_is_nan(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("b", (int)isnan(x));
}

// Removed 'static' keyword
PyObject* calco_is_infinity(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("b", (int)isinf(x));
}

