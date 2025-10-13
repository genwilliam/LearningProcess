const arr = [1, 2, 3, 4, 5, 6, 7];
for (let i in arr) {/*for in 循环趋向于索引*/
    console.log(i); // i为索引
}
for (let i of arr) {/*for of 循环趋向于值*/
    console.log(i); // i为值
}


const array = ['a', 'b', 'c', 'd', 'e', 'f'];
for (let j in array) {
    console.log(i); // j为索引
}
for (let j of array) {
    console.log(j); // j为值
}
