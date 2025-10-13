# **Monorepo 工程管理全攻略**

<p align="center">
  <img src="https://img.shields.io/badge/Keep-Learning-blue?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Stay-Curious-yellow?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Share-Knowledge-success?style=for-the-badge" />
</p>

如果你正在管理一个包含多个子项目（前端、后端、组件库、工具包等）的工程，那么这篇文档可以让你少踩很多坑。

---

## **一、Multirepo vs Monorepo**

在开始之前，我们得先分清这俩概念。

| **模式**      | **说明**               | **优点**                     | **缺点**                     |
| ------------- | ---------------------- | ---------------------------- | ---------------------------- |
| **Multirepo** | 每个项目独立一个仓库   | 权限清晰、简单               | 项目间依赖难管理、版本不一致 |
| **Monorepo**  | 所有项目放在同一个仓库 | 管理统一、共享依赖、便于重构 | CI/CD 复杂、构建体量大       |

简单说：

> **Multirepo 是“各自为政”**，而 **Monorepo 是“集中治理”**。

![image-20251012142505709](https://raw.githubusercontent.com/genwilliam/picgo_img/main/img/image-20251012142505709.png)

---

## **二、Monorepo 管理工具一览**

目前主流的管理工具有：

- **pnpm** — 简单、快速、原生支持 monorepo
- npm
- Yarn
- ⚙Lerna
- Nx
- Turborepo
- Rush

> 推荐使用 **pnpm**，因为它原生支持 workspace，不需要额外插件。

---

## **三、用 pnpm 初始化 Monorepo**

新建一个 workspace 配置文件：

```
touch pnpm-workspace.yaml
```

内容如下：

```
# pnpm-workspace.yaml
packages:
  - "packages/*"
  - "apps/*"
```

这就定义了两个工作区：

- packages/：放公共库、组件库、工具函数等；
- apps/：放具体应用，比如前端、后端。

---

### **常用命令**

执行工程级命令（在根目录执行）：

```
pnpm --workspace-root <command>
# 或
pnpm -w <command>
```

执行子包命令：

```
pnpm -C apps/frontend dev
```

或直接进入目录执行：

```
cd apps/frontend && pnpm dev
```

> 💡 **Tips**：

> -C 参数让你不用切目录，直接在根项目里跨子包执行命令。

---

## **四、环境版本锁定**

为了避免团队中出现“我这能跑、你那报错”的情况，我们需要**锁定 Node 环境版本**。

```
// package.json
"engines": {
  "node": ">=22.14.0",
  "npm": ">=10.9.2",
  "pnpm": ">=10.15.1"
}
```

并在 .npmrc 中开启强制校验：

```
engine-strict=true
```

这样，当有人使用旧版本 Node 时，pnpm 会直接拒绝运行。

---

## **五、TypeScript 项目配置**

安装 TypeScript 依赖：

```
pnpm -Dw add typescript @types/node
```

创建基础配置文件：

```
touch tsconfig.json
```

### ** 根配置 tsconfig.json**

```
{
  "compilerOptions": {
    "baseUrl": ".",
    "module": "esnext",
    "target": "esnext",
    "types": [],
    "lib": ["esnext"],
    "sourceMap": true,
    "declaration": true,
    "strict": true,
    "skipLibCheck": true,
    "moduleResolution": "bundler",
    "isolatedModules": true
  },
  "exclude": ["node_modules", "dist"]
}
```

### **子项目继承配置**

后端：

```
// apps/backend/tsconfig.json
{
  "extends": "../../tsconfig.json",
  "compilerOptions": {
    "types": ["node"],
    "lib": ["esnext"]
  },
  "include": ["src"]
}
```

前端：

```
// apps/frontend/tsconfig.json
{
  "extends": "../../tsconfig.json",
  "compilerOptions": {
    "types": ["node"],
    "lib": ["esnext", "DOM"]
  },
  "include": ["src"]
}
```

> ✅ **为什么要继承？**

> 这样所有子项目都能共享一份基础规则，既统一又可自定义扩展。

---

## **六、代码风格与质量检查**

一致的代码风格可以大大减少团队摩擦，尤其在 monorepo 这种多人协作场景中。

### **✨ Prettier —— 自动格式化**

安装：

```
pnpm -Dw add prettier
```

配置文件：

```
touch prettier.config.js
export default {
  printWidth: 120,
  tabWidth: 2,
  semi: true,
  singleQuote: false,
  trailingComma: "none",
  bracketSpacing: true,
  arrowParens: "avoid",
  endOfLine: "auto"
};
```

忽略文件：

```
touch .prettierignore
dist
public
node_modules
pnpm-lock.yaml
```

命令：

```
"scripts": {
  "lint:prettier": "prettier --write \"**/*.{js,ts,vue,md,json,css,html}\""
}
```

---

### **ESLint —— 语法规则检查**

安装：

```
pnpm -Dw add eslint @eslint/js globals typescript-eslint eslint-plugin-prettier eslint-config-prettier eslint-plugin-vue
```

配置：

```
touch eslint.config.js
import { defineConfig } from "eslint/config";
import eslint from "@eslint/js";
import tseslint from "typescript-eslint";
import eslintPluginPrettier from "eslint-plugin-prettier";
import eslintPluginVue from "eslint-plugin-vue";
import globals from "globals";
import eslintConfigPrettier from "eslint-config-prettier/flat";

export default defineConfig(
  {
    ignores: ["**/dist/**", "**/node_modules/**"],
    extends: [eslint.configs.recommended, ...tseslint.configs.recommended, eslintConfigPrettier],
    plugins: { prettier: eslintPluginPrettier },
    languageOptions: {
      ecmaVersion: "latest",
      parser: tseslint.parser
    }
  },
  {
    files: ["apps/frontend/**/*.{ts,vue}"],
    extends: [...eslintPluginVue.configs["flat/recommended"], eslintConfigPrettier],
    languageOptions: { globals: globals.browser }
  },
  {
    files: ["apps/backend/**/*.{ts,js}"],
    languageOptions: { globals: globals.node }
  }
);
```

命令：

```
"scripts": {
  "lint:eslint": "eslint"
}
```

---

### **拼写检查 —— Code Spell Checker**

安装：

```
pnpm -Dw add cspell @cspell/dict-lorem-ipsum
```

配置文件：

```
{
  "import": ["@cspell/dict-lorem-ipsum/cspell-ext.json"],
  "ignorePaths": ["**/node_modules/**", "**/dist/**"],
  "dictionaryDefinitions": [
    { "name": "custom-dictionary", "path": "./.cspell/custom-dictionary.txt", "addWords": true }
  ],
  "dictionaries": ["custom-dictionary"]
}
```

命令：

```
"lint:spellcheck": "cspell lint \"(packages|apps)/**/*.{js,ts,vue,md}\""
```

---

## **七、Git 提交规范**

统一的提交信息能让项目历史清晰可读。

### **🪄 Commitizen + cz-git**

安装：

```
pnpm -Dw add @commitlint/cli @commitlint/config-conventional commitizen cz-git
```

配置：

```
"scripts": {
  "commit": "git-cz"
},
"config": {
  "commitizen": {
    "path": "node_modules/cz-git"
  }
}
```

自定义规则（commitlint.config.js）：

```
export default {
  extends: ["@commitlint/config-conventional"],
  rules: {
    "subject-empty": [2, "never"],
    "type-enum": [2, "always", ["feat", "fix", "docs", "style", "refactor", "test", "chore"]]
  }
};
```

> 🧩 效果：

> 执行 pnpm commit 后，会弹出一个交互式 CLI，让你优雅地填写 commit 信息。

---

### **🪝 Husky + Lint-staged**

自动在提交前检查代码。

安装：

```
pnpm -Dw add husky lint-staged
pnpx husky init
```

配置 .husky/pre-commit：

```
#!/usr/bin/env sh
pnpm lint:prettier && pnpm lint:eslint && pnpm lint:spellcheck
```

配置 .lintstagedrc.js：

```
export default {
  "*.{js,ts,vue,md}": ["prettier --write", "eslint"],
  "*.{js,ts,vue,html,md}": ["cspell lint"]
};
```

---

## **八、公共库打包（Rollup）**

安装依赖：

```
pnpm -Dw add rollup @rollup/plugin-node-resolve @rollup/plugin-commonjs rollup-plugin-typescript2 @rollup/plugin-terser @vitejs/plugin-vue rollup-plugin-postcss
```

这些插件的作用：

| **插件**                    | **作用**           |
| --------------------------- | ------------------ |
| @rollup/plugin-node-resolve | 解析 node_modules  |
| @rollup/plugin-commonjs     | 支持 CommonJS 模块 |
| rollup-plugin-typescript2   | 编译 TypeScript    |
| @rollup/plugin-terser       | 压缩、混淆         |
| @vitejs/plugin-vue          | 支持 Vue SFC       |
| rollup-plugin-postcss       | 处理 CSS           |

---

## **九、子包间依赖**

pnpm 的 workspace 支持子包直接互相引用：

```
{
  "foo": "workspace:*",
  "bar": "workspace:^1.0.0"
}
```

> 💡 这意味着你不需要发布到 npm 就能在项目间共享模块。

---

## **十、单元测试（Vitest）**

安装：

```
pnpm -Dw add vitest @vitest/browser vitest-browser-vue vue
```

命令：

```
"scripts": {
  "test": "vitest"
}
```

在 tsconfig.json 中增加：

```
"types": ["vitest/globals", "@vitest/browser/matchers"]
```

---

## **十一、发布？休息一下**

这里其实就是配置 CI/CD、版本号、打包产物上传等。

但是嘛……先喝口咖啡 ☕️，我们下一章再聊。

---

## **总结**

| **环节** | **工具**                    | **作用**       |
| -------- | --------------------------- | -------------- |
| 管理     | pnpm                        | 工作区管理     |
| 代码质量 | Prettier / ESLint / CSpell  | 统一风格与规范 |
| 提交规范 | Commitizen / cz-git / Husky | 规范化提交     |
| 构建     | Rollup                      | 打包公共库     |
| 测试     | Vitest                      | 单元测试       |
| 发布     | CI/CD                       | 自动化流程     |

---

> Monorepo 的魅力不只是“放一起”，而是“统一、规范、自动化”。

> 当你真正掌控它后，你会发现：

> **整个工程像一个有机体一样运行。**
