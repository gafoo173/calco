//calco.c
#include <Python.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <errno.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

static PyObject* calco_add(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a + b);
}

static PyObject* calco_subtract(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a - b);
}

static PyObject* calco_multiply(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a * b);
}

static PyObject* calco_divide(PyObject* self, PyObject* args) {
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

static PyObject* calco_power(PyObject* self, PyObject* args) {
    double base, exponent;
    if (!PyArg_ParseTuple(args, "dd", &base, &exponent)) {
        return NULL;
    }
    return Py_BuildValue("d", pow(base, exponent));
}

static PyObject* calco_square_root(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", sqrt(x));
}

static PyObject* calco_cube_root(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", cbrt(x));
}

static PyObject* calco_absolute_value(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", fabs(x));
}

static PyObject* calco_float_modulo(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    if (y == 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", fmod(x, y));
}

static PyObject* calco_hypotenuse(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", hypot(x, y));
}

static PyObject* calco_positive_difference(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", fdim(x, y));
}

static PyObject* calco_copy_sign_double(PyObject* self, PyObject* args) {
    double magnitude, sign_source;
    if (!PyArg_ParseTuple(args, "dd", &magnitude, &sign_source)) {
        return NULL;
    }
    return Py_BuildValue("d", copysign(magnitude, sign_source));
}

static PyObject* calco_floor_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", floor(x));
}

static PyObject* calco_ceil_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", ceil(x));
}

static PyObject* calco_round_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", round(x));
}

static PyObject* calco_nearbyint_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", nearbyint(x));
}

static PyObject* calco_truncate_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", trunc(x));
}

static PyObject* calco_natural_log(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log(x));
}

static PyObject* calco_log_base10(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log10(x));
}

static PyObject* calco_log_base2(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= 0.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log2(x));
}

static PyObject* calco_log_custom_base(PyObject* self, PyObject* args) {
    double x, base;
    if (!PyArg_ParseTuple(args, "dd", &x, &base)) {
        return NULL;
    }
    if (x <= 0.0 || base <= 0.0 || base == 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", log(x) / log(base));
}

static PyObject* calco_exponential(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", exp(x));
}

static PyObject* calco_exponential_base2(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", exp2(x));
}

static PyObject* calco_exponential_minus_1(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", expm1(x));
}

static PyObject* calco_sine(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    return Py_BuildValue("d", sin(angle_rad));
}

static PyObject* calco_cosine(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    return Py_BuildValue("d", cos(angle_rad));
}

static PyObject* calco_tangent(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    double cos_val = cos(angle_rad);
    if (fabs(cos_val) < DBL_EPSILON) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", tan(angle_rad));
}

static PyObject* calco_arcsine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < -1.0 || x > 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", asin(x));
}

static PyObject* calco_arccosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < -1.0 || x > 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", acos(x));
}

static PyObject* calco_arctangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", atan(x));
}

static PyObject* calco_arctangent2(PyObject* self, PyObject* args) {
    double y, x;
    if (!PyArg_ParseTuple(args, "dd", &y, &x)) {
        return NULL;
    }
    return Py_BuildValue("d", atan2(y, x));
}

static PyObject* calco_hyperbolic_sine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", sinh(x));
}

static PyObject* calco_hyperbolic_cosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", cosh(x));
}

static PyObject* calco_hyperbolic_tangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", tanh(x));
}

static PyObject* calco_inverse_hyperbolic_sine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", asinh(x));
}

static PyObject* calco_inverse_hyperbolic_cosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x < 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", acosh(x));
}

static PyObject* calco_inverse_hyperbolic_tangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    if (x <= -1.0 || x >= 1.0) {
        return Py_BuildValue("d", NAN);
    }
    return Py_BuildValue("d", atanh(x));
}

static PyObject* calco_gamma_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", tgamma(x));
}

static PyObject* calco_log_gamma_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", lgamma(x));
}

static PyObject* calco_error_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", erf(x));
}

static PyObject* calco_complementary_error_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", erfc(x));
}

static PyObject* calco_next_after_double(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", nextafter(x, y));
}

static PyObject* calco_fused_multiply_add(PyObject* self, PyObject* args) {
    double a, b, c;
    if (!PyArg_ParseTuple(args, "ddd", &a, &b, &c)) {
        return NULL;
    }
    return Py_BuildValue("d", fma(a, b, c));
}

static PyObject* calco_degrees_to_radians(PyObject* self, PyObject* args) {
    double degrees;
    if (!PyArg_ParseTuple(args, "d", &degrees)) {
        return NULL;
    }
    return Py_BuildValue("d", degrees * (M_PI / 180.0));
}

static PyObject* calco_radians_to_degrees(PyObject* self, PyObject* args) {
    double radians;
    if (!PyArg_ParseTuple(args, "d", &radians)) {
        return NULL;
    }
    return Py_BuildValue("d", radians * (180.0 / M_PI));
}

static PyObject* calco_get_pi(PyObject* self, PyObject* args) {
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return Py_BuildValue("d", M_PI);
}

static PyObject* calco_get_e(PyObject* self, PyObject* args) {
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return Py_BuildValue("d", M_E);
}

static PyObject* calco_is_nan(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("b", (int)isnan(x));
}

static PyObject* calco_is_infinity(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("b", (int)isinf(x));
}

static PyMethodDef CalcoMethods[] = {
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
    {"truncate_val", calco_truncate_val, METH_VARARGS, "Truncates a double towards zero."},
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

static struct PyModuleDef calcomodule = {
    PyModuleDef_HEAD_INIT,
    "calco",
    "A comprehensive and fast C library for mathematical operations.",
    -1,
    CalcoMethods
};

PyMODINIT_FUNC PyInit_calco(void) {
    return PyModule_Create(&calcomodule);
}
