def generate_type_I(size):
    return [[1] * size for _ in range(size)]

def generate_type_II(size):
    return [[1 if i % 2 == 0 else 0 for _ in range(size)] for i in range(size)]

def generate_type_III(size):
    return [[1 if j % 2 == 0 else 0 for j in range(size)] for _ in range(size)]

sizes = [1, 2, 4, 8, 16, 32, 64, 128, 256]
templates = {}

for size in sizes:
    templates[f"t{size}_I"] = generate_type_I(size)
    templates[f"t{size}_II"] = generate_type_II(size)
    templates[f"t{size}_III"] = generate_type_III(size)
