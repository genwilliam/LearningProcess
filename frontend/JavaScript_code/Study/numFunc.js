// toExponential()方法返回以数字表示的数字字符串
const num = 12.34567;
console.log(num.toExponential())
console.log(num.toExponential(2))/*数字表示保留几位小数(四舍五入)*/
console.log(num.toExponential(4))
console.log(num.toExponential(6))

// toFixed()方法使用定点表示法格式化数字
const number = 12.525;
console.log(number.toFixed())
console.log(number.toFixed(2))/*数字表示保留几位小数(四舍五入)*/
console.log(number.toFixed(4))
console.log(number.toFixed(6))
