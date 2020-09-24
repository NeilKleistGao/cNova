# cNova
A light script language embedded in C++

## usage
### define and use local variables
```c++
auto x = 10; // int
auto y = 1.2; // float
auto z = "hello"; // string
auto w = true; // bool
auto p = [1, 2, 3]; // array
auto q = {}; // dictionary
```

cNova is a weak-type language:
```c++
auto x = 10;
x = "wryyyy";
```

You can use these variables in c style way:
```c++
x = 10 + 20;
y = sin(3.14); // use math lib
z = strlen("QWQ"); // use string lib
```

### condition and loop
```c++
if (x == 10) {
    y = true;
}
else if (x == 20) {
    y = false;
}
else {
    y = nullptr;
}

```c++
auto i = 0;
while (i < 10) {
    i++;
}
```

### input and output
In cNova, all codes in a file is considered as a function. So function parameters are all input data you can get, and you can use keyword `return` to return a value:
```c++
extern x, y, z;
return x + y + z;
```

### closure
You can use `this` to access member variables or member function in current class:
```c++
auto player = this;
player.HP -= 10;

if (player.HP <= 0) {
    player.die();
}
```

## an example
```c++
// a poison state script
extern last_time;

auto player = this;
player.HP -= 10;
last_time--;

if (player.HP <= 0) {
    last_time = 0;
}

return last_time == 0;
```