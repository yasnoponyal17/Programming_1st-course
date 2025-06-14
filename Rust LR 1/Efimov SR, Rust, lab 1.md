# Лабораторная работа 1
## Тема работы: Введение в Rust
### Задача 1
#### Постановка задачи
Напишите программу, которая запрашивает у пользователя имя и выводит на экран приветственное сообщение с использованием этого имени.
#### Математическая модель
Отсутствует
#### Список идентификаторов
| Имя | Тип | Смысл |
| - | - | - |
| name | String | Имя |

#### Код программы
```Rust
use std::io;

fn main() {
    println!("Введите ваше имя: ");
    let mut name = String::new();
    io::stdin()
        .read_line(&mut name)
        .expect("Ошибка при чтении строки");
    
    println!("Привет, {}", name);
}
```
#### Результат работы
![Task 1](images/rust%201.png)

### Задача 2
#### Постановка задачи
Создайте переменную типа целое беззнаковое число и выведите ее значение на экран. Явно
укажите тип переменной. Затем измените значение переменной и снова выведите его.
#### Математическая модель
Отсутствует
#### Список идентификаторов
| Имя | Тип | Смысл |
| - | - | - |
| number | u32 | Число |

#### Код программы
```Rust
fn main() {
    let mut number: u32 = 42;
    println!("Начальное значение: {}", number);
    
    number = 52;
    println!("Новое значение: {}", number);
}
```
#### Результат работы
![Task 2](images/rust%202.png)

### Задача 3
#### Постановка задачи
Напишите функцию, которая принимает строку и возвращает ее длину (количество символов).
Затем вызовите эту функцию с различными строками.
#### Математическая модель
Отсутствует
#### Список идентификаторов
| Имя | Тип | Смысл |
| - | - | - |
| str1 | String | Строка 1 |
| str2 | String | Строка 2 |
| str3 | String | Строка 3 |
#### Код программы
```Rust
fn main() {
    let str1 = "Efimov Sergei";
    let str2 = "Rust";
    let str3 = "";
    
    println!("Длина строки '{}': {}", str1, get_length(str1));
    println!("Длина строки '{}': {}", str2, get_length(str2));
    println!("Длина строки '{}': {}", str3, get_length(str3));
}

fn get_length(s: &str) -> usize {
    s.len()
}
```
#### Результат работы
![Task 3](images/rust%203.png)

### Задача 4
#### Постановка задачи
Задайте структуру Car с полями brand, model и year, и создайте несколько экземпляров этой
структуры. Выведите информацию о каждой машине на экран.
#### Математическая модель
Отсутствует
#### Список идентификаторов
| Имя | Тип | Смысл |
| - | - | - |
| brand | String | Бренд машины |
| model | String | Модель машины |
| year | u32 | Год выпуска машины |

#### Код программы
```Rust
struct Car {
    brand: String,
    model: String,
    year: u32,
}

fn main() {
    let car1 = Car {
        brand: String::from("Mercedes-Benz"),
        model: String::from("E63"),
        year: 2014,
    };
    
    let car2 = Car {
        brand: String::from("Lamborghini"),
        model: String::from("Urus"),
        year: 2025,
    };
    
    let car3 = Car {
        brand: String::from("Bugatti"),
        model: String::from("Chiron"),
        year: 2016,
    };
    
    println!("Машина 1: {} {}, год выпуска: {}", car1.brand, car1.model, car1.year);
    println!("Машина 2: {} {}, год выпуска: {}", car2.brand, car2.model, car2.year);
    println!("Машина 3: {} {}, год выпуска: {}", car3.brand, car3.model, car3.year);
}
```
#### Результат работы
![Task 4](images/rust%204.png)

### Задача 5
#### Постановка задачи
Напишите программу, которая запрашивает у пользователя число 𝑁 и выводит на экран 𝑁­ное
число Фибоначчи. Используйте рекурсию для решения этой задачи.
#### Математическая модель

$$
F_{n} = F_{n-1} + F_{n-2}
$$

#### Список идентификаторов
#### Код программы
```Rust
use std::io;

fn main() -> io::Result<()> {
    println!("Введите число N для вычисления N-го числа Фибоначчи: ");
    
    let mut input = String::new();
    io::stdin().read_line(&mut input)?;
    
    let n: u32 = input
        .trim()
        .parse()
        .expect("Пожалуйста, введите положительное целое число!");
    
    let fib = fibonacci(n);
    println!("{} число Фибоначчи: {}", n, fib);
    Ok(())
}

fn fibonacci(n: u32) -> u64 {
    if n == 0 {
        0
    } else if n == 1 {
        1
    } else {
        fibonacci(n - 1) + fibonacci(n - 2)
    }
}
```
#### Результат работы
![Task 5](images/rust%205.png)

### Задача 6
#### Постановка задачи
Реализуйте перечисление DayOfWeek для дней недели. Напишите функцию, которая принимает
день недели и возвращает следующий день. Обработайте случаи перехода на следующий день
недели, если текущий день – воскресенье.
#### Математическая модель
Отсутствует
#### Список идентификаторов
#### Код программы
```Rust
use std::io;

#[derive(Debug)]
enum DayOfWeek {
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday,
}

fn next_day(day: &DayOfWeek) -> DayOfWeek {
    match day {
        DayOfWeek::Monday => DayOfWeek::Tuesday,
        DayOfWeek::Tuesday => DayOfWeek::Wednesday,
        DayOfWeek::Wednesday => DayOfWeek::Thursday,
        DayOfWeek::Thursday => DayOfWeek::Friday,
        DayOfWeek::Friday => DayOfWeek::Saturday,
        DayOfWeek::Saturday => DayOfWeek::Sunday,
        DayOfWeek::Sunday => DayOfWeek::Monday,
    }
}

fn main() -> io::Result<()> {
    println!("Введите день недели на английском (пример: Monday): ");
    let mut input = String::new();
    io::stdin().read_line(&mut input)?;
    
    let day = match input.trim().to_lowercase().as_str() {
        "monday" => DayOfWeek::Monday,
        "tuesday" => DayOfWeek::Tuesday,
        "wednesday" => DayOfWeek::Wednesday,
        "thursday" => DayOfWeek::Thursday,
        "friday" => DayOfWeek::Friday,
        "saturday" => DayOfWeek::Saturday,
        "sunday" => DayOfWeek::Sunday,
        _ => {
            println!("Ошибка: введите корректный день недели!");
            return Ok(());
        }
    };
    
    let next = next_day(&day);
    println!("Текущий день: {:?}", day);
    println!("Следующий день: {:?}", next);
    
    Ok(())
}
```
#### Результат работы
![Task 6](images/rust%206.png)

### Задача 7
#### Постановка задачи
Создайте структуру Product с полями name, price и category, а также перечисление (enum)
Category для категорий товаров. Напишите метод для вывода информации о продукте и
ассоциированную функцию для подсчета общей суммы товаров в заданной категории из
массива продуктов.
#### Математическая модель
#### Список идентификаторов
#### Код программы
#### Результат работы

### Задача 8
#### Постановка задачи
Создайте структуру Employee с полями name, position, salary, а также перечисление
Position для должностей сотрудников. Напишите функцию, которая принимает вектор
сотрудников и возвращает вектор сотрудников заданной должности.
#### Математическая модель
Отсуствует
#### Список идентификаторов
#### Код программы
#### Результат работы

### Ефимов Сергей Робертович, 1 курс, ИВТ-2, подгруппа 3