function isObject(val) {
    return val !== null && typeof val === 'object';
}

function equals(obj1, obj2) {
    let keys1 = Object.keys(obj1);
    let keys2 = Object.keys(obj2);
    let isSame = true;
    keys1.forEach((k) => {
        if (!keys2.includes(k)) {
            isSame = false;
        }
    });
    if (!isSame) {
        return false;
    }
    if (keys1.length !== keys2.length) {
        return false;
    }
    if (keys1.length !== keys2.length) {
        return false;
    }
    // 正式逻辑
    for (let i = 0; i < keys1.length; i++) {
        const k = keys1[i];
        if (!isObject(obj1[k]) && !isObject(obj2[k])) {
            // 注意：这里有逻辑
            return obj1[k] === obj2[k];
        } else if (
            (isObject(obj1[k]) && !isObject(obj2[k])) ||
            (!isObject(obj1[k]) && isObject(obj2[k]))
        ) {
            return false;
        } else {
            return equals(obj1[k], obj2[k]);
        }
    }
}

// 数组去重
function uniqueArray(arr) {
    let result = [];
    let primitives = [];
    let objects = [];
    arr.forEach((item) => {
        if (isObject(item)) {
            objects.push(item);
        } else {
            primitives.push(item);
        }
    });
    primitives = primitives.filter((item, index) => {
        return index === primitives.indexOf(item);
    });
    result.push(...primitives);
    // 处理主逻辑：处理引用对象类型
    objects = objects.filter((obj, index) => {
        return index === objects.findIndex((item) => equals(obj, item));

    });
    result.push(...objects);
    return result;
}

const arr = [{ a: 1, b: 2 }, { b: 2, a: 1 }, 1, 1, 3, 4];
const r = uniqueArray(arr);
console.log(r);
