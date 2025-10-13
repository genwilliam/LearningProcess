const person = {
    firstName: "Bill",
    lastName: "Gates",
    id: 678,
    fullName: function () {
        return this.firstName + " " + this.lastName;
    }
};

console.log(person.fullName())
console.log(person.fullName.call(person))