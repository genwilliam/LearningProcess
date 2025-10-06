const r = 
    console.log.
    call.call.call.call.call.call.
    call.call.call.call.call.call.
    call.call.call.call.call.call.
    call.call.call.call.call.call.
    call.call.call.call.call.call.
    call.call.call.call.call.call.
    call.call.call.call.call.call.
    apply (
        (a) => a,
        [1, 2]
    )


console.log(r);



/*
    函数.apply(xxx, [1, 2]) 表示：调用xxx函数，把apply中的第一个参数作为this指向，第二个参数作为函数的参数
    相当于xxx.函数(1, 2) 的效果
    xxx : (a) => a
    函数： call
*/