// calco.c
// ملف يضم عمليات رياضية متقدمة وسريعة ودقيقة لاستخدامها كمكتبة في بايثون
// تم تعديل هذا الملف ليتضمن واجهة برمجة تطبيقات بايثون C (Python C API)
// لكي يمكن ترجمته كوحدة امتداد (extension module) لبايثون.

#include <Python.h>  // Include the Python C API header
#include <stdio.h>   // For standard input/output (e.g., printf for debugging, if needed)
#include <math.h>    // For a wide range of mathematical functions (sqrt, pow, sin, cos, log, exp, etc.)
#include <float.h>   // For floating point limits and constants (e.g., DBL_EPSILON)
#include <errno.h>   // For error handling (e.g., detecting domain errors from math functions)

// تعريف بعض الثوابت الرياضية الشائعة إذا لم تكن معرفة مسبقًا في math.h
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef M_E
#define M_E 2.71828182845904523536
#endif

// تعليقات عامة حول التصميم والأداء:
// - تم استخدام نوع البيانات 'double' لجميع المدخلات والمخرجات لضمان أقصى دقة ممكنة
//   في حسابات الفاصلة العائمة.
// - تعتمد السرعة بشكل كبير على الاستخدام الأمثل لوظائف مكتبة C القياسية <math.h>،
//   والتي تم تحسينها بشكل كبير لأداء عالي على معظم المعالجات.
// - تم تضمين معالجة الأخطاء للعديد من الدوال لإرجاع 'NaN' (ليس رقمًا)
//   عندما تكون المدخلات خارج النطاق الصالح للدالة، مما يضمن سلوكًا متوقعًا.

// -----------------------------------------------------------------------------
// I. عمليات حسابية أساسية (الجبر) - Core Arithmetic (Algebraic) Operations
// -----------------------------------------------------------------------------

// دالة PyObject* هي نوع البيانات الذي تستخدمه بايثون لتمثيل الكائنات.
// Py_ssize_t n_args هو عدد الوسائط.
// PyObject* args هو كائن tuple يحتوي على جميع وسائط الدالة.

/**
 * @brief  يجمع عددين من نوع double.
 * @param  self (غير مستخدم هنا لوحدة C بسيطة).
 * @param  args الكائن tuple الذي يحتوي على الوسيطين (a, b).
 * @return كائن Python float يمثل نتيجة الجمع.
 */
static PyObject* calco_add(PyObject* self, PyObject* args) {
    double a, b;
    // PyArg_ParseTuple يقوم بتحويل وسائط بايثون إلى أنواع C.
    // "dd" تعني توقع وسيطين من نوع double.
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL; // إرجاع NULL إذا فشل التحويل (سيتم رفع استثناء بايثون).
    }
    return Py_BuildValue("d", a + b); // بناء كائن Python float من double في C.
}

/**
 * @brief  يطرح عددين من نوع double.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الوسيطين (a, b).
 * @return كائن Python float يمثل نتيجة الطرح.
 */
static PyObject* calco_subtract(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a - b);
}

/**
 * @brief  يضرب عددين من نوع double.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الوسيطين (a, b).
 * @return كائن Python float يمثل نتيجة الضرب.
 */
static PyObject* calco_multiply(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("d", a * b);
}

/**
 * @brief  يقسم عددين من نوع double.
 * يتعامل مع حالة القسمة على صفر لإرجاع NaN أو Inf.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الوسيطين (a, b).
 * @return كائن Python float يمثل نتيجة القسمة.
 */
static PyObject* calco_divide(PyObject* self, PyObject* args) {
    double a, b;
    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    if (b == 0.0) {
        if (a == 0.0) {
            return Py_BuildValue("d", NAN); // 0/0 -> NaN
        }
        return Py_BuildValue("d", (a > 0.0) ? INFINITY : -INFINITY); // x/0 -> Inf or -Inf
    }
    return Py_BuildValue("d", a / b);
}

/**
 * @brief  يرفع عددًا إلى قوة معينة.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الأساس والأس.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_power(PyObject* self, PyObject* args) {
    double base, exponent;
    if (!PyArg_ParseTuple(args, "dd", &base, &exponent)) {
        return NULL;
    }
    return Py_BuildValue("d", pow(base, exponent));
}

/**
 * @brief  يحسب الجذر التربيعي لعدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل نتيجة العملية أو NaN إذا كان العدد سالبًا.
 */
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

/**
 * @brief  يحسب الجذر التكعيبي لعدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_cube_root(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", cbrt(x));
}

/**
 * @brief  يحسب القيمة المطلقة لعدد فاصلة عائمة.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل القيمة المطلقة.
 */
static PyObject* calco_absolute_value(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", fabs(x));
}

/**
 * @brief  يحسب الجزء العائم المتبقي من القسمة (x - n*y).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على البسط والمقام.
 * @return كائن Python float يمثل باقي القسمة.
 */
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

/**
 * @brief  يحسب طول الوتر (hypotenuse).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على طولي الضلعين.
 * @return كائن Python float يمثل طول الوتر.
 */
static PyObject* calco_hypotenuse(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", hypot(x, y));
}

/**
 * @brief  يحسب الفرق الموجب بين عددين.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العددين.
 * @return كائن Python float يمثل الفرق الموجب.
 */
static PyObject* calco_positive_difference(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", fdim(x, y));
}

/**
 * @brief  يعيد قيمة العدد مع إشارة عدد آخر.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة والحجم.
 * @return كائن Python float يمثل العدد الجديد.
 */
static PyObject* calco_copy_sign_double(PyObject* self, PyObject* args) {
    double magnitude, sign_source;
    if (!PyArg_ParseTuple(args, "dd", &magnitude, &sign_source)) {
        return NULL;
    }
    return Py_BuildValue("d", copysign(magnitude, sign_source));
}

// -----------------------------------------------------------------------------
// II. وظائف التقريب والتصحيح - Rounding and Truncation Functions
// -----------------------------------------------------------------------------

/**
 * @brief  يعيد أكبر عدد صحيح لا يتجاوز x.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل القيمة المقربة.
 */
static PyObject* calco_floor_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", floor(x));
}

/**
 * @brief  يعيد أصغر عدد صحيح لا يقل عن x.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل القيمة المقربة.
 */
static PyObject* calco_ceil_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", ceil(x));
}

/**
 * @brief  يقرب العدد x إلى أقرب عدد صحيح، نصف النقاط تقرب بعيدًا عن الصفر.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل القيمة المقربة.
 */
static PyObject* calco_round_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", round(x));
}

/**
 * @brief  يقرب العدد x إلى أقرب عدد صحيح، نصف النقاط تقرب إلى العدد الزوجي الأقرب.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل القيمة المقربة.
 */
static PyObject* calco_nearbyint_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", nearbyint(x));
}

/**
 * @brief  يحصل على الجزء الصحيح من عدد فاصلة عائمة (تقريب نحو الصفر).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل الجزء الصحيح.
 */
static PyObject* calco_truncate_val(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", trunc(x));
}

// -----------------------------------------------------------------------------
// III. عمليات لوغاريتمية - Logarithmic Operations
// -----------------------------------------------------------------------------

/**
 * @brief  يحسب اللوغاريتم الطبيعي (الأساس e) لعدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل نتيجة العملية.
 */
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

/**
 * @brief  يحسب لوغاريتم عدد بالأساس 10.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل نتيجة العملية.
 */
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

/**
 * @brief  يحسب لوغاريتم عدد بالأساس 2.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python float يمثل نتيجة العملية.
 */
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

/**
 * @brief  يحسب لوغاريتم عدد بأي أساس محدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد والأساس.
 * @return كائن Python float يمثل نتيجة العملية.
 */
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

// -----------------------------------------------------------------------------
// IV. عمليات أسية - Exponential Operations
// -----------------------------------------------------------------------------

/**
 * @brief  يحسب الدالة الأسية (e مرفوعة لقوة x).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الأس.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_exponential(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", exp(x));
}

/**
 * @brief  يحسب 2 مرفوعة لقوة x.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الأس.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_exponential_base2(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", exp2(x));
}

/**
 * @brief  يحسب (e^x - 1) بدقة عالية للأعداد الصغيرة x.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الأس.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_exponential_minus_1(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", expm1(x));
}

// -----------------------------------------------------------------------------
// V. عمليات مثلثية (تتطلب الزوايا بالراديان) - Trigonometric Operations (Radians)
// -----------------------------------------------------------------------------

/**
 * @brief  يحسب جيب (sine) الزاوية.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الزاوية بالراديان.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_sine(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    return Py_BuildValue("d", sin(angle_rad));
}

/**
 * @brief  يحسب جيب التمام (cosine) الزاوية.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الزاوية بالراديان.
 * @return كائن Python float يمثل نتيجة العملية.
 */
static PyObject* calco_cosine(PyObject* self, PyObject* args) {
    double angle_rad;
    if (!PyArg_ParseTuple(args, "d", &angle_rad)) {
        return NULL;
    }
    return Py_BuildValue("d", cos(angle_rad));
}

/**
 * @brief  يحسب ظل (tangent) الزاوية.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الزاوية بالراديان.
 * @return كائن Python float يمثل نتيجة العملية.
 */
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

// -----------------------------------------------------------------------------
// VI. عمليات مثلثية عكسية (تعود بالزوايا بالراديان) - Inverse Trigonometric Operations (Returns Radians)
// -----------------------------------------------------------------------------

/**
 * @brief  يحسب القوس الجيبي (arcsine) لعدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل الزاوية بالراديان.
 */
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

/**
 * @brief  يحسب القوس جيب التمام (arccosine) لعدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل الزاوية بالراديان.
 */
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

/**
 * @brief  يحسب القوس الظلي (arctangent) لعدد.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل الزاوية بالراديان.
 */
static PyObject* calco_arctangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", atan(x));
}

/**
 * @brief  يحسب القوس الظلي (arctangent) لزوج من الإحداثيات (y, x).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الإحداثي y و x.
 * @return كائن Python float يمثل الزاوية بالراديان.
 */
static PyObject* calco_arctangent2(PyObject* self, PyObject* args) {
    double y, x;
    if (!PyArg_ParseTuple(args, "dd", &y, &x)) {
        return NULL;
    }
    return Py_BuildValue("d", atan2(y, x));
}

// -----------------------------------------------------------------------------
// VII. العمليات الزائدية (Hyperbolic Functions)
// -----------------------------------------------------------------------------

/**
 * @brief  يحسب جيب الزاوية الزائدي (hyperbolic sine).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_hyperbolic_sine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", sinh(x));
}

/**
 * @brief  يحسب جيب التمام الزائدي (hyperbolic cosine).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_hyperbolic_cosine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", cosh(x));
}

/**
 * @brief  يحسب ظل الزاوية الزائدي (hyperbolic tangent).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_hyperbolic_tangent(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", tanh(x));
}

/**
 * @brief  يحسب القوس الجيبي الزائدي العكسي (inverse hyperbolic sine).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_inverse_hyperbolic_sine(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", asinh(x));
}

/**
 * @brief  يحسب القوس جيب التمام الزائدي العكسي (inverse hyperbolic cosine).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
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

/**
 * @brief  يحسب القوس الظلي الزائدي العكسي (inverse hyperbolic tangent).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
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

// -----------------------------------------------------------------------------
// VIII. وظائف خاصة/متقدمة - Special/Advanced Functions
// -----------------------------------------------------------------------------

/**
 * @brief  يحسب دالة غاما (Gamma function).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_gamma_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", tgamma(x));
}

/**
 * @brief  يحسب اللوغاريتم الطبيعي للقيمة المطلقة لدالة غاما.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_log_gamma_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", lgamma(x));
}

/**
 * @brief  يحسب دالة الخطأ (Error function).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_error_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", erf(x));
}

/**
 * @brief  يحسب دالة الخطأ المكملة.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على القيمة.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_complementary_error_function(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("d", erfc(x));
}

/**
 * @brief  يحسب أقرب عدد فاصلة عائمة للقيمة x في اتجاه y.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على x و y.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_next_after_double(PyObject* self, PyObject* args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "dd", &x, &y)) {
        return NULL;
    }
    return Py_BuildValue("d", nextafter(x, y));
}

/**
 * @brief  يحسب ضربًا مدمجًا مع إضافة: (a * b) + c بدقة عالية.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على a و b و c.
 * @return كائن Python float يمثل النتيجة.
 */
static PyObject* calco_fused_multiply_add(PyObject* self, PyObject* args) {
    double a, b, c;
    if (!PyArg_ParseTuple(args, "ddd", &a, &b, &c)) {
        return NULL;
    }
    return Py_BuildValue("d", fma(a, b, c));
}

// -----------------------------------------------------------------------------
// IX. وظائف مساعدة وتحويلات - Utility Functions and Conversions
// -----------------------------------------------------------------------------

/**
 * @brief  يحول الزاوية من درجات إلى راديان.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الزاوية بالدرجات.
 * @return كائن Python float يمثل الزاوية بالراديان.
 */
static PyObject* calco_degrees_to_radians(PyObject* self, PyObject* args) {
    double degrees;
    if (!PyArg_ParseTuple(args, "d", &degrees)) {
        return NULL;
    }
    return Py_BuildValue("d", degrees * (M_PI / 180.0));
}

/**
 * @brief  يحول الزاوية من راديان إلى درجات.
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على الزاوية بالراديان.
 * @return كائن Python float يمثل الزاوية بالدرجات.
 */
static PyObject* calco_radians_to_degrees(PyObject* self, PyObject* args) {
    double radians;
    if (!PyArg_ParseTuple(args, "d", &radians)) {
        return NULL;
    }
    return Py_BuildValue("d", radians * (180.0 / M_PI));
}

/**
 * @brief  يعيد قيمة الثابت الرياضي Pi (ط).
 * @param  self (غير مستخدم).
 * @param  args (لا يوجد وسائط).
 * @return كائن Python float يمثل قيمة Pi.
 */
static PyObject* calco_get_pi(PyObject* self, PyObject* args) {
    // التأكد من عدم وجود وسائط
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return Py_BuildValue("d", M_PI);
}

/**
 * @brief  يعيد قيمة الثابت الرياضي E (رقم أويلر).
 * @param  self (غير مستخدم).
 * @param  args (لا يوجد وسائط).
 * @return كائن Python float يمثل قيمة E.
 */
static PyObject* calco_get_e(PyObject* self, PyObject* args) {
    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }
    return Py_BuildValue("d", M_E);
}

/**
 * @brief  للتحقق مما إذا كان العدد هو NaN (ليس رقمًا).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python bool يمثل النتيجة.
 */
static PyObject* calco_is_nan(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("b", (int)isnan(x)); // "b" لـ Py_BuildValue يبني كائن bool
}

/**
 * @brief  للتحقق مما إذا كان العدد هو Inf (لانهاية).
 * @param  self (غير مستخدم).
 * @param  args الكائن tuple الذي يحتوي على العدد.
 * @return كائن Python bool يمثل النتيجة.
 */
static PyObject* calco_is_infinity(PyObject* self, PyObject* args) {
    double x;
    if (!PyArg_ParseTuple(args, "d", &x)) {
        return NULL;
    }
    return Py_BuildValue("b", (int)isinf(x));
}


// -----------------------------------------------------------------------------
// تعريف توابع الوحدة (Module Methods Definition)
// -----------------------------------------------------------------------------
// هذا الجدول يسرد جميع الدوال التي ستكون متاحة من وحدة بايثون.
// كل إدخال يتكون من:
// - اسم الدالة في بايثون (string)
// - مؤشر لدالة C (static PyObject* function(PyObject* self, PyObject* args))
// - METH_VARARGS: يعني أن الدالة تأخذ tuple من الوسائط.
// - docstring (string): وصف للدالة يظهر في مساعدة بايثون (help(calco.function_name)).
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
    {NULL, NULL, 0, NULL} // Sentinel - يجب أن تكون هذه هي الأخيرة في القائمة
};

// -----------------------------------------------------------------------------
// تعريف هيكل الوحدة (Module Definition Structure)
// -----------------------------------------------------------------------------
// هذا الهيكل يصف وحدة بايثون.
static struct PyModuleDef calcomodule = {
    PyModuleDef_HEAD_INIT, // ماكرو يقوم بتهيئة الهيكل
    "calco",               // اسم الوحدة (كما سيتم استيراده في بايثون: import calco)
    "A comprehensive and fast C library for mathematical operations.", // Docstring للوحدة
    -1,                    // حجم حالة الوحدة (أو -1 إذا كانت الحالة لكل مترجم)
    CalcoMethods           // جدول توابع الوحدة
};

// -----------------------------------------------------------------------------
// دالة تهيئة الوحدة (Module Initialization Function)
// -----------------------------------------------------------------------------
// هذه هي الدالة التي تستدعيها بايثون عند استيراد الوحدة.
// يجب أن يكون اسمها PyInit_<module_name>، حيث <module_name> هو اسم الوحدة الذي تم تعريفه في PyModuleDef.
PyMODINIT_FUNC PyInit_calco(void) {
    return PyModule_Create(&calcomodule);
}
