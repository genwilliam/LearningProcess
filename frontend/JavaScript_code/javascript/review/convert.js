// [] == ![];
console.log([] == ![]);

console.log(Number(undefined)); // NaN
console.log(Number(null)); // 0

console.log(String(undefined));
console.log(String(null));

console.log("--------");
console.log(Boolean(undefined));
console.log(Boolean(null));
console.log(Boolean(""));
console.log(Boolean(false));
console.log(Boolean(true));
console.log(Boolean(NaN));

console.log("-----------");
// [] == ![];   // []转布尔→true
// [] == !true; // !true→false
// [] == false; // false转数字→0
// [] == 0;     // []转字符串''
// '' == 0;     // ''转数字→0，0==0
// 0 == 0;      // 类型+值均相等，直接匹配
