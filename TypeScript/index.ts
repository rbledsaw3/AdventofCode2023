import * as fs from 'fs';

function processLine(line: string): number {
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

function processFile(filePath: string) {
    const data = fs.readFileSync(filePath, 'utf8');
    const lines = data.split(/\r?\n/);
    let sum = 0;

    for (const line of lines) {
        sum += processLine(line);
    }

    console.log(`Total sum: ${sum}`);
}

processFile('inputDay1.txt');
