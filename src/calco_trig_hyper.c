// calco_trig_hyper.c
// Contains implementations for trigonometric and hyperbolic operations (double only).

#include "calco.h" // Include the main header for prototypes

// -----------------------------------------------------------------------------
// Trigonometric Operations (Radians)
// -----------------------------------------------------------------------------

// Removed 'static' keyword from function definitions
PyObject* calco_sine(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    return Py_BuildValue("d", sin(angle_rad));
}

// Removed 'static' keyword
PyObject* calco_cosine(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    return Py_BuildValue("d", cos(angle_rad));
}

// Removed 'static' keyword
PyObject* calco_tangent(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    double cos_val = cos(angle_rad);
    if (fabs(cos_val) < DBL_EPSILON) { // Check for values very close to zero
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", tan(angle_rad));
}

// -----------------------------------------------------------------------------
// Inverse Trigonometric Operations (Returns Radians)
// -----------------------------------------------------------------------------

// Removed 'static' keyword
PyObject* calco_arcsine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < -1.0 || x > 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", asin(x));
}

// Removed 'static' keyword
PyObject* calco_arccosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < -1.0 || x > 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", acos(x));
}

// Removed 'static' keyword
PyObject* calco_arctangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", atan(x));
}

// Removed 'static' keyword
PyObject* calco_arctangent2(PyObject* self, PyObject* args) {
    double y, x;
    if (!PyArg_ParseTuple(args, "dd", &y, &x)) {
        return NULL;
    }
    return Py_BuildValue("d", atan2(y, x));
}

// -----------------------------------------------------------------------------
// Hyperbolic Functions
// -----------------------------------------------------------------------------

// Removed 'static' keyword
PyObject* calco_hyperbolic_sine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", sinh(x));
}

// Removed 'static' keyword
PyObject* calco_hyperbolic_cosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", cosh(x));
}

// Removed 'static' keyword
PyObject* calco_hyperbolic_tangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", tanh(x));
}

// Removed 'static' keyword
PyObject* calco_inverse_hyperbolic_sine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", asinh(x));
}

// Removed 'static' keyword
PyObject* calco_inverse_hyperbolic_cosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", acosh(x));
}

// Removed 'static' keyword
PyObject* calco_inverse_hyperbolic_tangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= -1.0 || x >= 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", atanh(x));
}

