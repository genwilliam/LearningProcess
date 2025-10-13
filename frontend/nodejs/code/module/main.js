// 可以导入一整个js模块，也可以导入模块中的特定函数或变量

// 1. 导入一整个模块
var mathOperations = require('./exports');

// 2. 导入特定的函数
// var { add, subtract, multiply, divide } = require('./exports');
// var add = require('./exports').add;

console.log("Addition: " + mathOperations.add(5, 3));
console.log("Subtraction: " + mathOperations.subtract(5, 3));
console.log("Multiplication: " + mathOperations.multiply(5, 3));
try {
    console.log("Division: " + mathOperations.divide(5, 10));
} catch (error) {
    console.error("Error: " + error.message);
}
