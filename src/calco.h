// calco.h
// Main header file for the calco library.
// Contains function prototypes, constants, and module definitions.

#ifndef CALCO_H
#define CALCO_H

#include <Python.h>   // Python C API header
#include <stdio.h>    // For standard input/output (e.g., printf for debugging, if needed)
#include <math.h>     // For a wide range of mathematical functions (sqrt, pow, sin, cos, log, exp, etc.)
#include <float.h>    // For floating point limits and constants (e.g., DBL_EPSILON)
#include <errno.h>    // For error handling (e.g., for NAN/INFINITY)

// Define common mathematical constants if not already defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// -----------------------------------------------------------------------------
// Function Prototypes (all double precision)
// -----------------------------------------------------------------------------

// Basic Arithmetic Operations
PyObject* calco_add(PyObject* self, PyObject* args);
PyObject* calco_subtract(PyObject* self, PyObject* args);
PyObject* calco_multiply(PyObject* self, PyObject* args);
PyObject* calco_divide(PyObject* self, PyObject* args);
PyObject* calco_power(PyObject* self, PyObject* args);
PyObject* calco_square_root(PyObject* self, PyObject* args);
PyObject* calco_cube_root(PyObject* self, PyObject* args);
PyObject* calco_absolute_value(PyObject* self, PyObject* args);
PyObject* calco_float_modulo(PyObject* self, PyObject* args);
PyObject* calco_hypotenuse(PyObject* self, PyObject* args);
PyObject* calco_positive_difference(PyObject* self, PyObject* args);
PyObject* calco_copy_sign_double(PyObject* self, PyObject* args);

// Rounding and Truncation Functions
PyObject* calco_floor_val(PyObject* self, PyObject* args);
PyObject* calco_ceil_val(PyObject* self, PyObject* args);
PyObject* calco_round_val(PyObject* self, PyObject* args);
PyObject* calco_nearbyint_val(PyObject* self, PyObject* args);
PyObject* calco_truncate_val(PyObject* self, PyObject* args);

// Logarithmic Operations
PyObject* calco_natural_log(PyObject* self, PyObject* args);
PyObject* calco_log_base10(PyObject* self, PyObject* args);
PyObject* calco_log_base2(PyObject* self, PyObject* args);
PyObject* calco_log_custom_base(PyObject* self, PyObject* args);

// Exponential Operations
PyObject* calco_exponential(PyObject* self, PyObject* args);
PyObject* calco_exponential_base2(PyObject* self, PyObject* args);
PyObject* calco_exponential_minus_1(PyObject* self, PyObject* args);

// Trigonometric Operations (Radians)
PyObject* calco_sine(PyObject* self, PyObject* args);
PyObject* calco_cosine(PyObject* self, PyObject* args);
PyObject* calco_tangent(PyObject* self, PyObject* args);

// Inverse Trigonometric Operations (Returns Radians)
PyObject* calco_arcsine(PyObject* self, PyObject* args);
PyObject* calco_arccosine(PyObject* self, PyObject* args);
PyObject* calco_arctangent(PyObject* self, PyObject* args);
PyObject* calco_arctangent2(PyObject* self, PyObject* args);

// Hyperbolic Functions
PyObject* calco_hyperbolic_sine(PyObject* self, PyObject* args);
PyObject* calco_hyperbolic_cosine(PyObject* self, PyObject* args);
PyObject* calco_hyperbolic_tangent(PyObject* self, PyObject* args);
PyObject* calco_inverse_hyperbolic_sine(PyObject* self, PyObject* args);
PyObject* calco_inverse_hyperbolic_cosine(PyObject* self, PyObject* args);
PyObject* calco_inverse_hyperbolic_tangent(PyObject* self, PyObject* args);

// Special/Advanced Functions
PyObject* calco_gamma_function(PyObject* self, PyObject* args);
PyObject* calco_log_gamma_function(PyObject* self, PyObject* args);
PyObject* calco_error_function(PyObject* self, PyObject* args);
PyObject* calco_complementary_error_function(PyObject* self, PyObject* args);
PyObject* calco_next_after_double(PyObject* self, PyObject* args);
PyObject* calco_fused_multiply_add(PyObject* self, PyObject* args);

// Utility Functions and Conversions
PyObject* calco_degrees_to_radians(PyObject* self, PyObject* args);
PyObject* calco_radians_to_degrees(PyObject* self, PyObject* args);
PyObject* calco_get_pi(PyObject* self, PyObject* args);
PyObject* calco_get_e(PyObject* self, PyObject* args);
PyObject* calco_is_nan(PyObject* self, PyObject* args);
PyObject* calco_is_infinity(PyObject* self, PyObject* args);

// -----------------------------------------------------------------------------
// Module Definition (Declared here, defined in calco_module.c)
// -----------------------------------------------------------------------------
extern PyMethodDef CalcoMethods[];
extern struct PyModuleDef calcomodule;

#endif // CALCO_H
