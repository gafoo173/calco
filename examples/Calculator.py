import customtkinter
import calco

# Configure customtkinter appearance and theme
customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("blue")

class CalcoCalculator(customtkinter.CTk):
    def __init__(self):
        super().__init__()

        self.title("Calco Scientific Calculator")
        self.geometry("480x750")
        
        # Create main container frame
        self.main_container = customtkinter.CTkFrame(self)
        self.main_container.pack(fill="both", expand=True)
        
        # Configure grid layout for the main container
        self.main_container.grid_rowconfigure(0, weight=1)
        self.main_container.grid_rowconfigure(1, weight=5)
        self.main_container.grid_columnconfigure(0, weight=1)

        # --- Display Entry ---
        self.display = customtkinter.CTkEntry(
            self.main_container,
            width=400,
            height=70,
            font=("Inter", 30, "bold"),
            justify="right",
            corner_radius=10,
            state="readonly"
        )
        self.display.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        self.display.insert(0, "0")

        # Calculator state variables
        self.display_text = "0"
        self.current_operator = None
        self.first_operand = None
        self.second_operand = None
        self.new_number = True
        self.is_radian_mode = True
        self.waiting_for_second_arg = False

        # --- Main Button Frame ---
        self.main_buttons_frame = customtkinter.CTkFrame(self.main_container, fg_color="transparent")
        self.main_buttons_frame.grid(row=1, column=0, sticky="nsew", padx=20, pady=10)
        self.main_buttons_frame.grid_columnconfigure((0, 1, 2, 3), weight=1)
        self.main_buttons_frame.grid_rowconfigure((0, 1, 2, 3, 4), weight=1)

        # --- Scientific Functions Frame ---
        self.scientific_frame = customtkinter.CTkFrame(self.main_container, fg_color="transparent")
        self.scientific_frame.grid_columnconfigure((0, 1, 2, 3, 4), weight=1)
        self.scientific_frame.grid_rowconfigure((0, 1, 2, 3, 4, 5, 6, 7, 8, 9), weight=1)

        self.create_buttons()
        self.current_mode = "basic"
        self.update_display()
        self.scientific_frame.grid_remove()  # Hide scientific frame initially

    def create_buttons(self):
        num_btn_color = "#555555"
        op_btn_color = "orange"
        util_btn_color = "#1e3f66"  # Changed from "dark-blue" to hex color
        clear_btn_color = "red"
        eq_btn_color = "green"
        sci_btn_color = "#3a3a3a"

        # --- Numeric Pad & Basic Operations Buttons ---
        buttons = [
            ('C', 0, 0, self.clear_display, clear_btn_color),
            ('DEL', 0, 1, self.delete_last_char, clear_btn_color),
            ('Sci', 0, 2, self.toggle_mode, util_btn_color),
            ('/', 0, 3, self.set_operator, op_btn_color),

            ('7', 1, 0, self.append_number, num_btn_color), ('8', 1, 1, self.append_number, num_btn_color), 
            ('9', 1, 2, self.append_number, num_btn_color), ('*', 1, 3, self.set_operator, op_btn_color),

            ('4', 2, 0, self.append_number, num_btn_color), ('5', 2, 1, self.append_number, num_btn_color),
            ('6', 2, 2, self.append_number, num_btn_color), ('-', 2, 3, self.set_operator, op_btn_color),

            ('1', 3, 0, self.append_number, num_btn_color), ('2', 3, 1, self.append_number, num_btn_color),
            ('3', 3, 2, self.append_number, num_btn_color), ('+', 3, 3, self.set_operator, op_btn_color),

            ('+/-', 4, 0, self.negate_number, util_btn_color), ('0', 4, 1, self.append_number, num_btn_color),
            ('.', 4, 2, self.append_decimal, util_btn_color), ('=', 4, 3, self.calculate_result, eq_btn_color),
        ]

        for (text, row, col, command_func, color) in buttons:
            btn = customtkinter.CTkButton(
                self.main_buttons_frame,
                text=text,
                font=("Inter", 25, "bold"),
                command=lambda t=text, cf=command_func: cf(t),
                fg_color=color,
                hover_color=self._get_hover_color(color),
                corner_radius=10
            )
            btn.grid(row=row, column=col, sticky="nsew", padx=5, pady=5)
            if text == 'Sci':
                self.btn_Sci = btn

        # --- Scientific Functions Buttons ---
        scientific_buttons_data = [
            ('sin', 0, 0, 'trig', sci_btn_color), ('cos', 0, 1, 'trig', sci_btn_color),
            ('tan', 0, 2, 'trig', sci_btn_color), ('asin', 0, 3, 'trig', sci_btn_color),
            ('acos', 0, 4, 'trig', sci_btn_color), ('atan', 1, 0, 'trig', sci_btn_color),
            ('atan2', 1, 1, 'trig_two_arg', sci_btn_color), ('sinh', 1, 2, 'hyper', sci_btn_color),
            ('cosh', 1, 3, 'hyper', sci_btn_color), ('tanh', 1, 4, 'hyper', sci_btn_color),
            ('asinh', 2, 0, 'hyper', sci_btn_color), ('acosh', 2, 1, 'hyper', sci_btn_color),
            ('atanh', 2, 2, 'hyper', sci_btn_color), ('PI', 2, 3, 'const', util_btn_color),
            ('E', 2, 4, 'const', util_btn_color), ('ln', 3, 0, 'log', sci_btn_color),
            ('log10', 3, 1, 'log', sci_btn_color), ('log2', 3, 2, 'log', sci_btn_color),
            ('log_base', 3, 3, 'log_two_arg', sci_btn_color), ('e^x', 3, 4, 'exp', sci_btn_color),
            ('2^x', 4, 0, 'exp', sci_btn_color), ('e^x-1', 4, 1, 'exp', sci_btn_color),
            ('sqrt', 4, 2, 'arith', sci_btn_color), ('cbrt', 4, 3, 'arith', sci_btn_color),
            ('x^y', 4, 4, 'arith_two_arg', sci_btn_color), ('fmod', 5, 0, 'arith_two_arg', sci_btn_color),
            ('hypot', 5, 1, 'arith_two_arg', sci_btn_color), ('fdim', 5, 2, 'arith_two_arg', sci_btn_color),
            ('copysign', 5, 3, 'arith_two_arg', sci_btn_color), ('fma', 5, 4, 'arith_three_arg', sci_btn_color),
            ('floor', 6, 0, 'round', sci_btn_color), ('ceil', 6, 1, 'round', sci_btn_color),
            ('round', 6, 2, 'round', sci_btn_color), ('nearbyint', 6, 3, 'round', sci_btn_color),
            ('trunc', 6, 4, 'round', sci_btn_color), ('gamma', 7, 0, 'special', sci_btn_color),
            ('lgamma', 7, 1, 'special', sci_btn_color), ('erf', 7, 2, 'special', sci_btn_color),
            ('erfc', 7, 3, 'special', sci_btn_color), ('next_after', 7, 4, 'special_two_arg', sci_btn_color),
            ('DegToRad', 8, 0, 'convert', util_btn_color), ('RadToDeg', 8, 1, 'convert', util_btn_color),
            ('is_nan', 8, 2, 'check', util_btn_color), ('is_inf', 8, 3, 'check', util_btn_color),
            ('Mode', 9, 4, 'mode_toggle', util_btn_color)
        ]

        for (text, row, col, func_type, color) in scientific_buttons_data:
            btn = customtkinter.CTkButton(
                self.scientific_frame,
                text=text,
                font=("Inter", 18, "bold"),
                command=lambda t=text, ft=func_type: self.do_function(t, ft) if ft != 'mode_toggle' else self.toggle_radian_mode(),
                fg_color=color,
                hover_color=self._get_hover_color(color),
                corner_radius=10
            )
            btn.grid(row=row, column=col, sticky="nsew", padx=3, pady=3)
            if text == 'Mode':
                self.btn_sci_Mode = btn

        self.update_radian_mode_button_text()

    def _get_hover_color(self, base_color):
        if base_color == "#555555": return "#6a6a6a"
        elif base_color == "orange": return "#e08000"
        elif base_color == "green": return "#00aa00"
        elif base_color == "red": return "#cc0000"
        elif base_color == "#1e3f66": return "#2a4f7a"  # Updated hover color for util buttons
        elif base_color == "#3a3a3a": return "#4a4a4a"
        return base_color

    def append_number(self, num):
        if self.display_text == "0" or self.new_number:
            self.display_text = num
            self.new_number = False
        else:
            self.display_text += num
        self.update_display()

    def append_decimal(self, text):
        if self.new_number:
            self.display_text = "0."
            self.new_number = False
        elif '.' not in self.display_text:
            self.display_text += "."
        self.update_display()

    def negate_number(self, text):
        try:
            current_val = float(self.display_text)
            self.display_text = self._format_result(-current_val)
            self.update_display()
        except ValueError:
            self.display_text = "Error"
            self.update_display()

    def clear_display(self, text=None):
        self.display_text = "0"
        self.current_operator = None
        self.first_operand = None
        self.second_operand = None
        self.new_number = True
        self.waiting_for_second_arg = False
        self.update_display()

    def delete_last_char(self, text=None):
        if self.display_text == "Error" or self.new_number:
            self.clear_display()
        else:
            self.display_text = self.display_text[:-1]
            if not self.display_text or self.display_text == '-':
                self.display_text = "0"
            self.update_display()

    def set_operator(self, operator):
        try:
            self.first_operand = float(self.display_text)
            self.current_operator = operator
            self.new_number = True
            self.waiting_for_second_arg = False
        except ValueError:
            self.display_text = "Error"
        self.update_display()

    def calculate_result(self, text=None):
        if self.current_operator is None:
            return

        try:
            self.second_operand = float(self.display_text)

            result = None
            if self.current_operator == '+':
                result = calco.add(self.first_operand, self.second_operand)
            elif self.current_operator == '-':
                result = calco.subtract(self.first_operand, self.second_operand)
            elif self.current_operator == '*':
                result = calco.multiply(self.first_operand, self.second_operand)
            elif self.current_operator == '/':
                result = calco.divide(self.first_operand, self.second_operand)
            elif self.current_operator == 'atan2':
                result = calco.arctangent2(self.first_operand, self.second_operand)
                if not self.is_radian_mode and result is not None and not (calco.is_nan(result) or calco.is_infinity(result)):
                    result = calco.radians_to_degrees(result)
            elif self.current_operator == 'log_base':
                result = calco.log_custom_base(self.first_operand, self.second_operand)
            elif self.current_operator == 'x^y':
                result = calco.power(self.first_operand, self.second_operand)
            elif self.current_operator == 'fmod':
                result = calco.float_modulo(self.first_operand, self.second_operand)
            elif self.current_operator == 'hypot':
                result = calco.hypotenuse(self.first_operand, self.second_operand)
            elif self.current_operator == 'fdim':
                result = calco.positive_difference(self.first_operand, self.second_operand)
            elif self.current_operator == 'copysign':
                result = calco.copy_sign_double(self.first_operand, self.second_operand)
            elif self.current_operator == 'next_after':
                result = calco.next_after_double(self.first_operand, self.second_operand)

            self.display_text = self._format_result(result)
            self.first_operand = result
            self.current_operator = None
            self.second_operand = None
            self.new_number = True
            self.waiting_for_second_arg = False

        except Exception as e:
            self.display_text = "Error"
            print(f"Calculation Error: {e}")
        self.update_display()

    def do_function(self, func_name, func_type):
        try:
            current_value = float(self.display_text)
            result = None

            self.current_operator = None
            self.first_operand = None
            self.second_operand = None
            self.new_number = True
            self.waiting_for_second_arg = False

            if func_type == 'trig':
                if not self.is_radian_mode:
                    current_value = calco.degrees_to_radians(current_value)

                if func_name == 'sin': result = calco.sine(current_value)
                elif func_name == 'cos': result = calco.cosine(current_value)
                elif func_name == 'tan': result = calco.tangent(current_value)
                elif func_name == 'asin': result = calco.arcsine(current_value)
                elif func_name == 'acos': result = calco.arccosine(current_value)
                elif func_name == 'atan': result = calco.arctangent(current_value)

                if not self.is_radian_mode and result is not None and not (calco.is_nan(result) or calco.is_infinity(result)):
                    result = calco.radians_to_degrees(result)

            elif func_type == 'trig_two_arg' and func_name == 'atan2':
                self.first_operand = current_value
                self.current_operator = 'atan2'
                self.waiting_for_second_arg = True
                self.new_number = True
                self.display_text = str(current_value)
                self.update_display()
                return

            elif func_type == 'hyper':
                if func_name == 'sinh': result = calco.hyperbolic_sine(current_value)
                elif func_name == 'cosh': result = calco.hyperbolic_cosine(current_value)
                elif func_name == 'tanh': result = calco.hyperbolic_tangent(current_value)
                elif func_name == 'asinh': result = calco.inverse_hyperbolic_sine(current_value)
                elif func_name == 'acosh': result = calco.inverse_hyperbolic_cosine(current_value)
                elif func_name == 'atanh': result = calco.inverse_hyperbolic_tangent(current_value)

            elif func_type == 'log':
                if func_name == 'ln': result = calco.natural_log(current_value)
                elif func_name == 'log10': result = calco.log_base10(current_value)
                elif func_name == 'log2': result = calco.log_base2(current_value)
                elif func_name == 'log_base':
                    self.first_operand = current_value
                    self.current_operator = 'log_base'
                    self.waiting_for_second_arg = True
                    self.new_number = True
                    self.display_text = str(current_value)
                    self.update_display()
                    return

            elif func_type == 'exp':
                if func_name == 'e^x': result = calco.exponential(current_value)
                elif func_name == '2^x': result = calco.exponential_base2(current_value)
                elif func_name == 'e^x-1': result = calco.exponential_minus_1(current_value)

            elif func_type == 'arith':
                if func_name == 'sqrt': result = calco.square_root(current_value)
                elif func_name == 'cbrt': result = calco.cube_root(current_value)
                elif func_name == 'x^y':
                    self.first_operand = current_value
                    self.current_operator = 'x^y'
                    self.waiting_for_second_arg = True
                    self.new_number = True
                    self.display_text = str(current_value)
                    self.update_display()
                    return

            elif func_type == 'arith_two_arg':
                self.first_operand = current_value
                self.current_operator = func_name
                self.waiting_for_second_arg = True
                self.new_number = True
                self.display_text = str(current_value)
                self.update_display()
                return

            elif func_type == 'arith_three_arg' and func_name == 'fma':
                a = current_value
                try:
                    b_str = customtkinter.CTkInputDialog(text=f"Enter b for fma({a}, b, c):", title="Input b").get_input()
                    if b_str is None:
                        self.clear_display()
                        return
                    b = float(b_str)

                    c_str = customtkinter.CTkInputDialog(text=f"Enter c for fma({a}, {b}, c):", title="Input c").get_input()
                    if c_str is None:
                        self.clear_display()
                        return
                    c = float(c_str)

                    result = calco.fused_multiply_add(a, b, c)
                except ValueError:
                    result = float('nan')
                except Exception as ex:
                    print(f"FMA input dialog error: {ex}")
                    result = float('nan')
                finally:
                    self.clear_display()
                    self.display_text = self._format_result(result)
                    self.update_display()
                    return

            elif func_type == 'round':
                if func_name == 'floor': result = calco.floor_val(current_value)
                elif func_name == 'ceil': result = calco.ceil_val(current_value)
                elif func_name == 'round': result = calco.round_val(current_value)
                elif func_name == 'nearbyint': result = calco.nearbyint_val(current_value)
                elif func_name == 'trunc': result = calco.truncate_val(current_value)

            elif func_type == 'special':
                if func_name == 'gamma': result = calco.gamma_function(current_value)
                elif func_name == 'lgamma': result = calco.log_gamma_function(current_value)
                elif func_name == 'erf': result = calco.error_function(current_value)
                elif func_name == 'erfc': result = calco.complementary_error_function(current_value)
                elif func_name == 'next_after':
                    self.first_operand = current_value
                    self.current_operator = 'next_after'
                    self.waiting_for_second_arg = True
                    self.new_number = True
                    self.display_text = str(current_value)
                    self.update_display()
                    return

            elif func_type == 'convert':
                if func_name == 'DegToRad': result = calco.degrees_to_radians(current_value)
                elif func_name == 'RadToDeg': result = calco.radians_to_degrees(current_value)

            elif func_type == 'const':
                self.new_number = True
                if func_name == 'PI': result = calco.get_pi()
                elif func_name == 'E': result = calco.get_e()

            elif func_type == 'check':
                if func_name == 'is_nan': result = "True" if calco.is_nan(current_value) else "False"
                elif func_name == 'is_inf': result = "True" if calco.is_infinity(current_value) else "False"

            self.display_text = self._format_result(result)
            self.update_display()
            self.new_number = True

        except ValueError:
            self.display_text = "Error"
            self.update_display()
        except Exception as e:
            self.display_text = "Error"
            print(f"Function Error ({func_name}): {e}")
            self.update_display()

    def _format_result(self, res):
        if res is None:
            return "Error"
        if isinstance(res, str):
            return res
        if calco.is_nan(res):
            return "NaN"
        if calco.is_infinity(res):
            return "Infinity" if res > 0 else "-Infinity"

        s_res = str(res)
        if '.' in s_res and 'e' not in s_res.lower():
            if len(s_res.split('.')[1]) > 10:
                return f"{res:.10f}".rstrip('0').rstrip('.')
        return s_res

    def update_display(self):
        self.display.configure(state="normal")
        self.display.delete(0, customtkinter.END)
        self.display.insert(0, self.display_text)
        self.display.configure(state="readonly")

    def toggle_mode(self, text=None):
        if self.current_mode == "basic":
            self.current_mode = "scientific"
            self.main_buttons_frame.grid_remove()
            self.scientific_frame.grid(row=1, column=0, sticky="nsew", padx=20, pady=10)
            self.btn_Sci.configure(text="Basic")
        else:
            self.current_mode = "basic"
            self.scientific_frame.grid_remove()
            self.main_buttons_frame.grid(row=1, column=0, sticky="nsew", padx=20, pady=10)
            self.btn_Sci.configure(text="Sci")
        self.update_radian_mode_button_text()

    def toggle_radian_mode(self):
        self.is_radian_mode = not self.is_radian_mode
        self.update_radian_mode_button_text()

    def update_radian_mode_button_text(self):
        if hasattr(self, 'btn_sci_Mode'):
            if self.is_radian_mode:
                self.btn_sci_Mode.configure(text="Rad Mode")
            else:
                self.btn_sci_Mode.configure(text="Deg Mode")

if __name__ == "__main__":
    app = CalcoCalculator()
    app.mainloop()
