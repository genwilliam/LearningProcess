document.getElementById('button')
    .addEventListener('click', function () {
        const inputBox = document.getElementById('inputBox');
        const outputBox = document.getElementById('outputBox');
        const expression = inputBox.value;

        try {
            const result = eval(expression);
            outputBox.textContent = result;
        } catch (e) {
            outputBox.textContent = '错误的算式';
        }
        /*
        eval() 的参数是一个字符串。
        如果字符串表示的是表达式，eval() 会对表达式进行求值。
        如果参数表示一个或多个 JavaScript 语句，
        那么eval() 就会执行这些语句。不需要用 eval()
        来执行一个算术表达式：因为 JavaScript 可以自动为算术表达式求值。
        */

    });
