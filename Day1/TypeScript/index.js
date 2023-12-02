"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const fs = __importStar(require("fs"));
function processLine(line) {
    let firstDigit = -1;
    let lastDigit = -1;
    for (const chr of line) {
        if (!isNaN(parseInt(chr)) && chr.trim() !== '') {
            const digit = parseInt(chr, 10);
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
    const data = fs.readFileSync(filePath, 'utf8');
    const lines = data.split(/\r?\n/);
    let sum = 0;
    for (const line of lines) {
        sum += processLine(line);
    }
    console.log(`Total sum: ${sum}`);
}
processFile('input.txt');
