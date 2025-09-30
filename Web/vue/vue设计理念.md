### Vue 的设计理念

Vue 的核心设计理念就是**声明式渲染**和**组件化**。这意味着，你用 Vue 编写界面时，更多的是声明你想要的结果，而不是关注每一步是如何实现的。

比如说，我们经常会在 Vue 中看到这样的代码：

```javascript
<p>{{ message }}</p>
```

这段代码看起来很简单，但是它的意思是：Vue 会自动渲染 `message` 变量的值到 `<p>` 标签中，而你只需要告诉 Vue 去做这件事就行了。你不需要自己手动去修改 DOM 元素，Vue 会帮你处理。

此外，Vue 提倡**组件化**，也就是说，我们可以把界面拆成一个个小的部分，每个部分都有自己的逻辑和视图，这样就很容易管理和复用代码了。

### 虚拟 DOM 和 真实 DOM

接下来聊聊 Vue 是如何高效更新界面的。这个过程离不开**虚拟 DOM**。

#### 什么是虚拟 DOM？

真实的 DOM 就是浏览器中的文档对象模型，它是 HTML 元素在浏览器中的表示。每当我们修改页面内容时，浏览器会重新渲染和更新这个 DOM。如果页面比较复杂，频繁地操作真实 DOM 会导致性能问题。

为了优化这个问题，Vue 引入了 **虚拟 DOM**。虚拟 DOM 就是一个 JavaScript 对象，它模拟了真实 DOM 的结构。你可以把虚拟 DOM 想象成一个轻量级的“快照”或者“副本”，它看起来和真实的 DOM 一模一样，但是没有直接操作界面，它只是存在内存中。

#### Vue 是怎么使用虚拟 DOM 的？

1. **初次渲染：** 当 Vue 应用开始运行时，它会根据你定义的组件和数据，生成虚拟 DOM。这个虚拟 DOM 就是你整个应用的初步结构。
2. **数据变化：** 当你改变了某个数据，比如修改了 `message`，Vue 会更新虚拟 DOM 中对应的数据。虚拟 DOM 和真实 DOM 是分开的，Vue 并不会立刻把新的虚拟 DOM 内容直接刷新到页面上。
3. **比较差异：** Vue 会有一个“diff 算法”，也叫“虚拟 DOM 比对算法”。它会比较旧的虚拟 DOM 和新的虚拟 DOM，找出它们之间的差异，生成最小的修改方案。
4. **更新真实 DOM：** 最后，Vue 根据差异来更新真实 DOM。它会把变化最小化，只改变需要变动的部分，避免每次数据更新时重新渲染整个页面。

#### 为什么这样做？

这种做法能大大提高性能。因为虚拟 DOM 是在内存中进行操作的，相较于直接操作浏览器中的真实 DOM，速度更快。而且 Vue 通过 diff 算法，只更新页面上发生变化的部分，避免了不必要的重绘和重排，提升了效率。

### 真实 DOM 和虚拟 DOM 之间的交互

简单来说，真实 DOM 和虚拟 DOM 之间的交互流程大概就是这样的：

1. **Vue 会创建虚拟 DOM** 来表示你组件的结构。
2. **数据变化** 后，Vue 会生成新的虚拟 DOM。
3. 然后，**Vue 比较新旧虚拟 DOM**，找到它们的差异（diff 算法）。
4. 最后，**Vue 将差异更新到真实 DOM**，确保页面显示是最新的。

通过这种方式，Vue 在保持高效更新的同时，也让开发者不需要过多关注 DOM 操作本身，而是可以专注于数据和界面的绑定。

### 总结一下

- **声明式渲染**：你只需要告诉 Vue 你想要的结果，而不关心实现细节。
- **虚拟 DOM**：它是内存中的轻量级 DOM 结构，能够提高性能。
- **数据变化和 DOM 更新**：数据变化后，Vue 会通过虚拟 DOM 进行对比，找出差异并更新真实 DOM，避免不必要的页面重渲染。



### 面试题

vue3中的`setup`和传统配置项`data()` , `methons` 有什么区别？

setup和传统的配置项可不可以同时写，如果冲突了以谁为主，传统配置项能不能取setup的的东西，setup能不能取传统配置项的东西？



#### 答

1. setup和传统配置项可以同时存在，如果冲突了以setup为主
2. 传统配置项可以使用`this`，在setup中不能，显示为undefined
3. data()可以获取setup的东西，但是setup不能获取data的东西（没有this）。因为setup生命周期在data之前，在data执行之前，setup就已经解析完毕

```js
data() {
    alert(this.name)
  },
 setup() {
    const name = "zhangsan";
    return { name };
  }
```





# vue2

## 怎么确定**methods 本质就是一个对象**

-  直接查看定义时的methods

在你创建实例之前，methods 就是一个普通的对象：

```
var options = {
  methods: {
    reverseMessage: function () {
      this.message = this.message.split('').reverse().join('')
    }
  }
}
console.log(options.methods)
```

在控制台里会打印：

```
{
  reverseMessage: ƒ ()
}
```



2. 查看 Vue 实例上的方法

假设你定义了：

```
var app5 = new Vue({
  el: '#app-5',
  data: {
    message: 'Hello Vue.js!'
  },
  methods: {
    reverseMessage: function () {
      this.message = this.message.split('').reverse().join('')
    }
  }
})
```

在控制台输入：

```
app5.reverseMessage
```

会输出：

```
ƒ () { this.message = this.message.split('').reverse().join('') }
```

这说明 Vue 已经把 methods 里的函数挂载到了实例上。

3. 确认methods是对象的方法

你也可以在控制台里验证它的类型：

```
typeof app5.$options.methods   // "object"
app5.$options.methods          // { reverseMessage: ƒ }
```

$options 是 Vue 实例里保存的原始配置对象，你能直接看到 methods 确实是个对象。

同理，data本质上是一个函数，el本质上是一个string



## 定义组件

### **1. 什么是组件？**

在 Vue 里，**组件（component）就是可以复用的一块小的页面结构**。

你可以把它想象成乐高积木：

- 页面是由很多小积木拼起来的
- 每个积木都有自己长什么样（模板）、自己的数据、自己的逻辑

### **2. 定义组件的语法**



```
Vue.component('todo-item', {
  template: '<li>这是个待办项</li>'
})
```

这行代码做了两件事：



1. **注册一个全局组件**，名字叫 **todo-item**。

   

   - 注意：名字必须是 **小写+中横线**（这是 HTML 的规范）。
   - 以后你就可以在 HTML 模板里用 <todo-item></todo-item> 来使用它。

   

2. **给这个组件定义了一个模板**（template）。

   

   - 模板就是这块“积木”显示的内容。
   - 现在它的内容就是：


```
<li>这是个待办项</li>
```





所以现在你拥有了一个叫 **todo-item** 的小积木，拼到页面上就会显示一个 <li>。

### **3. 在 Vue 实例里使用组件**

接下来你创建 Vue 实例：

```
var app = new Vue({
  el: '#app'
})
```

假设你有一个 HTML：

```
<div id="app">
  <ol>
    <!-- 在这里使用组件 -->
    <todo-item></todo-item>
    <todo-item></todo-item>
    <todo-item></todo-item>
  </ol>
</div>
```

页面结果就是：

```
<ol>
  <li>这是个待办项</li>
  <li>这是个待办项</li>
  <li>这是个待办项</li>
</ol>
```

因为 <todo-item> 被 Vue 识别成了你定义的那个组件。

### 4. 总结

- **Vue.component** 就是“注册一个积木”。
- **名字**是 'todo-item'，以后用 <todo-item></todo-item> 来放到页面里。
- **template** 就是这块积木里面的 HTML 长相。
- 在 Vue 实例挂载的地方（#app）使用 <todo-item> 标签，就能显示出定义好的内容。
- 

💡 小拓展：以后你可以给组件加 **props**（传参数）、**data**（自己的状态）、**methods**（方法），让这个“积木”更灵活。

## [`v-if` vs `v-show`](https://v2.cn.vuejs.org/v2/guide/conditional.html#v-if-vs-v-show)

`v-if` 是“真正”的条件渲染，因为它会确保在切换过程中条件块内的事件监听器和子组件适当地被销毁和重建。

`v-if` 也是**惰性的**：如果在初始渲染时条件为假，则什么也不做——直到条件第一次变为真时，才会开始渲染条件块。

相比之下，`v-show` 就简单得多——不管初始条件是什么，元素总是会被渲染，并且只是简单地基于 CSS 进行切换。

一般来说，`v-if` 有更高的切换开销，而 `v-show` 有更高的初始渲染开销。因此，如果需要非常频繁地切换，则使用 `v-show` 较好；如果在运行时条件很少改变，则使用 `v-if` 较好。



## [`v-if` 与 `v-for` 一起使用](https://v2.cn.vuejs.org/v2/guide/conditional.html#v-if-与-v-for-一起使用)

**不推荐**同时使用 `v-if` 和 `v-for`。请查阅[风格指南](https://v2.cn.vuejs.org/v2/style-guide/#避免-v-if-和-v-for-用在一起-必要)以获取更多信息。

当 `v-if` 与 `v-for` 一起使用时，`v-for` 具有比 `v-if` 更高的优先级。请查阅[列表渲染指南](https://v2.cn.vuejs.org/v2/guide/list.html#v-for-with-v-if)以获取详细信息。



## 关于`v-for`

当 Vue 正在更新使用 `v-for` 渲染的元素列表时，它默认使用“就地更新”的策略。如果数据项的顺序被改变，Vue 将不会移动 DOM 元素来匹配数据项的顺序，而是就地更新每个元素，并且确保它们在每个索引位置正确渲染。这个类似 Vue 1.x 的 `track-by="$index"`。

这个默认的模式是高效的，但是**只适用于不依赖子组件状态或临时 DOM 状态 (例如：表单输入值) 的列表渲染输出**。

为了给 Vue 一个提示，以便它能跟踪每个节点的身份，从而重用和重新排序现有元素，你需要为每项提供一个唯一 `key` attribute：

```
<div v-for="item in items" v-bind:key="item.id">
  <!-- 内容 -->
</div>
```

建议尽可能在使用 `v-for` 时提供 `key` attribute，除非遍历输出的 DOM 内容非常简单，或者是刻意依赖默认行为以获取性能上的提升。

因为它是 Vue 识别节点的一个通用机制，`key` 并不仅与 `v-for` 特别关联。后面我们将在指南中看到，它还具有其它用途。

不要使用对象或数组之类的非基本类型值作为 `v-for` 的 `key`。请用字符串或数值类型的值。

更多 `key` attribute 的细节用法请移步至 [`key` 的 API 文档](https://v2.cn.vuejs.org/v2/api/#key)。



## [事件修饰符](https://v2.cn.vuejs.org/v2/guide/events.html#事件修饰符)

在事件处理程序中调用 `event.preventDefault()` 或 `event.stopPropagation()` 是非常常见的需求。尽管我们可以在方法中轻松实现这点，但更好的方式是：方法只有纯粹的数据逻辑，而不是去处理 DOM 事件细节。

为了解决这个问题，Vue.js 为 `v-on` 提供了**事件修饰符**。之前提过，修饰符是由点开头的指令后缀来表示的。

- `.stop`
- `.prevent`
- `.capture`
- `.self`
- `.once`
- `.passive`

```
<!-- 阻止单击事件继续传播 -->
<a v-on:click.stop="doThis"></a>

<!-- 提交事件不再重载页面 -->
<form v-on:submit.prevent="onSubmit"></form>

<!-- 修饰符可以串联 -->
<a v-on:click.stop.prevent="doThat"></a>

<!-- 只有修饰符 -->
<form v-on:submit.prevent></form>

<!-- 添加事件监听器时使用事件捕获模式 -->
<!-- 即内部元素触发的事件先在此处理，然后才交由内部元素进行处理 -->
<div v-on:click.capture="doThis">...</div>

<!-- 只当在 event.target 是当前元素自身时触发处理函数 -->
<!-- 即事件不是从内部元素触发的 -->
<div v-on:click.self="doThat">...</div>
```

使用修饰符时，顺序很重要；相应的代码会以同样的顺序产生。因此，用 `v-on:click.prevent.self` 会阻止**所有的点击**，而 `v-on:click.self.prevent` 只会阻止对元素自身的点击。

> 2.1.4 新增

```
<!-- 点击事件将只会触发一次 -->
<a v-on:click.once="doThis"></a>
```

不像其它只能对原生的 DOM 事件起作用的修饰符，`.once` 修饰符还能被用到自定义的[组件事件](https://v2.cn.vuejs.org/v2/guide/components-custom-events.html)上。如果你还没有阅读关于组件的文档，现在大可不必担心。

> 2.3.0 新增

Vue 还对应 [`addEventListener` 中的 `passive` 选项](https://developer.mozilla.org/en-US/docs/Web/API/EventTarget/addEventListener#Parameters)提供了 `.passive` 修饰符。

```
<!-- 滚动事件的默认行为 (即滚动行为) 将会立即触发 -->
<!-- 而不会等待 `onScroll` 完成  -->
<!-- 这其中包含 `event.preventDefault()` 的情况 -->
<div v-on:scroll.passive="onScroll">...</div>
```

这个 `.passive` 修饰符尤其能够提升移动端的性能。

不要把 `.passive` 和 `.prevent` 一起使用，因为 `.prevent` 将会被忽略，同时浏览器可能会向你展示一个警告。请记住，`.passive` 会告诉浏览器你*不*想阻止事件的默认行为。



## 什么是语法糖



**语法糖 (Syntactic Sugar)** 是计算机科学里的一个术语。

👉 它的意思是：**一种让代码写起来更方便、更简洁的写法**，但本质上它并没有引入新的功能，只是对已有功能的“包装”。



换句话说：



- **语法糖 = 简化写法**
- **去掉语法糖 = 冗长但效果相同的写法**





就像吃糖不是为了营养，而是为了让味道更好，语法糖的作用就是让代码更好写、更好读。



------





### **举例（非 Vue）**





比如在 JavaScript 里：

```
class Person {
  constructor(name) {
    this.name = name;
  }
}
```

这其实是语法糖，本质等价于：

```
function Person(name) {
  this.name = name;
}
```

class 并没有创造新的功能，只是让你写起来像传统的面向对象语言。



### **Vue 中**

### **v-model**





Vue 里我们常写：

```
<input v-model="message" />
```

看起来很简单，但本质上 Vue 在背后帮你做了两件事：



等价于：

```
<input 
  :value="message" 
  @input="message = $event.target.value"
/>
```



- :value="message"   -->  把数据绑定到输入框的 value 上（单向绑定）。
- @input="..."   -- > 监听输入事件，更新 message（实现双向绑定）。



所以 **v-model = :value + @input 的语法糖**。

用 v-model 更直观、更简洁。

### 小结

- **语法糖**：简化写法，本质上不增加新功能。
- **好处**：代码更简洁、更易读。
- 在 Vue 里：v-model 是双向绑定的语法糖，本质是 :value 加上 @input。

