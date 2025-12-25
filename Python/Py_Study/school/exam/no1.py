t = 1.0
days = 365

for i in range(1, days + 1):
    if i % 7 == 6 or i % 7 == 0:
        t = t * 0.99
    else:
        t = t * 1.01

print(f"{t:.2f}")