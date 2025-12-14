Array.prototype.flatMap = function (callback, thisArg) {
  if (this == null) {
    throw new TypeError("Array.prototype.flatMap called on null or undefined");
  }
  if (typeof callback !== "function") {
    throw new TypeError(callback + " is not a function");
  }

  const result = [];
  const array = Object(this);
  const len = array.length >>> 0;

  for (let i = 0; i < len; i++) {
    if (i in array) {
      const mappedValue = callback.call(thisArg, array[i], i, array);
      if (Array.isArray(mappedValue)) {
        for (let j = 0; j < mappedValue.length; j++) {
          if (j in mappedValue) {
            result.push(mappedValue[j]);
          }
        }
      } else {
        result.push(mappedValue);
      }
    }
  }

  return result;
};

// 示例用法
const array = [1, 2, 3];
const result = array.flatMap((x) => [x, x * 2]);
console.log(result); // 输出: [1, 2, 2, 4, 3, 6]
