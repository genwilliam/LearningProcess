const a = [1, 2, 3, 4, 5, 6]
let newVar = typeof a;  // 结果是object
console.log(newVar)

const fruits = ["Banana", "Orange", "Apple", "Mango"];
console.log(fruits)
let s = fruits.join("**");  // join() 方法也可将所有数组元素结合为一个字符串,可以规定分隔符
console.log(s)

// pop() 方法从数组中删除最后一个元素
// 使用 delete 会在数组留下未定义的空洞。请使用 pop() 或 shift() 取而代之。
let s1 = fruits.pop();  // pop() 方法返回“被弹出”的值
console.log(fruits)
console.log("删除的值为：" + s1)

// push() 方法（在数组结尾处）向数组添加一个新的元素
fruits.push("Kiwi");
console.log(fruits)

// shift() 方法会删除首个数组元素，并把所有其他元素“位移”到更低的索引
let s2 = fruits.shift();
console.log("移除的首个元素为：" + s2)
console.log(fruits)

// unshift() 方法（在开头）向数组添加新元素，并“反向位移”旧元素
let len = fruits.unshift("Lemon");
console.log("新数组得长度为：" + len)  //unshift() 方法返回新数组的长度
console.log(fruits)

// splice() 方法可用于向数组添加新项
/*
* 第一个参数（2）定义了应添加新元素的位置（拼接）（第几个元素开始）。
第二个参数（0）定义应删除多少元素。参数不为0，则从该位置开始删除元素。
其余参数（“Lemon”，“Kiwi”）定义要添加的新元素。
splice() 方法返回一个包含已删除项的数组：
* */
fruits.splice(2, 0, "Lemon", "Kiwi");
console.log(fruits)

// 能够使用 splice() 在数组中不留“空洞”的情况下移除元素
fruits.splice(0, 1);
console.log(fruits)

// concat() 方法通过合并（连接）现有数组来创建一个新数组
/*
  concat() 方法不会更改现有数组。它总是返回一个新数组。
  concat() 方法可以使用任意数量的数组参数
  concat() 方法也可以将值作为参数
* */
const myGirls = ["Cecilie", "Lone"];
const myBoys = ["Emil", "Tobias", "Linus"];
const myChildren = myGirls.concat(myBoys);
console.log(myChildren)

// slice() 方法用数组的某个片段切出新数组
/*
* slice() 方法创建新数组。它不会从源数组中删除任何元素。
* */
const fruits1 = ["Banana", "Orange", "Lemon", "Apple", "Mango"];
const citrus = fruits1.slice(1, 3);  // 包左不包右
console.log(citrus)


/*数组排序*/
const fru = ["Banana", "Orange", "Apple", "Mango"];
fru.sort();            // 对 fruits 中的元素进行排序
console.log(fru)
// reverse() 方法反转数组中的元素。
let strings = fru.reverse();
console.log(strings)

/*
* map() 方法通过对每个数组元素执行函数来创建新数组。
  map() 方法不会对没有值的数组元素执行函数。
  map() 方法不会更改原始数组。
* */
const numbers = [4, 9, 16, 25];
const newArr = numbers.map(Math.sqrt);
console.log(newArr)
const arr = [1, 2, 3, 4, 5];
let newArr1 = arr.map(myFunction);
function myFunction(value, index, array) {
    return value * 2;
}
console.log(newArr1)


/*
* filter() 方法创建一个新数组，其包含通过测试（函数内判断）的数组元素。
  filter() 方法不会改变原始数组。
* */
const ages = [32, 33, 16, 40];
const result = ages.filter(checkAdult);
function checkAdult(age) {
    return age >= 18;
}
console.log(result)

/*
* reduce() 方法对数组中的每个元素执行一个由您提供的 reducer 函数，将其结果汇总为单个返回值。
  reduce() 方法会从左到右（从索引 0 开始）遍历数组，并将每个值与一个“累计器”值进行 reduction（归约）。
  reduce() 方法没有 reducer 函数时，数组中的第一个值会用作初始值，从第二个值开始。
  reduce() 方法不改变原始数组。
* */
const arr1 = [1, 2, 3, 4, 5];
const sum = arr1.reduce(reducer);
function reducer(accumulator, currentValue) {
    return accumulator + currentValue;
}
console.log(sum)

/*
* reduceRight() 方法在每个数组元素上运行函数，以生成（减少它）单个值。
reduceRight() 方法在数组中从右到左工作。另请参阅 reduce()。
reduceRight() 方法不会减少原始数组。
* */

const arr2 = [1, 2, 3, 4];
const sum1 = arr2.reduceRight(reducer1);
function reducer1(accumulator, currentValue) {
    return accumulator + currentValue;
}
console.log(sum1)
