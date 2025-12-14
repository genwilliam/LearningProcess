class Person1 {
  /**
   * @param {string} name
   * @param {number} age
   */
  constructor(name, age) {
    // 始终添加名为 constructor() 的方法
    this.name = name;
    this.age = age;
  }
}

let pe = new Person1("william", 20);

console.log(pe.name);
console.log(pe.age);

// --------------

class Animal {
  /**
   *
   * @param {string} name
   */
  constructor(name) {
    this.name = name;
  }
}

class Dog extends Animal {
  /**
   *
   * @param {string} name
   * @param {number} year
   */
  constructor(name, year) {
    super(name); // 必须调用父类 constructor
    this.year = year;
  }
}

let dog = new Dog("dog", 3);

console.log(dog);

// ------------------

class Car {
  /**
   *
   * @param {string} name
   * @param {number} year
   */
  constructor(name, year) {
    this.name = name;
    this.year = year;
  }
  age() {
    let date = new Date();
    return date.getFullYear() - this.year;
  }
}

let myCar = new Car("Ford", 2014);
console.log("My car is " + myCar.age() + " years old.");
