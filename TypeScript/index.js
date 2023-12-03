"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
var fs = require("fs");
function processLine(line) {
    var firstDigit = -1;
    var lastDigit = -1;
    for (var _i = 0, line_1 = line; _i < line_1.length; _i++) {
        var chr = line_1[_i];
        if (!isNaN(parseInt(chr)) && chr.trim() !== '') {
            var digit = parseInt(chr, 10);
            if (firstDigit === -1) {
                firstDigit = digit;
            }
            lastDigit = digit;
        }
    }
    if (firstDigit !== -1 && lastDigit === -1) {
        lastDigit = firstDigit;
    }
    return firstDigit * 10 + lastDigit;
}
function processFile(filePath) {
    var data = fs.readFileSync(filePath, 'utf8');
    var lines = data.split(/\r?\n/);
    var sum = 0;
    for (var _i = 0, lines_1 = lines; _i < lines_1.length; _i++) {
        var line = lines_1[_i];
        sum += processLine(line);
    }
    console.log("Total sum: ".concat(sum));
}
processFile('inputDay1.txt');
