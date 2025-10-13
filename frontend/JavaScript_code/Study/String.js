const str = "The full name of China is the People's Republic of China.";

let of = str.indexOf("China");
console.log("China出现第一次的索引为" + of)

of = str.lastIndexOf("China");  // 方法向后进行检索（从尾到头）
console.log("China出现最后一次的索引为" + of)

let n = str.search("China");  //  方法搜索特定值的字符串，并返回匹配的位置
console.log("China出现的位置为" + n)

let n2 = str.match(/China/g);
console.log("China出现的次数为" + n2.length)

let length = str.length;
console.log("字符串的长度为" + length)

let str2 = str.slice(0, 4);  // slice提取字符串的某个部分并在新字符串中返回被提取的部分
console.log(str2)

let str3 = str.substring(0, 4);
/*substring() 类似于 slice()。
不同之处在于 substring() 无法接受负的索引。*/
console.log(str3)

let trim = str.trim();  // trim() 方法删除字符串两端的空白符
console.log(trim)

// charAt() 方法返回指定位置的字符
let char = str.charAt(0);
console.log(char)

// charCodeAt() 方法返回指定位置的字符的 Unicode 编码
let char2 = str.charCodeAt(0);
console.log(char2)

// matchAll() 方法返回一个迭代器，其中包含将字符串与字符串（或正则表达式）匹配的结果。
let str4 = "The full name of China is the People's Republic of China.";
let n3 = str4.matchAll("China");
for (let item of n3) {
    console.log(item)
}

// includes() 方法用于判断一个字符串是否包含在另一个字符串中（不区分大小写）
let text1 = "Hello world, welcome to the universe.";
text1.includes("world");

// startsWith() 方法用于判断一个字符串是否在另一个字符串的开头
let text2 = "Hello world, welcome to the universe.";
text2.startsWith("Hello");
let text3 = "Hello world, welcome to the universe.";
text3.startsWith("world", 6)

// endsWith() 方法用于判断一个字符串是否在另一个字符串的结尾
let text4 = "Hello world, welcome to the universe.";
text4.endsWith("universe.");



// 模板字符串
let str5 = `Hello world, welcome to the universe.`;
// 使用${...}语法
let str6 = `Hello world, welcome to the ${str5}`;
console.log(str6)

// 模板字符串嵌入表达式
let price = 10;
let VAT = 0.25;
let total = `Total: ${(price * (1 + VAT)).toFixed(2)}`;
console.log(total)







