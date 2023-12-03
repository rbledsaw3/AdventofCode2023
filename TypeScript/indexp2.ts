import * as fs from 'fs';

const ASCII_ZERO: number = '0'.charCodeAt(0);

function findNumber(line: string, wordMap: { [key: string]: string }, searchFromStart: boolean): number {
    if (!line) {
        return -1;
    }

    let index: number = searchFromStart ? 0 : line.length - 1;
    const increment: number = searchFromStart ? 1 : -1;

    while ((searchFromStart && index < line.length) || (!searchFromStart && index >= 0)) {
        if (!isNaN(parseInt(line[index], 10))) {
            return line.charCodeAt(index) - ASCII_ZERO;
        }

        let currentWord: string = '';
        for (let i: number = index; (searchFromStart && i < line.length) || (!searchFromStart && i >= 0); i += increment) {
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

function processLine(line: string): string {
    const wordMap: { [key: string]: string } = {
        'one': '1', 'two': '2', 'three': '3', 'four': '4',
        'five': '5', 'six': '6', 'seven': '7', 'eight': '8', 'nine': '9'
    };

    const firstNumber: number = findNumber(line, wordMap, true);
    const lastNumber: number = findNumber(line, wordMap, false);

    return (firstNumber !== -1 && lastNumber !== -1) ? `${firstNumber}${lastNumber}` : '';
}

fs.readFile('inputDay1.txt', 'utf8', (err, data) => {
    if (err) {
        console.error('Error reading file:', err);
        return;
    }

    const lines: string[] = data.split('\n');
    let sum: number = 0;

    for (const line of lines) {
        const processedLine: string = processLine(line);
        if (processedLine) {
            sum += parseInt(processedLine, 10);
        }
    }

    console.log('Total sum:', sum);
});

