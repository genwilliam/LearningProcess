# null 和 undefined的区别

![PixPin_2025-11-15_17-08-19](https://raw.githubusercontent.com/genwilliam/picgo_img/main/img/PixPin_2025-11-15_17-08-19.png)

语意上,`null`认为是无对象, `undefined`是无值的



#### undefined

比如我定义了一个变量 demo:

```javascript
var demo;
console.log(demo);
```

打印的是 `undefined`



这说明,这个demo,将来可以是任意数据类型的值,比如数字,字符串,对象……



#### null

如果是定义变量并赋值为`null`

```javascript
var demo = null;
console.log(demo);
```

打印的是`null`



说明现在还不是一个对象,但是以后有可能是一个对象



#### 抽象漏洞(abstraction leak)

`null`和`undefined`错误的共享了同一个类型标记,

这就导致:

```javascript
console.log(typeof null);
```

输出`object`

 



#### 总结

JavaScript 的历史包袱比较多，它最早设计的时候为了区分两件事：

##### `undefined`: 系统级的 “缺省状态”

- 变量声明了，但没赋值 → `undefined`
- 函数没有返回值 → 默认返回 `undefined`
- 访问对象不存在的属性 → `undefined`

它表示：**“这东西还没准备好”**

##### `null`: 开发者主动设置的 “空对象”

- 用来表示“你将来应该放的是一个对象，但现在我先给你一个空的”
- 也是一种占位符
- 清除不再需要的引用（帮助垃圾回收）

它表示：
 **“我已经准备好让你放一个值了，但现在先空着。”**

