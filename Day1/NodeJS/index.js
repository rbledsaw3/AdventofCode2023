const fs = require('fs');
const readline = require('readline');

async function processFile() {
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

    console.log('Total sum: ', sum);
}

processFile().catch(err => {
    console.error('Error while processing file', err);
});
