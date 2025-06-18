import customtkinter
import calco
import cmath

# Configure customtkinter appearance and theme
customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("blue")

class EquationSolverCalculator(customtkinter.CTk):
    """
    A GUI application for solving first and second-degree equations
    using the calco.pyd mathematical library.
    """
    def __init__(self):
        super().__init__()

        self.title("Equation Solver Calculator")
        self.geometry("600x700") # Increased size to accommodate more elements

        # Configure grid layout for the main window
        self.grid_rowconfigure((0, 1, 2, 3, 4, 5, 6, 7), weight=1)
        self.grid_rowconfigure((0, 1, 2, 3, 4, 5, 6, 7), weight=1)
        self.grid_columnconfigure(0, weight=1)

        # --- Title Label ---
        self.title_label = customtkinter.CTkLabel(self, text="Equation Solver",
                                                  font=("Inter", 30, "bold"))
        self.title_label.grid(row=0, column=0, pady=20, sticky="ew")

        # --- Linear Equation Section (ax + b = 0) ---
        self.linear_frame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.linear_frame.grid(row=1, column=0, padx=20, pady=10, sticky="nsew")
        self.linear_frame.grid_columnconfigure((0, 1), weight=1)

        customtkinter.CTkLabel(self.linear_frame, text="Linear Equation: ax + b = 0",
                               font=("Inter", 20, "bold")).grid(row=0, column=0, columnspan=2, pady=5)

        customtkinter.CTkLabel(self.linear_frame, text="a:", font=("Inter", 16)).grid(row=1, column=0, sticky="e", padx=5)
        self.linear_a_entry = customtkinter.CTkEntry(self.linear_frame, width=150, font=("Inter", 16))
        self.linear_a_entry.grid(row=1, column=1, sticky="w", padx=5)
        self.linear_a_entry.insert(0, "1") # Default value

        customtkinter.CTkLabel(self.linear_frame, text="b:", font=("Inter", 16)).grid(row=2, column=0, sticky="e", padx=5)
        self.linear_b_entry = customtkinter.CTkEntry(self.linear_frame, width=150, font=("Inter", 16))
        self.linear_b_entry.grid(row=2, column=1, sticky="w", padx=5)
        self.linear_b_entry.insert(0, "0") # Default value

        self.solve_linear_button = customtkinter.CTkButton(self.linear_frame, text="Solve Linear",
                                                           command=self.solve_linear_equation,
                                                           font=("Inter", 18, "bold"),
                                                           fg_color="green", hover_color="#00aa00")
        self.solve_linear_button.grid(row=3, column=0, columnspan=2, pady=10)

        self.linear_result_label = customtkinter.CTkLabel(self.linear_frame, text="Solution: ",
                                                          font=("Inter", 16), wraplength=550)
        self.linear_result_label.grid(row=4, column=0, columnspan=2, pady=5, sticky="ew")

        # --- Separator ---
        customtkinter.CTkFrame(self, height=2, fg_color="gray").grid(row=2, column=0, sticky="ew", padx=20, pady=15)


        # --- Quadratic Equation Section (ax^2 + bx + c = 0) ---
        self.quadratic_frame = customtkinter.CTkFrame(self, fg_color="transparent")
        self.quadratic_frame.grid(row=3, column=0, padx=20, pady=10, sticky="nsew")
        self.quadratic_frame.grid_columnconfigure((0, 1), weight=1)

        customtkinter.CTkLabel(self.quadratic_frame, text="Quadratic Equation: ax² + bx + c = 0",
                               font=("Inter", 20, "bold")).grid(row=0, column=0, columnspan=2, pady=5)

        customtkinter.CTkLabel(self.quadratic_frame, text="a:", font=("Inter", 16)).grid(row=1, column=0, sticky="e", padx=5)
        self.quadratic_a_entry = customtkinter.CTkEntry(self.quadratic_frame, width=150, font=("Inter", 16))
        self.quadratic_a_entry.grid(row=1, column=1, sticky="w", padx=5)
        self.quadratic_a_entry.insert(0, "1") # Default value

        customtkinter.CTkLabel(self.quadratic_frame, text="b:", font=("Inter", 16)).grid(row=2, column=0, sticky="e", padx=5)
        self.quadratic_b_entry = customtkinter.CTkEntry(self.quadratic_frame, width=150, font=("Inter", 16))
        self.quadratic_b_entry.grid(row=2, column=1, sticky="w", padx=5)
        self.quadratic_b_entry.insert(0, "0") # Default value

        customtkinter.CTkLabel(self.quadratic_frame, text="c:", font=("Inter", 16)).grid(row=3, column=0, sticky="e", padx=5)
        self.quadratic_c_entry = customtkinter.CTkEntry(self.quadratic_frame, width=150, font=("Inter", 16))
        self.quadratic_c_entry.grid(row=3, column=1, sticky="w", padx=5)
        self.quadratic_c_entry.insert(0, "0") # Default value

        self.solve_quadratic_button = customtkinter.CTkButton(self.quadratic_frame, text="Solve Quadratic",
                                                              command=self.solve_quadratic_equation,
                                                              font=("Inter", 18, "bold"),
                                                              fg_color="green", hover_color="#00aa00")
        self.solve_quadratic_button.grid(row=4, column=0, columnspan=2, pady=10)

        self.quadratic_result_label = customtkinter.CTkLabel(self.quadratic_frame, text="Solution: ",
                                                             font=("Inter", 16), wraplength=550)
        self.quadratic_result_label.grid(row=5, column=0, columnspan=2, pady=5, sticky="ew")

        # --- Error Message Label ---
        self.error_label = customtkinter.CTkLabel(self, text="",
                                                  font=("Inter", 16, "bold"), text_color="red", wraplength=550)
        self.error_label.grid(row=6, column=0, pady=10, sticky="ew")


    def _get_float_input(self, entry_widget):
        """Helper to get float from entry and handle ValueError."""
        try:
            value = float(entry_widget.get())
            self.error_label.configure(text="") # Clear previous errors
            return value
        except ValueError:
            self.error_label.configure(text="Error: Please enter valid numbers for coefficients.")
            return None

    def solve_linear_equation(self):
        """
        Solves a linear equation of the form ax + b = 0.
        """
        a = self._get_float_input(self.linear_a_entry)
        b = self._get_float_input(self.linear_b_entry)

        if a is None or b is None:
            self.linear_result_label.configure(text="Solution: Invalid input.")
            return

        if calco.absolute_value(a) < 1e-9: # Check if 'a' is close to zero
            if calco.absolute_value(b) < 1e-9: # 0x + 0 = 0
                self.linear_result_label.configure(text="Solution: Infinite solutions (0 = 0).")
            else: # 0x + b = 0 where b is not 0
                self.linear_result_label.configure(text="Solution: No solution (e.g., 5 = 0).")
        else:
            # x = -b / a
            # Use calco functions for arithmetic
            neg_b = calco.multiply(-1.0, b)
            x = calco.divide(neg_b, a)
            self.linear_result_label.configure(text=f"Solution: x = {x:.6f}") # Limit decimals for display

    def solve_quadratic_equation(self):
        """
        Solves a quadratic equation of the form ax^2 + bx + c = 0.
        """
        a = self._get_float_input(self.quadratic_a_entry)
        b = self._get_float_input(self.quadratic_b_entry)
        c = self._get_float_input(self.quadratic_c_entry)

        if a is None or b is None or c is None:
            self.quadratic_result_label.configure(text="Solution: Invalid input.")
            return

        # Handle the case where 'a' is zero (it becomes a linear equation)
        if calco.absolute_value(a) < 1e-9:
            self.error_label.configure(text="Warning: 'a' is effectively zero. Solving as a linear equation.")
            # Set the linear equation entries and call its solver
            self.linear_a_entry.delete(0, customtkinter.END)
            self.linear_a_entry.insert(0, str(b))
            self.linear_b_entry.delete(0, customtkinter.END)
            self.linear_b_entry.insert(0, str(c))
            self.solve_linear_equation()
            self.quadratic_result_label.configure(text="Solution: See Linear Equation section.")
            return

        # Calculate discriminant: D = b^2 - 4ac
        # b_squared = b * b
        b_squared = calco.power(b, 2.0)
        # four_ac = 4 * a * c
        four_ac = calco.multiply(4.0, calco.multiply(a, c))
        # discriminant = b_squared - four_ac
        discriminant = calco.subtract(b_squared, four_ac)

        if discriminant >= 0:
            # Real roots
            # sqrt_discriminant = sqrt(discriminant)
            sqrt_discriminant = calco.square_root(discriminant)

            # x1 = (-b + sqrt_discriminant) / (2a)
            # x2 = (-b - sqrt_discriminant) / (2a)
            neg_b = calco.multiply(-1.0, b)
            two_a = calco.multiply(2.0, a)

            x1_numerator = calco.add(neg_b, sqrt_discriminant)
            x1 = calco.divide(x1_numerator, two_a)

            x2_numerator = calco.subtract(neg_b, sqrt_discriminant)
            x2 = calco.divide(x2_numerator, two_a)

            if calco.absolute_value(discriminant) < 1e-9: # D is close to zero, one real root
                self.quadratic_result_label.configure(text=f"Solution: x = {x1:.6f} (one real root)")
            else: # Two distinct real roots
                self.quadratic_result_label.configure(text=f"Solution: x₁ = {x1:.6f}, x₂ = {x2:.6f}")
        else:
            # Complex roots (D < 0)
            # Use cmath for complex square root, as calco.square_root returns NaN for negative numbers
            # sqrt_discriminant_complex = cmath.sqrt(discriminant)
            sqrt_discriminant_complex = cmath.sqrt(discriminant)

            # x1 = (-b + sqrt_discriminant_complex) / (2a)
            # x2 = (-b - sqrt_discriminant_complex) / (2a)
            neg_b = calco.multiply(-1.0, b) # Can still use calco for real number ops
            two_a = calco.multiply(2.0, a)

            x1 = (neg_b + sqrt_discriminant_complex) / two_a
            x2 = (neg_b - sqrt_discriminant_complex) / two_a

            self.quadratic_result_label.configure(text=f"Solution: x₁ = {x1:.6f}, x₂ = {x2:.6f} (complex roots)")

# Entry point for the application
if __name__ == "__main__":
    app = EquationSolverCalculator()
    app.mainloop()
