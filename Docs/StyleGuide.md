# Fuse C++ Style Guide

**TODO**

- Apart from the exceptions below, all identifiers and source file names are `PascalCase`.

```c++
struct BaseColor;
class Color;
namespace FileSystem = std::filesystem; 
```

- Private methods have a `Private` prefix.

```c++
class Color {
public:
    Color();
    
private:
    void PrivateCreateColor();
};
```

- Class members that aren't methods have an `m_` prefix.

```c++
class Color {
public:
    float m_Red;
    float m_Green;
    float m_Blue;
};
```

- Global variables have a `g_` prefix.

```c++
const char* g_Name = "Danny Carey";

int main() {
    printf("Hello, %s\n", g_Name);
    return 0;
}
```

- Pointer asterisks `*` and reference symbols `&` **append the type**.
- Arguments are `camelCase`.

```c++
int Add(const int& valA, const int& valB, int* outVal) {
    *outVal = valA + valB;
}
```

- Global constants and `defines` are `UPPER_CASE`.

```c++
#define CHECK_RESULT(X) SUCCEEDED((X))
static constexpr int WINDOW_WIDTH = 800;
```

- Interfaces are prefixed with `I`, traits with `T` and enums with `E`.
  Structs prefixed with `F` are optional.

```c++
enum EStrokeType;
class TSingleChild;
class IObject;
struct FColor; // or Color
```

- Class headers and definitions are placed in the same directory.

```
▼ Lib
  - Color.h
  - Color.cpp
```

- Header files whose primary purpose is to provide inline functions are saved with the `.inl` extension.
- Interfaces are typically saved in their own subdirectory.

```
▼ Lib
  ▼ Interfaces
    - Object.h
  - Color.h
  - Color.cpp
  - Helpers.inl
```

- All classes that implement an interface should be marked `final`.

```c++
class PushButton final : public IComponent {};
```

- `constexpr` variables have a `k` prefix, no underscore.

```c++
static constexpr unsigned kMouseLeft = 0;
```