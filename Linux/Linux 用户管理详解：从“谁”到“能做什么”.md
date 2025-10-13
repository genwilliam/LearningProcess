# **Linux 用户管理详解：从“谁”到“能做什么”**





在 Linux 里，一切都讲究“权限”。而权限的基础，就是**用户（user）**。

系统通过用户来区分“谁能做什么”，这既是安全机制的核心，也是多用户系统设计的精髓。



想象 Linux 是一栋大楼：

每个用户都有自己的房间（home 目录），自己的钥匙（密码），

有的人只能待在自己的房间里，有的人则能拿着万能钥匙（root）进出任何地方。

用户管理，就是在管理这栋楼的住户和他们的权限。



------





## **一、用户和组的基本概念**







### **1. 用户（User）**





Linux 是多用户操作系统，这意味着多个用户可以共享同一台机器而互不干扰。

用户分为三类：



- **超级用户（root）**：拥有系统的最高权限，可以做任何事情，包括删除整个系统。UID 是 0。
- **系统用户（system user）**：用于运行系统服务（比如 www-data、mysql），它们没有登录权限。
- **普通用户（regular user）**：我们日常登录使用的账户，比如 william。





每个用户在系统中都有一个唯一的 UID（用户 ID）。

系统通过 UID 而不是用户名来识别身份。



------





### **2. 用户组（Group）**





组就像“部门”。

多个用户可以属于同一个组，从而共享一些文件或目录的访问权限。

每个组都有唯一的 GID（组 ID）。



- **主组（Primary Group）**：每个用户必须有一个主组，一般在创建用户时自动生成。
- **附加组（Secondary Group）**：用户可以加入多个附加组，获得额外权限。





举个例子：

假设你有两个用户 alice 和 bob，都属于组 dev。

那么 /project 目录的所有者组设置为 dev，两个人都可以访问。



------





## **二、用户信息文件**





Linux 用户和组的信息都存储在几个系统文件中：

| **文件路径** | **说明**                                                     |
| ------------ | ------------------------------------------------------------ |
| /etc/passwd  | 存储用户的基本信息（用户名、UID、主组ID、home目录、登录shell等） |
| /etc/shadow  | 存储加密后的用户密码及密码策略                               |
| /etc/group   | 存储组信息（组名、GID、成员）                                |

来看个例子：

```
$ cat /etc/passwd | grep william
william:x:1000:1000:William,,,:/home/william:/bin/bash
```

每个字段的含义如下：



1. 用户名：william
2. 密码占位符：x（真实密码在 /etc/shadow）
3. 用户 ID（UID）：1000
4. 组 ID（GID）：1000
5. 用户描述：William
6. 主目录：/home/william
7. 登录 shell：/bin/bash





------





## **三、常用的用户管理命令**







### **1. 创建用户**



```
sudo useradd -m -s /bin/bash william
```

参数解释：



- -m：自动创建 home 目录
- -s：指定登录 shell





然后设置密码：

```
sudo passwd william
```



------





### **2. 修改用户信息**



```
sudo usermod -aG sudo william
```



- -aG：将用户添加到附加组（这里是 sudo 组，获得管理权限）





也可以修改 home 目录或 shell：

```
sudo usermod -d /newhome/william william
sudo usermod -s /bin/zsh william
```



------





### **3. 删除用户**



```
sudo userdel -r william
```



- -r：连同 home 目录一并删除。





------





### **4. 创建组与管理组**



```
sudo groupadd dev
sudo gpasswd -a william dev
sudo gpasswd -d william dev
```



------





## **四、root 用户与 sudo**





在 Linux 中，root 用户几乎可以做任何事。

但让每个用户都用 root 登录，显然是不安全的。



于是，Linux 设计了 sudo 机制。

通过 sudo，普通用户可以“临时借用” root 权限执行某些命令，而不必直接切换到 root 身份。

```
sudo apt update
```

如果你希望某个用户能使用 sudo，需要将其加入 sudo 组：

```
sudo usermod -aG sudo username
```

sudo 的行为由 /etc/sudoers 文件定义。

你可以通过 visudo 安全地编辑它。



------





## **五、切换用户与身份验证**





切换用户：

```
su - username
```

带上 - 表示加载目标用户的环境。



查看当前用户：

```
whoami
```

查看当前登录的所有用户：

```
who
```

查看用户活动：

```
last
```



------





## **六、密码与安全策略**





密码信息保存在 /etc/shadow 中，它只对 root 可读。

示例：

```
william:$6$VvG...:19500:0:99999:7:::
```

字段分别表示：



1. 用户名
2. 加密后的密码
3. 上次修改日期
4. 最小/最大密码期限
5. 警告时间等





你可以用 chage 命令管理密码策略：

```
sudo chage -l william
sudo chage -M 90 william  # 密码有效期90天
```



------





## **七、小结**



| **概念**     | **描述**                       |
| ------------ | ------------------------------ |
| 用户（user） | 系统中的个体，拥有 UID 和 home |
| 组（group）  | 权限共享机制                   |
| root 用户    | 最高权限账户                   |
| sudo         | 临时以 root 身份执行命令       |
| /etc/passwd  | 用户信息                       |
| /etc/shadow  | 密码信息                       |
| /etc/group   | 组信息                         |



------





## **最后的思考**



Linux 的用户系统看似复杂，其实核心逻辑很清晰：



> “一切都是为了安全地管理权限。”



通过用户和组，系统能精细地控制资源访问；

通过 sudo，普通用户能有限地行使管理权。



这套体系让 Linux 既灵活又稳健。

理解用户管理，不仅是系统管理的第一步，也是理解 Linux 安全模型的起点。