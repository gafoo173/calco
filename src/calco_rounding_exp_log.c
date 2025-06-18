// calco_rounding_exp_log.c
// Contains implementations for rounding, exponential, and logarithmic operations (double only).

#include "calco.h" // Include the main header for prototypes

// -----------------------------------------------------------------------------
// Rounding and Truncation Functions
// -----------------------------------------------------------------------------

// Removed 'static' keyword from function definitions
PyObject* calco_floor_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", floor(x));
}

// Removed 'static' keyword
PyObject* calco_ceil_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", ceil(x));
}

// Removed 'static' keyword
PyObject* calco_round_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", round(x));
}

// Removed 'static' keyword
PyObject* calco_nearbyint_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", nearbyint(x));
}

// Removed 'static' keyword
PyObject* calco_truncate_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", trunc(x));
}

// -----------------------------------------------------------------------------
// Logarithmic Operations
// -----------------------------------------------------------------------------

// Removed 'static' keyword
PyObject* calco_natural_log(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log(x));
}

// Removed 'static' keyword
PyObject* calco_log_base10(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log10(x));
}

// Removed 'static' keyword
PyObject* calco_log_base2(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log2(x));
}

// Removed 'static' keyword
PyObject* calco_log_custom_base(PyObject* self, PyObject* args) {
    double x, base;
    if (!PyArg_ParseTuple(args, "dd", &x, &base)) {
        return NULL;
    }
    if (x <= 0.0 || base <= 0.0 || base == 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log(x) / log(base));
}

// -----------------------------------------------------------------------------
// Exponential Operations
// -----------------------------------------------------------------------------

// Removed 'static' keyword
PyObject* calco_exponential(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", exp(x));
}

// Removed 'static' keyword
PyObject* calco_exponential_base2(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", exp2(x));
}

// Removed 'static' keyword
PyObject* calco_exponential_minus_1(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", expm1(x));
}

