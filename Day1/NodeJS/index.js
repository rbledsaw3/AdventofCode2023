const fs = require('fs');
const readline = require('readline');

async function processFilePart1() {
    const fileStream = fs.createReadStream('input.txt');
    const rl = readline.createInterface({
        input: fileStream,
        crlfDelay: Infinity
    });

    let sum = 0;

    for await (const line of rl) {
        let firstDigit = -1;
        let lastDigit = -1;

        for (const chr of line) {
            if (!isNaN(chr) && chr.trim() !== '') {
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

        sum += firstDigit * 10 + lastDigit;
    }

    console.log('Part 1 Total sum: ', sum);
}

processFilePart1().catch(err => {
    console.error('Error while processing file', err);
});

const ASCII_ZERO = '0'.charCodeAt(0);

function findNumber(line, wordMap, searchFromStart) {
    if (!line) {
        return -1;
    }

    let index = searchFromStart ? 0 : line.length - 1;
    const increment = searchFromStart ? 1 : -1;

    while ((searchFromStart && index < line.length) || (!searchFromStart && index >= 0)) {
        if (!isNaN(parseInt(line[index], 10))) {
            return line.charCodeAt(index) - ASCII_ZERO;
        }

        let currentWord = '';
        for (let i = index; (searchFromStart && i < line.length) || (!searchFromStart && i >= 0); i += increment) {
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
    const wordMap = {
        'one': '1', 'two': '2', 'three': '3', 'four': '4',
        'five': '5', 'six': '6', 'seven': '7', 'eight': '8', 'nine': '9'
    };

    const firstNumber = findNumber(line, wordMap, true);
    const lastNumber = findNumber(line, wordMap, false);

    return (firstNumber !== -1 && lastNumber !== -1) ? `${firstNumber}${lastNumber}` : '';
}

fs.readFile('input.txt', 'utf8', (err, data) => {
    if (err) {
        console.error('Error reading file:', err);
        return;
    }

    const lines = data.split('\n');
    let sum = 0;

    for (const line of lines) {
        const processedLine = processLine(line);
        if (processedLine) {
            sum += parseInt(processedLine, 10);
        }
    }

    console.log('Part 2 Total sum:', sum);
});
