# **风格指南**

此文件描述了 **Basicamente** 项目中 **必需遵守的** 风格指南，用于在开发新功能或改进/修改现有功能时保持最佳实践。



## **项目文件夹结构**

**始终** 遵循如下文件夹结构：

```
src/
  core/
    components/
      BaseButton.vue
      BaseInput.vue
    models/
    store/
    services/
    views/
    ...
  modules/
    checkout/
      components/
        CheckoutCart.vue # web
        CheckoutCart.native.vue # 通用原生
        CheckoutCart.android.vue # 安卓原生
        CheckoutCart.ios.vue # iOS 原生
        ...
      models/
      store/
      services/
      views/
      routes.ts
      ...
    customizer/
      models/
      store/
      services/
      views/
      routes.ts
      ...
  assets/
  scss/
  App.vue
  main.ts
  router.ts
  store.ts
```

说明：

- core/：存放整个应用通用的组件、服务等。
- modules/：用于创建新的功能模块。每个模块拥有自己的 Components、Models、Store、Routes、Services 等，并且模块之间不直接通信。
- components/：存放属于模块自身或根模块的组件。
- models/：TypeScript 接口/类，用于映射实体。
- store/：根 Vuex 或命名空间 Vuex 存储。
- services/：TypeScript 类（或简单 JS 对象导出）用于实现业务逻辑。（提示：保持组件只处理界面显示逻辑）
- views/：存放路由组件（页面）。
- routes.ts：存放模块的路由列表，数组类型为 RouteConfig，并默认导出。例如：

```
// src/modules/customizer/routes.ts

import { RouteConfig } from 'vue-router'

const routes: RouteConfig[] = [
  {
    path: '/products/:product/customize',
    name: 'Customizer',
    component: () => import('./views/TheCustomizer.vue'),
  },
]

export default routes
```

------



## **命名约定**

首先，推荐阅读 [官方 Vue 风格指南](https://vuejs.org/v2/style-guide/)，此指南中使用了许多该文档中的规则。

### **多词组件名称**

组件命名应尽量使用 **多词名称**，根组件 App 或 Vue 内置组件（如 <transition>、<component>）除外。

这样可以避免与现有或未来的 HTML 元素冲突，因为 HTML 元素都是单词命名。

```
# 错误示例
components/
  Todo.vue
# 正确示例
components/
  TodoItem.vue
  TodoList.vue
```



------



### **单文件组件文件名大小写**

**单文件组件的文件名应始终使用 PascalCase（首字母大写驼峰）**。

PascalCase 在代码编辑器中提供更好的自动补全，并且在 JS(X) 和模板中引用组件时保持一致。

```
# 错误示例
components/
  mycomponent.vue
  myComponent.vue
  my-component.vue
# 正确示例
components/
  MyComponent.vue
```



------



### **其他文件命名**

除 .vue 文件外，其他文件使用后缀来表明文件类型：



- 服务（Services）：<Name>.service.ts，例如 Customizer.service.ts
- 模型（Models）：<Name>.model.ts
- Vuex Store：<Name>.store.ts

------



### **基础组件命名**

**基础组件（又称展示型、哑组件或纯组件）用于实现应用样式和约定，应统一使用 Base 前缀**。

```
# 错误示例
components/
  MyButton.vue
  VueTable.vue
  Icon.vue
# 正确示例
components/
  BaseButton.vue
  BaseTable.vue
  BaseIcon.vue
```

[> 官方 Vue 风格指南详细说明](https://vuejs.org/v2/style-guide/#Base-component-names-strongly-recommended)

------



### **单实例组件命名**

[> 遵循官方 Vue 风格指南规则](https://vuejs.org/v2/style-guide/#Single-instance-component-names-strongly-recommended)



**注意：此规则也适用于路由组件。**



------



### **紧密耦合组件命名**

[> 遵循官方 Vue 风格指南规则](https://vuejs.org/v2/style-guide/#Tightly-coupled-component-names-strongly-recommended)



------



### **组件命名单词顺序**

[> 遵循官方 Vue 风格指南规则](https://vuejs.org/v2/style-guide/#Order-of-words-in-component-names-strongly-recommended)



------



### **模板中的组件命名大小写**

**组件在单文件组件模板中应始终使用 PascalCase**。

```
# 错误示例
<mycomponent />
<myComponent />
# 正确示例
<MyComponent />
```

[> 官方 Vue 风格指南详细说明](https://vuejs.org/v2/style-guide/#Component-name-casing-in-templates-strongly-recommended)



------



### **自闭合组件**

**无内容的组件应自闭合（self-closing），在单文件组件、字符串模板和 JSX 中适用，但 DOM 模板中不要自闭合**。

```
# 错误示例
<MyComponent></MyComponent>
# 正确示例
<MyComponent />
```



------





### **完整单词组件名称**

[> 遵循官方 Vue 风格指南规则](https://vuejs.org/v2/style-guide/#Full-word-component-names-strongly-recommended)



------





### **避免在** v-for上使用v-if

**不要在同一个元素上同时使用 v-for 和 v-if。**

常见的两种情况：



1. 过滤列表项（如 v-for="user in users" v-if="user.isActive"），应改用计算属性返回过滤后的列表（如 activeUsers）。
2. 避免渲染整个列表（如 v-for="user in users" v-if="shouldShowUsers"），应将 v-if 移到父容器（如 ul、ol）上。

[> 官方 Vue 风格指南详细说明](https://vuejs.org/v2/style-guide/#Avoid-v-if-with-v-for-essential)

