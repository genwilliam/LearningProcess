package data_struct

import (
	"fmt"
)

// User 结构体
//
// 可以理解为把多个变量进行打包，
// 构成一个整体
//
// 也可以理解为是一种数据类型
type User struct {
	// 成员变量
	ID            int
	Name, address string
	Score         float64
}

// say 是结构体的方法
//
// 不能直接通过函数调用的方式进行使用,
// 需要实例化结构体才能使用
func (u User) say() {
	fmt.Println("hello", u.Name)
}

func StructDemo() {
	// 结构体里的数据可以不赋值
	// 默认是对应数据类型的零值
	// int : 0
	// bool : false
	// string : ""
	//
	// 你也可以省略ID，Name等字段，但是需要一一对应写，不能省略
	var u = User{ID: 100, Name: "william", address: "cn", Score: 90.2}
	fmt.Println(u)

	u.say()

	// 匿名结构体
	// 把type 变成var，
	// 就是把他当变量的方式
	//
	// 当你在一个函数里面需要结构体
	// 但是只需要提供给这个函数
	// 那么就可以用匿名结构体
	//
	// 匿名结构体student像变量一样，不能像User一样复用
	var student struct {
		name string
		age  int
	}
	student.name = "Peter"
	student.age = 35
	fmt.Println(student)

	u2 := &u // 取址符号，u2是User的指针类型 *User
	fmt.Println("u的地址", &u, "u2的地址", &u2)
	fmt.Println((*u2).Name)
	fmt.Println(u2.Name) // 自动解引用

	u3 := new(User) // nwe先创建空的结构体，再返回其指针 。 u3 是 *User类型
	u3.Name = "John"
	fmt.Println(u3.Name)
}

// Extend 实现类似继承的效果
//
// golang中没有继承的概念
func Extend() {
	type User struct {
		name string
		age  int
		// 如果要嵌套引用自己User，需要是指针类型
		// 指针的零值为nil
		// 否则会形成递归引用
		User *User
	}
	type Video struct {
		length int
		name   string
		//author User

		// 或者使用匿名成员
		User // 只有类型没有名称

	}
	u := User{name: "william", age: 18, User: nil}
	u1 := User{name: "william1", age: 19, User: &User{name: "fa"}}
	v := Video{length: 120, name: "peter", User: u}

	//fmt.Println(u)
	//fmt.Println(v)
	//fmt.Println(v.User.age)
	//fmt.Println(v.age)
	fmt.Println(u1)
	fmt.Printf("%v\n", v)
	fmt.Printf("%+v\n", v)
	fmt.Printf("%#v\n", v)
}
