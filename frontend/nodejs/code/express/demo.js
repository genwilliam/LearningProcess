var experss = require('express');
var app = experss();

app.get('/demo', function (req, res) {
    res.send('Hello, this is a demo endpoint!');
});

app.listen(3000,'127.0.0.1', function () { // 指定'127.0.0.1'否则会监听所有IP地址，address显示为 '::'
    var host = this.address().address;
    var port = this.address().port;
    console.log('Demo app listening at http://%s:%s', host, port);

    console.log('Demo app listening on port 3000!');
});

