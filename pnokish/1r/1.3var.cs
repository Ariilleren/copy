using System;

namespace Variant3_Car_Simple
{
    public class Car
    {
        private string make;
        private string model;
        private int year;
        private bool engineStarted;

        public string Make
        {
            get { return make; }
            set { make = value; }
        }

        public string Model
        {
            get { return model; }
            set { model = value; }
        }

        public int Year
        {
            get { return year; }
            set { year = value; }
        }

        public string EngineStatus
        {
            get { return engineStarted ? "Запущен" : "Заглушен"; }
        }

        // ВСЕГО ОДИН КОНСТРУКТОР!
        public Car(string make = "Неизвестно", string model = "Неизвестно", int year = 2000)
        {
            this.make = make;
            this.model = model;
            this.year = year;
            this.engineStarted = false;
        }

        // Метод запуска двигателя
        public void StartEngine()
        {
            engineStarted = true;
            Console.WriteLine($"Двигатель {make} {model} запущен!");
        }

        // Метод вывода информации
        public void PrintInfo()
        {
            Console.WriteLine($"{make} {model}, {year} г. - {EngineStatus}");
        }
    }

    public class CarList
    {
        private Car[] cars;
        private int count;

        public CarList(int size = 10)
        {
            cars = new Car[size];
            count = 0;
        }

        // Добавление автомобиля
        public void Add(Car car)
        {
            if (count < cars.Length)
            {
                cars[count] = car;
                count++;
                Console.WriteLine($"Добавлен: {car.Make} {car.Model}");
            }
        }

        // Добавление с клавиатуры (здесь, а не в конструкторе!)
        public void AddFromKeyboard()
        {
            Console.WriteLine("Введите данные автомобиля:");
            
            Console.Write("Марка: ");
            string make = Console.ReadLine();
            
            Console.Write("Модель: ");
            string model = Console.ReadLine();
            
            Console.Write("Год: ");
            int year = int.Parse(Console.ReadLine());
            
            // Используем ЕДИНСТВЕННЫЙ конструктор
            Car newCar = new Car(make, model, year);
            Add(newCar);
        }

        public void PrintAll()
        {
            Console.WriteLine("\nСписок автомобилей:");
            for (int i = 0; i < count; i++)
            {
                Console.Write($"[{i}] ");
                cars[i].PrintInfo();
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            CarList list = new CarList();
            
            // Используем ОДИН И ТОТ ЖЕ конструктор по-разному
            Car car1 = new Car();                          // Без параметров
            Car car2 = new Car("Toyota", "Camry", 2020);   // С параметрами
            Car car3 = new Car("BMW", "X5");               // Год будет 2000 (по умолчанию)
            
            list.Add(car1);
            list.Add(car2);
            list.Add(car3);
            
            list.PrintAll();
            
            // Ввод с клавиатуры
            list.AddFromKeyboard();
            list.PrintAll();
            
            Console.ReadKey();
        }
    }
}