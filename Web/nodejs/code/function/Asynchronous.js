// 异步函数：在 JavaScript 中，异步函数可以通过 setTimeout、setInterval 或者使用 Promise 来实现。
function asynchronous() {
    console.log("task1");
    setTimeout(() => {
        console.log("task2");
    }, timeout = 2000);
    console.log("task3");
}
asynchronous();



// 回调函数：通过把一个函数作为参数传递给另一个函数，当异步操作完成时调用这个回调函数。
// 这种方式可以让我们在异步操作完成后执行特定的代码，但可能会导致回调地狱（callback hell）问题。
// 解决回调地狱问题的一种方法是使用 Promise 对象，它可以让我们更清晰地处理异步操作的结果。
function asyncFunction(callback) {  // 这里的callback是一个函数参数
    setTimeout(() => {
        console.log("异步操作完成");
        callback();  // 回调函数会在异步操作完成时被调用
    }, 2000);
}

asyncFunction(() => {
    console.log("回调函数执行");
});

// example2:
const fs = require('fs');

// 异步读取文件
fs.readFile('example.txt', 'utf8', (err, data) => {
  if (err) {
    console.error('读取文件出错:', err);
    return;
  }
  console.log('文件内容:', data);
});

console.log('读取文件请求已发送，继续执行其他代码...');



// Promise
function asyncPromise() {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            console.log("异步操作完成");
            resolve("Promise resolved");
        }, 2000);
    });
}
asyncPromise()
    .then(result => {
        console.log(result);
    })
    .catch(error => {
        console.error("Promise rejected:", error);
    });


// async/await
// async/await 语法糖使得处理异步操作更加直观和易读
// async/await 需要在支持 ES2017 的环境中使用，或者使用 Babel 等工具进行转译
// 注意：async/await 只能在 async 函数内部使用
// async/await 使得异步代码看起来像同步代码，易于理解和维护
async function asyncAwait() {
    try {
        const result = await asyncPromise();
        console.log(result);
    } catch (error) {
        console.error("Error in async/await:", error);
    }
}
asyncAwait();
