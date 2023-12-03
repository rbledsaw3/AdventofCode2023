package main

import (
  "bufio"
  "fmt"
  "os"
  "strconv"
  "strings"
)

const ASCII_ZERO = int('0')

func findNumber(line string, wordMap map[string]byte, searchFromStart bool) int {
  if line == "" {
    return -1
  }
  index := 0
  if !searchFromStart {
    index = len(line) - 1
  }
  increment := 1
  if !searchFromStart {
    increment = -1
  }
  for searchFromStart && index < len(line) || !searchFromStart && index >= 0 {
    if line[index] >= '0' && line[index] <= '9' {
      return int(line[index]) - ASCII_ZERO
    }
    currentWord := ""
    for i := index; searchFromStart && i < len(line) || !searchFromStart && i >= 0; i += increment {
      if searchFromStart {
        currentWord = line[index : i+1]
      } else {
        currentWord = line[i : index+1]
      }
      currentWord = strings.ToLower(currentWord)
      if val, ok := wordMap[currentWord]; ok {
        return int(val) - int('0')
      }
      if line[i] < 'A' || line[i] > 'z' {
        break
      }
    }
    index += increment
  }
  return -1
}

func processLine(line string) string {
  wordMap := map[string]byte{
    "one":   '1',
    "two":   '2',
    "three": '3',
    "four":  '4',
    "five":  '5',
    "six":   '6',
    "seven": '7',
    "eight": '8',
    "nine":  '9',
  }
  firstNumber := findNumber(line, wordMap, true)
  lastNumber := findNumber(line, wordMap, false)
  if firstNumber != -1 && lastNumber != -1 {
    return strconv.Itoa(firstNumber) + strconv.Itoa(lastNumber)
  }
  return ""
}

func main() {
  file, err := os.Open("inputDay1.txt")
  if err != nil {
    fmt.Println("Error opening file")
    return
  }
  defer file.Close()

  scanner := bufio.NewScanner(file)
  sum := 0
  for scanner.Scan() {
    line := scanner.Text()
    processedLine := processLine(line)
    if processedLine != "" {
      num, _ := strconv.Atoi(processedLine)
      sum += num
    }
    fmt.Println(sum)
  }

  fmt.Println("Total sum:", sum)
}
