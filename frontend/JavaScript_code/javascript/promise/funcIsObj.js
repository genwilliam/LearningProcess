// 函数本质上是一个对象
function foo() {}
console.log(typeof foo); // "function"


// 函数本质上是 Object 的实例
// instanceof 是一个 运算符，用来判断某个对象在其原型链上，是否存在指定构造函数的 prototype。
console.log(foo instanceof Object); // true

// 给函数添加属性
foo.bar = 123;
console.log(foo.bar); // 123

// 函数的原型链
console.log(foo.__proto__ === Function.prototype); // true
console.log(Function.prototype.__proto__ === Object.prototype); // true
console.log(Object.prototype.__proto__ === null); // true
