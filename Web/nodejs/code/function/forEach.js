var arr = ['a', 'b', 'c', 'd', 'e', 'f'];

// 数组的 forEach 方法
// 用于遍历数组中的每个元素，并对每个元素执行指定的函数
// 语法：array.forEach(function(currentValue, index, array), thisArg)
// currentValue: 当前元素的值
// index: 当前元素的索引
// array: 被遍历的数组
// thisArg: 可选，执行回调函数时的 this 值
// 注意：forEach 不会返回任何值，它只是对数组的每个元素执行一次提供的函数
arr.forEach(function(value, index) {
    console.log('Index: ' + index + ', Value: ' + value);
});

// 自定义实现的 forEach 函数
// 该函数接受一个数组和一个回调函数，对数组的每个元素执行回调函数
function arr_forEach(arr, callback) {
    if (!Array.isArray(arr)) {
        throw new TypeError('First argument must be an array');
    }
    if (typeof callback !== 'function') {
        throw new TypeError('Second argument must be a function');
    }
    
    for (let i = 0; i < arr.length; i++) {
        callback(arr[i], i, arr);
    }
}



