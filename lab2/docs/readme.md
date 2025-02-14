# ENSE481 - Lab 2
Cameron Oehler \
200384643

Running -Ofast APB1=64MHz
| Test | Avg Ticks | WCET Ticks | Scopy (1 run) us | Scopy (1 run) ticks |
| -------- | ------- | ------ | ------ | ------ |
| addTwoRandom32BitIntegers | 28 | 28 | 1.271 | ~81 |
| addTwoRandom64BitIntegers | 32 | 32 | 1.320 | ~84 |
| multiplyTwoRandom32BitIntegers | 28 | 28 | 1.222 | ~78 |
| multiplyTwoRandom64BitIntegers | 40 | 40 | 1.418 | ~91 |
| divideTwoRandom32BitIntegers | 39 | 42 | 1.369 | ~88 |
| divideTwoRandom64BitIntegers | 176 | 178 | 3.570 | ~228 |
| copy8ByteStruct | 34 | 34 | 1.369 | ~88 |
| copy128ByteStruct | 1201 | 1202 | 19.511 | ~1249 |
| copy1024ByteStruct | 9267 | 9268 | 145.467 | ~9310 |

