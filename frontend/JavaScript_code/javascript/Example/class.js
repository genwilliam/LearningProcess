class Person {
    static bar = 'bar';

    sayHi() {
        console.log('this.bar:', this.bar);
        console.log('Person.bar:', Person.bar);
    }

}

const p = new Person();

// 实例不能访问静态属性
p.sayHi();
// 能通过类访问静态属性
console.log(Person.bar);