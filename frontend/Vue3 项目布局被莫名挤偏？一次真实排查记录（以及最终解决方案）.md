# **Vue3 项目布局被莫名挤偏？一次真实排查记录（以及最终解决方案）**







## **前言**





最近在拆分布局组件（Header / Toolbar / Main）的时候，我突然发现一件非常奇怪的事：



> **整个页面明明应该是全屏布局（100vw / 100vh），但实际 UI 只占了中间一小条。**



左边空了一大块灰色寂寞空间,右边还可以左右滚动



于是我开始了一次排查之旅。



# **最初怀疑：是不是布局组件写错了？**





我最先检查的是我自己写的这三个组件：



- layouts/index.vue
- TheHeader.vue
- TheToolbar.vue
- TheMain.vue





代码大概长这样：

```
<div class="layout-container">
  <TheHeader />
  <TheToolbar />
  <main class="layout-main">
    <RouterView />
  </main>
</div>
```

样式也是标准 flex：

```
.layout-container {
  display: flex;
  flex-direction: column;
  height: 100vh;
  width: 100vw;
  overflow: hidden;
}
```

理论上，这样的布局一定是**从左到右撑满全屏的**。



但事实不是



# **开始怀疑：是不是某个子组件撑开了？**





为了验证，我打开了 Chrome DevTools，选中最外层的 #app 节点。



然后我看到了 —— 一个“原罪级别”的东西。





# **罪魁祸首：Vite 默认模板的 main.css！**





原来我项目里有一个文件：



```src/assets/main.css```



内容是 **Vite + Vue3 官方模板自动生成的布局示例**。



里面有这么两段代码：

```
#app {
  max-width: 1280px;
  margin: 0 auto;
  padding: 2rem;
  font-weight: normal;
}
```

以及媒体查询里还有：

```
@media (min-width: 1024px) {
  body {
    display: flex;
    place-items: center;
  }

  #app {
    display: grid;
    grid-template-columns: 1fr 1fr;
    padding: 0 2rem;
  }
}
```



### **这是什么意思？**





官方模板本来是给你做一个“居中内容区”的。



也就是说 —— **Vue 根节点 #app 被强行限制成了最大 1280px 宽，并且被居中了。**



这恰恰解释了为什么：



- 我改再多布局，页面就是不贴左
- 我的布局永远只有中间那一条
- 左右两边出现大片空白
- 工具栏输入框永远无法贴边对齐





因为你整个页面，都装在这个被限制宽度的箱子里了。



你在箱子里面跳得再欢，也跳不出去。



------





# **解决方案：直接注释掉这些“模板遗留样式”**





最终，只需要做一件事：



- 找到 src/assets/main.css



然后把下面这两段注释掉：

```
/* #app {
  max-width: 1280px;
  margin: 0 auto;
  padding: 2rem;
  font-weight: normal;
} */

@media (min-width: 1024px) {
  /* #app {
    display: grid;
    grid-template-columns: 1fr 1fr;
    padding: 0 2rem;
  } */
}
```

保存一下，整个页面瞬间变回正常的全屏布局——

世界和平 ✌️



------





# **总结（防止以后再踩坑）**





如果你也在写 Vue3 全屏后台项目，而你的布局突然出现了这些症状：



- 页面总是“只在中间一小块范围”
- 左侧或右侧出现奇怪留白
- 明明设置了 width:100vw 页面还是不贴边
- 页面突然可以左右滚动
- Toolbar / Header 无论如何无法对齐左边





请第一时间检查：



- src/assets/main.css

- 是否存在对 #app 的 max-width / margin / grid 控制

- 是否来自 vite 官方模板残留样式



如果你的项目设计本身不是“居中内容区”模式，那么这些模板样式 **应该全部删除**。



------





# **写在最后（一点感想 😄）**





其实这个问题不是 Vue 的锅，也不是你的布局代码写错。纯粹是：



> **Vite 默认模板为了“好看”，给 #app 加了一个 max-width 1280px 居中布局。**



但对于需要铺满全屏的后台系统、控制台、可视化页面，这个默认值直接就是灾难。



以后如果你再创建 Vue3 项目，记得第一件事就是：



> **删掉 main.css 中对 #app 的所有样式。**



毕竟，谁也不希望，把一个后台页面塞进一个 1280px 的小盒子里吧 