var rewrite = require('./exports');

delete rewrite.add; // 删除 add 函数
// delete rewrite['add']; // 也可以使用这种方式删除

// rewrite.add(10, 20); // 报错


