using System;

public class Telephone
{
    public string Marka { get; set; }
    public int Capacity { get; set; } // мощность аккумулятора
    public string BatteryType { get; set; } // тип аккумулятора
    public bool HasGprs { get; set; } // поддержка GPRS
    
    public override string ToString()
    {
        string gprsStatus = HasGprs ? "Да" : "Нет";
        return $"{Marka}, мощность: {Capacity} мАч, тип: {BatteryType}, GPRS: {gprsStatus}";
    }
}

public class PhoneList
{
    private Telephone[] telephones = new Telephone[5];
    private int count = 0;

    public void Add(Telephone phone)
    {
        if (phone == null)
        {
            Console.WriteLine("Ошибка: телефон не может быть null");
            return;
        }

        if (count < telephones.Length)
        {
            telephones[count] = phone;
            count++;
            Console.WriteLine($"Добавлен телефон: {phone.Marka}");
        }
        else
        {
            Console.WriteLine("Ошибка: список полон");
        }
    }

    public void Search(string mark)
    {
        if (string.IsNullOrEmpty(mark))
        {
            Console.WriteLine("Марка не указана");
            return;
        }

        bool found = false;
        for (int i = 0; i < count; i++)
        {
            if (telephones[i] != null && 
                telephones[i].Marka.Equals(mark, StringComparison.OrdinalIgnoreCase))
            {
                Console.WriteLine($"Найден телефон {i}: {telephones[i]}");
                found = true;
            }
        }

        if (!found)
        {
            Console.WriteLine($"Телефоны марки {mark} не найдены");
        }
    }

    public void DisplayAll()
    {
        if (count == 0)
        {
            Console.WriteLine("Список пуст");
            return;
        }

        Console.WriteLine("\nСписок телефонов:");
        Console.WriteLine("№ | Марка | Мощность | Тип АКБ | GPRS");
        Console.WriteLine(new string('-', 40));
        
        for (int i = 0; i < count; i++)
        {
            if (telephones[i] != null)
            {
                string gprs = telephones[i].HasGprs ? "Да" : "Нет";
                Console.WriteLine($"{i} | {telephones[i].Marka} | {telephones[i].Capacity} | {telephones[i].BatteryType} | {gprs}");
            }
        }
        Console.WriteLine();
    }

    public void Delete(int index)
    {
        if (index < 0 || index >= count)
        {
            Console.WriteLine("Ошибка: неверный номер");
            return;
        }

        string deletedPhone = telephones[index].Marka;
        
        for (int i = index; i < count - 1; i++)
        {
            telephones[i] = telephones[i + 1];
        }
        
        count--;
        telephones[count] = null;
        Console.WriteLine($"Телефон {deletedPhone} удален");
    }
}

class Program
{
    static void Main(string[] args)
    {
        PhoneList list = new PhoneList();
        
        // Добавление телефонов
        list.Add(new Telephone { Marka = "Apple", Capacity = 210, BatteryType = "Li-ion", HasGprs = true });
        list.Add(new Telephone { Marka = "Samsung", Capacity = 300, BatteryType = "Li-Po", HasGprs = false });
        list.Add(new Telephone { Marka = "Poco", Capacity = 190, BatteryType = "Li-Po", HasGprs = true });
        list.Add(new Telephone { Marka = "Xiaomi", Capacity = 240, BatteryType = "Ni-Cd", HasGprs = false });
        list.Add(new Telephone { Marka = "Realme", Capacity = 232, BatteryType = "Ni-MH", HasGprs = true });

        Console.WriteLine("=== Весь список ===");
        list.DisplayAll();

        Console.WriteLine("=== Поиск телефонов Apple ===");
        list.Search("apple");

        Console.WriteLine("\n=== Удаление первого телефона ===");
        list.Delete(0);
        
        Console.WriteLine("\n=== Список после удаления ===");
        list.DisplayAll();

        Console.WriteLine("Нажмите любую клавишу для выхода...");
        Console.ReadKey();
    }
}