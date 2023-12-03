def find_number(line, word_map, search_from_start):
    if not line:
        return -1

    index = 0 if search_from_start else len(line) - 1
    increment = 1 if search_from_start else -1

    while (search_from_start and index < len(line)) or (not search_from_start and index >= 0):
        if line[index].isdigit():
            return int(line[index])

        current_word = ""
        for i in range(index, len(line) if search_from_start else -1, increment):
            current_word = (line[index:i + 1] if search_from_start else line[i:index + 1]).lower()

            if current_word in word_map:
                return int(word_map[current_word])

            if not line[i].isalpha():
                break

        index += increment

    return -1

def process_line(line):
    word_map = {
        "one": "1", "two": "2", "three": "3", "four": "4",
        "five": "5", "six": "6", "seven": "7", "eight": "8", "nine": "9"
    }

    first_number = find_number(line, word_map, True)
    last_number = find_number(line, word_map, False)

    if first_number != -1 and last_number != -1:
        return f"{first_number}{last_number}"
    return ""

def main():
    with open("inputDay1.txt", "r") as file:
        lines = file.readlines()

    sum = 0
    for line in lines:
        processed_line = process_line(line.strip())
        if processed_line:
            sum += int(processed_line)

    print("Total sum:", sum)

if __name__ == "__main__":
    main()
