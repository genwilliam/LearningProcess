// async 函数总是返回一个 Promise：
// 如果返回值不是 Promise，会自动包装成 resolved Promise
// 如果抛出异常，会返回 rejected Promise
async function fetchData() {
    const somePromise = new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve('Data fetched');
        }, 2000);
    });
    // await 只能在 async 函数内部使用
    const result = await somePromise;
    console.log(result);
}

fetchData();
console.log('After fetchData call');

