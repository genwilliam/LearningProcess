// 模块仅适用于 HTTP(s) 协议
// 通过 file:// 协议打开的网页无法使用导入/导出

import { name, age } from "./person.js";
import message from "./message.js";

console.log(message());

console.log(name);
console.log(age);
