cash = float(input("Change: "))

quarter = cash // 0.25
cash = cash % 0.25

ten = cash // 0.10
cash = cash % 0.10

five = cash // 0.05
cash = cash % 0.05

one = cash // 0.01

sum = quarter + ten + five + one
print(int(sum))
