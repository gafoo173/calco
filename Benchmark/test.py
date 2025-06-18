import time
import math
import numpy as np

# -----------------------------
# Module Imports with Fallbacks
# -----------------------------

try:
    import calco
except ImportError:
    calco = None

try:
    import mpmath
    mpmath.mp.dps = 30
except ImportError:
    mpmath = None

try:
    from numba import njit
except ImportError:
    njit = lambda x: x  # Fallback if numba is not available

# -----------------------------
# Configuration
# -----------------------------

REPEAT = 1_000_000
x = 123.456
y = 654.321

# -----------------------------
# Numba-optimized Functions
# -----------------------------

@njit
def numba_add(a, b): return a + b

@njit
def numba_subtract(a, b): return a - b

@njit
def numba_multiply(a, b): return a * b

@njit
def numba_divide(a, b): return a / b

@njit
def numba_sqrt(a): return math.sqrt(a)

@njit
def numba_log(a): return math.log(a)

@njit
def numba_sin(a): return math.sin(a)

@njit
def numba_exp(a): return math.exp(a)

@njit
def numba_complex(a):
    return math.sin(math.log(a*a + math.sqrt(a))) + math.exp(a)/a + math.gamma(math.sqrt(a))

# -----------------------------
# Benchmarking Core
# -----------------------------

def benchmark(func, expected, *args, repeat=REPEAT):
    """Run timing benchmark for a given function."""
    start = time.perf_counter()
    for _ in range(repeat):
        result = func(*args)
        if abs(result - expected) > 1e-8:
            raise ValueError(f"Mismatch! Expected {expected}, got {result}")
    return time.perf_counter() - start

# -----------------------------
# Test Definitions
# -----------------------------

class TestDefinitions:
    """Container for all test cases."""
    
    @staticmethod
    def get_basic_tests():
        """Basic arithmetic operations."""
        return {
            "Addition": [
                ("math", lambda x, y: x + y, x + y),
                ("numpy", lambda x, y: np.add(x, y), x + y),
                ("calco", calco.add if calco else None, x + y),
                ("numba", numba_add, x + y)
            ],
            "Subtraction": [
                ("math", lambda x, y: x - y, x - y),
                ("numpy", lambda x, y: np.subtract(x, y), x - y),
                ("calco", calco.subtract if calco else None, x - y),
                ("numba", numba_subtract, x - y)
            ],
            "Multiplication": [
                ("math", lambda x, y: x * y, x * y),
                ("numpy", lambda x, y: np.multiply(x, y), x * y),
                ("calco", calco.multiply if calco else None, x * y),
                ("numba", numba_multiply, x * y)
            ],
            "Division": [
                ("math", lambda x, y: x / y, x / y),
                ("numpy", lambda x, y: np.divide(x, y), x / y),
                ("calco", calco.divide if calco else None, x / y),
                ("numba", numba_divide, x / y)
            ]
        }

    @staticmethod
    def get_intermediate_tests():
        """Intermediate mathematical functions."""
        return {
            "Square root": [
                ("math", math.sqrt, math.sqrt(x)),
                ("numpy", np.sqrt, math.sqrt(x)),
                ("calco", calco.square_root if calco else None, math.sqrt(x)),
                ("numba", numba_sqrt, math.sqrt(x))
            ],
            "Logarithm": [
                ("math", math.log, math.log(x)),
                ("numpy", np.log, math.log(x)),
                ("calco", calco.natural_log if calco else None, math.log(x)),
                ("numba", numba_log, math.log(x))
            ],
            "Sine": [
                ("math", math.sin, math.sin(x)),
                ("numpy", np.sin, math.sin(x)),
                ("calco", calco.sine if calco else None, math.sin(x)),
                ("numba", numba_sin, math.sin(x))
            ],
            "Exponential": [
                ("math", math.exp, math.exp(x)),
                ("numpy", np.exp, math.exp(x)),
                ("calco", calco.exponential if calco else None, math.exp(x)),
                ("numba", numba_exp, math.exp(x))
            ]
        }

    @staticmethod
    def get_complex_tests():
        """Complex mathematical expression."""
        expected = math.sin(math.log(x**2 + math.sqrt(x))) + math.exp(x)/x + math.gamma(math.sqrt(x))
        return {
            "Complex Expression": [
                ("math", lambda x: math.sin(math.log(x**2 + math.sqrt(x))) + math.exp(x)/x + math.gamma(math.sqrt(x)), expected),
                ("numpy", lambda x: np.sin(np.log(x**2 + np.sqrt(x))) + np.exp(x)/x + math.gamma(np.sqrt(x)), expected),
                ("calco", lambda x: calco.sine(calco.natural_log(x * x + calco.square_root(x))) + calco.exponential(x)/x + calco.gamma_function(calco.square_root(x)) if calco else None, expected),
                ("numba", numba_complex, expected),
                ("mpmath", lambda x: float(mpmath.sin(mpmath.log(x**2 + mpmath.sqrt(x))) + mpmath.exp(x)/x + mpmath.gamma(mpmath.sqrt(x))) if mpmath else None, expected)
            ]
        }

# -----------------------------
# Test Runner
# -----------------------------

class BenchmarkRunner:
    """Handles running and displaying benchmark results."""
    
    @staticmethod
    def run_tests(title, tests, binary=True):
        """Execute and display benchmark results."""
        print(f"\n🔹 {title}")
        print("-" * 50)
        print(f"{'Operation':<20}{'Library':<10}{'Time (s)':>10}")
        print("-" * 50)

        for operation, funcs in tests.items():
            for name, func, expected in funcs:
                if not func:
                    continue
                try:
                    t = benchmark(func, expected, x, y) if binary else benchmark(func, expected, x)
                    print(f"{operation:<20}{name:<10}{t:>10.4f}")
                except ValueError as ve:
                    print(f"{operation:<20}{name:<10}{'INVALID'}")
        print("-" * 50)

# -----------------------------
# Main Execution
# -----------------------------

if __name__ == '__main__':
    runner = BenchmarkRunner()
    tests = TestDefinitions()
    
    runner.run_tests("Level 1: Basic Arithmetic", tests.get_basic_tests())
    runner.run_tests("Level 2: Intermediate Functions", tests.get_intermediate_tests(), binary=False)
    runner.run_tests("Level 3: Complex Expression", tests.get_complex_tests(), binary=False)
