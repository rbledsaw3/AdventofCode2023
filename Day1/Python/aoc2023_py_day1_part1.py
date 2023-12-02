def process_line(line):
    first_digit = -1
    last_digit = -1

    for char in line:
        if char.isdigit():
            digit = int(char)
            if first_digit == -1:
                first_digit = digit
            last_digit = digit

    if first_digit != -1 and last_digit == -1:
        last_digit = first_digit
    return first_digit * 10 + last_digit

def process_file(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    return sum(process_line(line) for line in lines)

total_sum = process_file('input.txt')
print(f"Total sum: {total_sum}")
