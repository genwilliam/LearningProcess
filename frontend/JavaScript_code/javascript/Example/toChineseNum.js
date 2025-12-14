/**
 * 数字转中文
 * @param {number} num 万亿以下的整数
 */
function toChineseNum(num) {
  const units = ["", "十", "百", "千", "万", "亿"];
  const digits = "零一二三四五六七八九".split("");
  let result = "";
  let unitIndex = 0;

  while (num > 0) {
    const digit = num % 10;
    if (digit > 0) {
      result = digits[digit] + units[unitIndex] + result;
    } else if (result && result[0] !== digits[0]) {
      result = digits[0] + result;
    }
    num = Math.floor(num / 10);
    unitIndex++;
  }

  return result;
}
console.log(toChineseNum(1234567890));
