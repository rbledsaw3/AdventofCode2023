"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs");
var ASCII_ZERO = '0'.charCodeAt(0);
function findNumber(line, wordMap, searchFromStart) {
    if (!line) {
        return -1;
    }
    var index = searchFromStart ? 0 : line.length - 1;
    var increment = searchFromStart ? 1 : -1;
    while ((searchFromStart && index < line.length) || (!searchFromStart && index >= 0)) {
        if (!isNaN(parseInt(line[index], 10))) {
            return line.charCodeAt(index) - ASCII_ZERO;
        }
        var currentWord = '';
        for (var i = index; (searchFromStart && i < line.length) || (!searchFromStart && i >= 0); i += increment) {
            currentWord = searchFromStart ? line.slice(index, i + 1) : line.slice(i, index + 1);
            currentWord = currentWord.toLowerCase();
            if (wordMap[currentWord] !== undefined) {
                return wordMap[currentWord].charCodeAt(0) - ASCII_ZERO;
            }
            if (!/[a-z]/i.test(line[i])) {
                break;
            }
        }
        index += increment;
    }
    return -1;
}
function processLine(line) {
    var wordMap = {
        'one': '1', 'two': '2', 'three': '3', 'four': '4',
        'five': '5', 'six': '6', 'seven': '7', 'eight': '8', 'nine': '9'
    };
    var firstNumber = findNumber(line, wordMap, true);
    var lastNumber = findNumber(line, wordMap, false);
    return (firstNumber !== -1 && lastNumber !== -1) ? "".concat(firstNumber).concat(lastNumber) : '';
}
fs.readFile('inputDay1.txt', 'utf8', function (err, data) {
    if (err) {
        console.error('Error reading file:', err);
        return;
    }
    var lines = data.split('\n');
    var sum = 0;
    for (var _i = 0, lines_1 = lines; _i < lines_1.length; _i++) {
        var line = lines_1[_i];
        var processedLine = processLine(line);
        if (processedLine) {
            sum += parseInt(processedLine, 10);
        }
    }
    console.log('Total sum:', sum);
});
