def aoc23_01_02(raw):
    lines = raw.split("\n")
    total = 0
    for line in lines:
        first = -1
        last = -1
        i = 0
        while i < len(line):
            if line[i].isdigit():
                if first == -1:
                    first = int(line[i])
                last = int(line[i])
            else:
                digit = get_digit(line[(i - 4):(i+1)])
                if digit != -1:
                    if first == -1:
                        first = digit
                    last = digit
            i += 1
        number = int(str(first) + str(last))
        total += number
        print(f"{line} -> {first} / {last} -> {number} = {total}")
    return total


def get_digit(raw):
    if "zero" in raw:
        return 0
    if "one" in raw:
        return 1
    if "two" in raw:
        return 2
    if "three" in raw:
        return 3
    if "four" in raw:
        return 4
    if "five" in raw:
        return 5
    if "six" in raw:
        return 6
    if "seven" in raw:
        return 7
    if "eight" in raw:
        return 8
    if "nine" in raw:
        return 9
    return -1


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    f = open("../Day01/aoc_01_input.txt", "r")
    print(aoc23_01_02(f.read()))
