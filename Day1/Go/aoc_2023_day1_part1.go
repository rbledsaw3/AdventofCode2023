package main

import (
    "bufio"
    "fmt"
    "os"
    "strconv"
    "unicode"
)

func main() {
    file, err := os.Open("input.txt")
    if err != nil {
        fmt.Println("Error reading file", err)
        return
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    sum := 0

    for scanner.Scan() {
        line := scanner.Text()
        firstDigit := -1
        lastDigit := -1

        for _, chr := range line {
            if unicode.IsDigit(chr) {
                digit, _ := strconv.Atoi(string(chr))
                if firstDigit == -1 {
                    firstDigit = digit
                }
                lastDigit = digit
            }
        }

        if firstDigit != -1 && lastDigit == -1 {
            lastDigit = firstDigit
        }

        sum += firstDigit*10 + lastDigit
    }

    if err:= scanner.Err(); err != nil {
        fmt.Println("Error reading file", err)
    }

    fmt.Println("Sum:", sum)
}
