const obj = {
    name: 'John',
    greet: () => {
        console.log(`${this.name}`);
    }
}
obj.greet();  // Output: undefined

console.log(obj.greet.__proto__ === Function.prototype);  // Output: true


x = 3;
console.log(x);
var x;