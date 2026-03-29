using System;
namespace Var3
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
        public Car(string make = "?", string model = "?", int year = 2000)
        {
            this.make = make ?? "?";      
            this.model = model ?? "?";    
            this.year = year;
            this.engineStarted = false;
        }
        public void StartEngine()
        {
            engineStarted = true;
            Console.WriteLine($"Двигатель {make} {model} запущен!");
        }
        public void PrintInfo()
        {
            Console.WriteLine($"{make} {model}, {year} г. - {EngineStatus}");
        }
    }

    public class CarList
    {
        private Car[] cars;
        private int count;
        public CarList(int size = 15)
        {
            cars = new Car[size];
            count = 0;
        }
        public int Count
        {
            get { return count; }
        }

        public void Add(Car car)
        {   if (count == 15){Console.WriteLine("Списк полон"); return;}

            cars[count] = car;
            count++;
            Console.WriteLine($"Добавлен: {car.Make} {car.Model}");
        }

        public void SearchByMake(string searchMake)
        {
            if (string.IsNullOrEmpty(searchMake))
            {
                Console.WriteLine("Марка не указана!");
                return;
            }

            bool found = false;

            for (int i = 0; i < count; i++)
            {
                if (cars[i].Make.Equals(searchMake, StringComparison.OrdinalIgnoreCase))
                {
                    Console.Write($"  Найден [{i}]: ");
                    cars[i].PrintInfo();
                    found = true;
                }
            }

            if (!found)
            {
                Console.WriteLine($"  Автомобили марки '{searchMake}' не найдены.");
            }
        }

        public void DeleteByMake(string searchMake)
        {            
            int indexToDelete = -1;
            for (int i = 0; i < count; i++)
            {
                if (cars[i].Make.Equals(searchMake, StringComparison.OrdinalIgnoreCase))
                {
                    indexToDelete = i;
                    break;
                }
            }

            if (indexToDelete != -1)
            {
                string deletedCar = $"{cars[indexToDelete].Make} {cars[indexToDelete].Model}";

                for (int i = indexToDelete; i < count - 1; i++)
                {
                    cars[i] = cars[i + 1];
                }
                count--;
                cars[count] = null;
            }
            else
            {
                Console.WriteLine($"Автомобили марки '{searchMake}' не найдены.");
            }
        }
        public void AddFromKeyboard()
        {   if (count == 15){Console.WriteLine("Списк полон"); return;}

            Console.Write("Марка: ");
            string make = Console.ReadLine();
            if (string.IsNullOrEmpty(make)) make = "?";

            Console.Write("Модель: ");
            string model = Console.ReadLine();
            if (string.IsNullOrEmpty(model)) model = "?";

            Console.Write("Год: ");
            int year = int.Parse(Console.ReadLine());

            Car newCar = new Car(make, model, year);
            Add(newCar);
        }

        public void PrintAll()
        {
            Console.WriteLine("\nСПИСОК АВТОМОБИЛЕЙ");
            for (int i = 0; i < count; i++)
            {
                //Console.Write($"[{i}] ");
                cars[i].PrintInfo();
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            CarList list = new CarList();
            Car car1 = new Car();                         
            Car car2 = new Car("Toyota", "Camry", 2020);   
            Car car3 = new Car("BMW", "X5", 2022);         
            Car car4 = new Car("Toyota", "Corolla", 2021); 
            
            list.Add(car1);
            list.Add(car2);
            list.Add(car3);
            list.Add(car4);
            list.PrintAll();
            while (true)
            {
                Console.WriteLine("\nМЕНЮ");
                Console.WriteLine("1. Показать все автомобили");
                Console.WriteLine("2. Добавить автомобиль");
                Console.WriteLine("3. Поиск по марке");
                Console.WriteLine("4. Удалить по марке");
                Console.WriteLine("0. Выход");

                string ch = Console.ReadLine();

                switch (ch)
                {
                    case "1":
                        list.PrintAll();
                        break;

                    case "2":
                        list.AddFromKeyboard();
                        list.PrintAll();
                        break;

                    case "3":
                        Console.Write("\nВведите марку для поиска: ");
                        string searchMake = Console.ReadLine();
                        list.SearchByMake(searchMake);
                        break;

                    case "4":
                        Console.Write("\nВведите марку автомобиля для удаления: ");
                        string deleteMake = Console.ReadLine();
                        list.DeleteByMake(deleteMake);
                        list.PrintAll();
                        break;

                    case "0":
                        Console.WriteLine("\nПрограмма завершена!");
                        return;

                    default:
                        Console.WriteLine("Ошибка! Введите 0-4");
                        break;
                }
            }
        }
    }
}