let layout = String.raw`#define LAYOUT( \
    k13, k26, k36, k31, k33, k07, k63, k71, k76, ka6, ka7, ka3, ka5, k97,     k01, \
    k16, k17, k27, k37, k47, k46, k56, k57, k67, k77, k87, k86, k66, ka1,     k65, \
    k11, k10, k20, k30, k40, k41, k51, k50, k60, k70, k80, k81, k61, ka2,     k15, \
    k21, k12, k22, k32, k42, k43, k53, k52, k62, k72, k82, k83,     ka4,      k25, \
    k00, k14, k24, k34, k44, k45, k55, k54, k64, k74, k85,    k91,       k35, k75, \
    k06,    k90,    k93,       k94,          k95,     k92, k04,     k03, k73, k05  \
) \
{ \
    { k00, k01, ___, k03, k04, k05, k06, k07}, \
    { k10, k11, k12, k13, k14, k15, k16, k17}, \
    { k20, k21, k22, ___, k24, k25, k26, k27}, \
    { k30, k31, k32, k33, k34, k35, k36, k37}, \
    { k40, k41, k42, k43, k44, k45, k46, k47}, \
    { k50, k51, k52, k53, k54, k55, k56, k57}, \
    { k60, k61, k62, k63, k64, k65, k66, k67}, \
    { k70, k71, k72, k73, k74, k75, k76, k77}, \
    { k80, k81, k82, k83, ___, k85, k86, k87}, \
    { k90, k91, k92, k93, k94, k95, ___, k97}, \
    { ___, ka1, ka2, ka3, ka4, ka5, ka6, ka7}  \
}`


let led_config = String.raw`
    { 4,      NO_LED, NO_LED, 95,     65,     79, 5,      28 },
    { 8,      2,      9,      0,      10,     75, 1,      7  },
    { 14,     3,      15,     NO_LED, 16,     86, 6,      13 },
    { 20,     18,     21,     23,     22,     94, 12,     19 },
    { 25,     30,     26,     31,     27,     32, 29,     24 },
    { 41,     36,     42,     37,     43,     38, 35,     40 },
    { 46,     89,     47,     34,     48,     72, 78,     45 },
    { 52,     39,     53,     97,     54,     82, 44,     51 },
    { 58,     63,     59,     64,     NO_LED, 60, 62,     57 },
    { 11,     90,     55,     17,     33,     49, NO_LED, 69 },
    { NO_LED, 85,     93,     61,     96,     66, 50,     56 }
`

let found = layout.match(/([^(]*\(([^)]+)\))[^{]*((.|[\n\r])*)\}/m)

if (found.length !== 5) {
    console.error("cannot parse layout")
    process.exit(1)
}

let mapping = new Map();
found[3].split('}').forEach((line, row) => {
    let vars = line.match(/\b[\w\d]+\b/g)
    if (vars) {
        vars.forEach((v, col) => mapping.set(v, [row, col]))
    }
})

let rgbMatrix = led_config.split('}').map(line => line.match(/\b[\w\d]+\b/g))

let rgbIndexes = []

layout.match(/\bk[\w\d]+\b/g).forEach((v) => {
    let [r, c] = mapping.get(v)
    let idx = rgbMatrix[r][c]
    if (idx !== 'NO_LED') {
        rgbIndexes[idx] = v
    }
})

const noRgb = 'XXX'

for (let i = 0; i < rgbIndexes.length; i++) {
    if (!rgbIndexes[i]) {
        rgbIndexes[i] = noRgb
    }
}

// console.log(layout)

let ledmap = `${found[1].replace('LAYOUT', 'LEDMAP')} \\
{ \\
${rgbIndexes.reduce((groups, v, i) => {
    if (i % 8 === 0) {
        groups.push([])
    }
    groups[groups.length - 1].push(v)
    return groups
}, []).map(a => a.join(', ')).map(l => ' '.repeat(4) + l + ',').join(' \\\n')} \\\n
}`
console.log(ledmap)
