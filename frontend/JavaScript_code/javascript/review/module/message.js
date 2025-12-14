// default export
// 一个文件中只能有一个默认导出
const message = () => {
    const name = 'john';
    const age = 21;

    return name + ' is ' + age + 'years old.';
}

export default message;