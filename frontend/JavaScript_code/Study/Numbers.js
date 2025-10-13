let num1 = 999999999999999n  // BigInt不能有小数
let num2  = BigInt(999999999999999)  // BigInt不可以用右移运算符，因为他没有固定宽度
console.log(num1)
console.log(num2)
let x = Number.MAX_SAFE_INTEGER  // 最大安全的整数
let y = Number.MIN_SAFE_INTEGER  // 最小安全的整数
console.log(x)
console.log(y)

boolean1 = Number.isInteger(1)  // 判断是否是整数
boolean2 = Number.isInteger(1.1)
console.log(boolean1)
console.log(boolean2)

boolean3 = Number.isSafeInteger(111)  // 判断是否是安全整数
console.log(boolean3)

/*
    数字方法：
    1.toString()  返回字符串
    2.toFixed(n)  保留n位小数
    3.toPrecision(n)  保留n位有效数字
    4.toExponential(n)  以科学计数法表示
    5.toString(n)  转换为n进制
    6.toLocaleString()  本地化数字
    7.valueOf()  返回数字本身
    8.toLocaleString()  本地化数字
*/

let num3 = 123.456
console.log(num3.toString())
console.log(num3.toFixed(2))
console.log(num3.toPrecision(2))
console.log(num3.toExponential(2))
console.log(num3.toString(2))
console.log(num3.toLocaleString())
console.log(num3.valueOf())

// Number() 方法可用于将 JavaScript 变量转换为数字：
// 如果无法转换数字，则返回 NaN
let str = "100"
console.log(Number(str))
let str2 = "100a"
console.log(Number(str2))

console.log(Number(new Date("1970-01-01")))

const array = [1,2,3,4,5]
array.push(7)  // push() 方法可向数组的末尾添加一个或多个元素，并返回新的长度。
// 在数组中没有append()方法
console.log(array)


