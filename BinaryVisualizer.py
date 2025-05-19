import tkinter as tk

def is_binary(char):
    return char in ('0', '1')

def validate_input(new_value):
    return all(is_binary(c) for c in new_value)

def twos_complement_to_int(b):
    # Interpret b (string) as a signed two's complement integer
    if not b:
        return 0
    n = len(b)
    value = int(b, 2)
    if b[0] == '1':  # negative number
        value -= (1 << n)
    return value

def int_to_twos_complement(value, bits):
    # Convert int to two's complement binary string with given bits
    if value < 0:
        value = (1 << bits) + value
    format_str = '{:0' + str(bits) + 'b}'
    return format_str.format(value & ((1 << bits) - 1))

def update_output(*args):
    b1 = entry1.get()
    b2 = entry2.get()

    try:
        d1 = twos_complement_to_int(b1)
        d2 = twos_complement_to_int(b2)

        label_decimal1.config(text=f"= {d1}")
        label_decimal2.config(text=f"= {d2}")

        total_dec = d1 + d2
        # Determine bit length for sum display: max input length + 1
        max_bits = max(len(b1), len(b2), 1) + 1
        total_bin = int_to_twos_complement(total_dec, max_bits)

        label_result.config(text=f"{b1 or '0'} + {b2 or '0'} = {total_bin} (binary), {total_dec} (decimal)")

    except ValueError:
        label_result.config(text="Invalid binary input")

root = tk.Tk()
root.title("Two's Complement Binary Adder")

vcmd = (root.register(validate_input), '%P')

# Entry 1
entry1 = tk.Entry(root, validate="key", validatecommand=vcmd, width=20)
entry1.grid(row=0, column=0, padx=5, pady=5)
entry1.bind("<KeyRelease>", update_output)

label_decimal1 = tk.Label(root, text="= 0")
label_decimal1.grid(row=0, column=1)

# Entry 2
entry2 = tk.Entry(root, validate="key", validatecommand=vcmd, width=20)
entry2.grid(row=1, column=0, padx=5, pady=5)
entry2.bind("<KeyRelease>", update_output)

label_decimal2 = tk.Label(root, text="= 0")
label_decimal2.grid(row=1, column=1)

# Result label
label_result = tk.Label(root, text="0 + 0 = 0 (binary), 0 (decimal)", font=("Helvetica", 12))
label_result.grid(row=2, column=0, columnspan=2, pady=10)

root.mainloop()
