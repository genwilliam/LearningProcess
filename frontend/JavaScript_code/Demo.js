// 获取当前日期
let currentDate = new Date();

// 获取年份
let year = currentDate.getFullYear();

// 获取月份，注意：月份从0开始，所以加1
let month = currentDate.getMonth() + 1; 

// 获取日期
let day = currentDate.getDate();

// 格式化输出：年-月-日
console.log(year + '-' + (month < 10 ? '0' + month : month) + '-' + (day < 10 ? '0' + day : day));
console.log(year + '-' + (month < 10 ? '0' + month : month) + '-' + (day < 10 ? '0' + day : day));

