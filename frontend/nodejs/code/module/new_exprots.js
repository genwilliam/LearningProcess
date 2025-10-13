// 向模块中添加功能
var example = require('./exports');

// 添加一个新的函数
example.exportNewFunction = function() {
    console.log("This is a new function added to the module.");
}

module.exports = example; // 确保导出修改后的模块

// 使用新的函数(可以在其他文件中调用)
example.exportNewFunction();