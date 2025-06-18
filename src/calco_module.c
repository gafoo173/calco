// calco_module.c
// Contains the PyMethodDef array, the PyModuleDef structure, and the PyInit_calco function.
// This file serves as the entry point for the Python module.

#include "calco.h" // Include the main header for function prototypes and definitions

// -----------------------------------------------------------------------------
// Module Methods Definition
// This table lists all functions that will be accessible from the Python module.
// -----------------------------------------------------------------------------
PyMethodDef CalcoMethods[] = {
    {"add", calco_add, METH_VARARGS, "Adds two double numbers."},
    {"subtract", calco_subtract, METH_VARARGS, "Subtracts two double numbers."},
    {"multiply", calco_multiply, METH_VARARGS, "Multiplies two double numbers."},
    {"divide", calco_divide, METH_VARARGS, "Divides two double numbers. Returns NaN for 0/0, Inf/-Inf for x/0."},
    {"power", calco_power, METH_VARARGS, "Raises base to the power of exponent."},
    {"square_root", calco_square_root, METH_VARARGS, "Calculates the square root of a number. Returns NaN for negative numbers."},
    {"cube_root", calco_cube_root, METH_VARARGS, "Calculates the cube root of a number."},
    {"absolute_value", calco_absolute_value, METH_VARARGS, "Calculates the absolute value of a double."},
    {"float_modulo", calco_float_modulo, METH_VARARGS, "Calculates the floating-point remainder of x/y."},
    {"hypotenuse", calco_hypotenuse, METH_VARARGS, "Calculates the hypotenuse of two sides (sqrt(x*x + y*y))."},
    {"positive_difference", calco_positive_difference, METH_VARARGS, "Calculates the positive difference: max(0, x - y)."},
    {"copy_sign_double", calco_copy_sign_double, METH_VARARGS, "Copies the sign of the second argument to the magnitude of the first."},
    {"floor_val", calco_floor_val, METH_VARARGS, "Rounds a double down to the nearest integer."},
    {"ceil_val", calco_ceil_val, METH_VARARGS, "Rounds a double up to the nearest integer."},
    {"round_val", calco_round_val, METH_VARARGS, "Rounds a double to the nearest integer, half away from zero."},
    {"nearbyint_val", calco_nearbyint_val, METH_VARARGS, "Rounds a double to the nearest integer, half to even."},
    {"truncate_val", calco_truncate_val, METH_VARARGS, "Truncalcoates a double towards zero."},
    {"natural_log", calco_natural_log, METH_VARARGS, "Calculates the natural logarithm (base e). Returns NaN for non-positive numbers."},
    {"log_base10", calco_log_base10, METH_VARARGS, "Calculates the base 10 logarithm. Returns NaN for non-positive numbers."},
    {"log_base2", calco_log_base2, METH_VARARGS, "Calculates the base 2 logarithm. Returns NaN for non-positive numbers."},
    {"log_custom_base", calco_log_custom_base, METH_VARARGS, "Calculates the logarithm to a custom base."},
    {"exponential", calco_exponential, METH_VARARGS, "Calculates e raised to the power of x."},
    {"exponential_base2", calco_exponential_base2, METH_VARARGS, "Calculates 2 raised to the power of x."},
    {"exponential_minus_1", calco_exponential_minus_1, METH_VARARGS, "Calculates (e^x - 1) accurately for small x."},
    {"sine", calco_sine, METH_VARARGS, "Calculates the sine of an angle (in radians)."},
    {"cosine", calco_cosine, METH_VARARGS, "Calculates the cosine of an angle (in radians)."},
    {"tangent", calco_tangent, METH_VARARGS, "Calculates the tangent of an angle (in radians)."},
    {"arcsine", calco_arcsine, METH_VARARGS, "Calculates the arcsine (inverse sine). Input must be between -1 and 1."},
    {"arccosine", calco_arccosine, METH_VARARGS, "Calculates the arccosine (inverse cosine). Input must be between -1 and 1."},
    {"arctangent", calco_arctangent, METH_VARARGS, "Calculates the arctangent (inverse tangent)."},
    {"arctangent2", calco_arctangent2, METH_VARARGS, "Calculates the arctangent of y/x in all four quadrants."},
    {"hyperbolic_sine", calco_hyperbolic_sine, METH_VARARGS, "Calculates the hyperbolic sine."},
    {"hyperbolic_cosine", calco_hyperbolic_cosine, METH_VARARGS, "Calculates the hyperbolic cosine."},
    {"hyperbolic_tangent", calco_hyperbolic_tangent, METH_VARARGS, "Calculates the hyperbolic tangent."},
    {"inverse_hyperbolic_sine", calco_inverse_hyperbolic_sine, METH_VARARGS, "Calculates the inverse hyperbolic sine."},
    {"inverse_hyperbolic_cosine", calco_inverse_hyperbolic_cosine, METH_VARARGS, "Calculates the inverse hyperbolic cosine. Input must be >= 1.0."},
    {"inverse_hyperbolic_tangent", calco_inverse_hyperbolic_tangent, METH_VARARGS, "Calculates the inverse hyperbolic tangent. Input must be between -1.0 and 1.0."},
    {"gamma_function", calco_gamma_function, METH_VARARGS, "Calculates the Gamma function."},
    {"log_gamma_function", calco_log_gamma_function, METH_VARARGS, "Calculates the natural logarithm of the absolute value of the Gamma function."},
    {"error_function", calco_error_function, METH_VARARGS, "Calculates the Error function."},
    {"complementary_error_function", calco_complementary_error_function, METH_VARARGS, "Calculates the Complementary error function (1 - erf(x))."},
    {"next_after_double", calco_next_after_double, METH_VARARGS, "Returns the next representable floating-point value after x in the direction of y."},
    {"fused_multiply_add", calco_fused_multiply_add, METH_VARARGS, "Calculates (a * b) + c with a single rounding."},
    {"degrees_to_radians", calco_degrees_to_radians, METH_VARARGS, "Converts an angle from degrees to radians."},
    {"radians_to_degrees", calco_radians_to_degrees, METH_VARARGS, "Converts an angle from radians to degrees."},
    {"get_pi", calco_get_pi, METH_VARARGS, "Returns the value of PI."},
    {"get_e", calco_get_e, METH_VARARGS, "Returns the value of E."},
    {"is_nan", calco_is_nan, METH_VARARGS, "Checks if a double is Not-a-Number (NaN)."},
    {"is_infinity", calco_is_infinity, METH_VARARGS, "Checks if a double is positive or negative infinity."},
    {NULL, NULL, 0, NULL}
};

// -----------------------------------------------------------------------------
// Module Definition Structure
// This structure describes the Python module itself.
// -----------------------------------------------------------------------------
struct PyModuleDef calcomodule = {
    PyModuleDef_HEAD_INIT, // Macro for initializing the structure
    "calco",               // Name of the module (as imported in Python: import calco)
    "A comprehensive and fast C library for mathematical operations.", // Docstring for the module
    -1,                    // Size of the module's per-interpreter state, or -1 if state is global
    CalcoMethods           // Table of module methods
};

// -----------------------------------------------------------------------------
// Module Initialization Function
// This is the function Python calls when importing the module.
// Its name must be PyInit_<module_name>, where <module_name> is defined in PyModuleDef.
// -----------------------------------------------------------------------------
PyMODINIT_FUNC PyInit_calco(void) {
    return PyModule_Create(&calcomodule);
}

