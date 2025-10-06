// 箭头函数的主体只有一个表达式时，可以省略大括号和 return 关键字
const add = (a, b) => a + b;
console.log(add(2, 3));

// 箭头函数的主体有多条语句时，必须使用大括号和 return 关键字
const addWithBody = (a, b) => {
    const sum = a + b;
    return sum;
}
console.log(addWithBody(2, 3));

// 箭头函数可以省略参数括号，当只有一个参数时
const square = x => x * x;
console.log(square(4));

// 箭头函数没有参数时，需要使用空括号
const greet = () => "Hello, World!";
console.log(greet());

// 箭头函数可以作为参数传递给其他函数
const numbers = [1, 2, 3, 4, 5];
const doubled = numbers.map(num => num * 2);
console.log(doubled); // [2, 4, 6, 8, 10]

// 箭头函数的this绑定是静态的，指向定义时的上下文，而不是调用时的上下文
const obj = {
    value: 10,
    getValue: function() {
        return () => this.value; // this指向obj
    }
};
const getValue = obj.getValue();
console.log(getValue()); // 10


// 箭头函数不能作为构造函数使用
const Person = (name) => {
    this.name = name; // 这里的this不会指向新创建的对象
}
// const person = new Person("Alice"); // TypeError: Person is not a constructor


// 箭头函数不能使用 arguments 对象
const sum = (...args) => {
    return args.reduce((acc, curr) => acc + curr, 0);
};
console.log(sum(1, 2, 3, 4)); // 10


// 箭头函数可以与其他函数结合使用
const numbers2 = [1, 2, 3, 4, 5];
const squares = numbers2.map(num => num * num);
console.log(squares); // [1, 4, 9, 16, 25]




