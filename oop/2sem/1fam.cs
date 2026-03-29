using System;

namespace Variant23_FunctionsAndarr0s
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                    Console.Clear();
                    Console.WriteLine("1. Найти индексы нулевых элементов в одномерном массиве");
                    Console.WriteLine("2. Перевернуть нечетные строки в двумерном массиве");
                    Console.WriteLine("3. Подсчитать количество слов в строке");
                    Console.WriteLine("0. Выход");
                    Console.Write("\n0-3: ");
                    
                    string ch = Console.ReadLine();
                    
                    if (ch == "0")
                    {
                        Console.WriteLine("Пока.");
                        break;
                    }
                    
                    switch (ch)
                    {
                        case "1":
                            t1();
                            break;
                        case "2":
                            Task2_TwoDimensionalarr0();
                            break;
                        case "3":
                            Task3_Strings();
                            break;
                        default:
                            Console.WriteLine("Неверный выбор.");
                            Console.ReadLine();
                            break;
                    }
                
            }
        }
        
        // Создать новый массив из номеров элементов, значения которых равны 0
        static void t1()
        {
            Console.Clear();
            Console.WriteLine("1)");
            
            Console.Write("Количество элементов: ");
            int size = int.Parse(Console.ReadLine());
            
            // Создание и заполнение массива
            int[] arr = new int[size];
            Console.WriteLine("Элементы:");
            for (int i = 0; i < size; i++)
            {
                Console.Write($"{i}: ");
                arr[i] = int.Parse(Console.ReadLine());
            }
            
            Console.WriteLine("\nИсходный массив (с индексами):");
            Printarr0Withinds(arr);
            
            // Создаем массив из номеров элементов, равных нулю
            int[] nol_arr = ind_nol(arr);
            
            if (nol_arr.Length > 0)
            {
                Console.WriteLine("Номера (индексы) нулевых элементов:");
                Printarr0(nol_arr);
            }
            else
            {
                Console.WriteLine("Нулевых элементов не найдено.");
            }
            
            Console.WriteLine("\nНажмите любую клавишу для возврата в меню...");
            Console.ReadLine();
        }
        
        // Метод для создания массива из индексов нулевых элементов
        static int[] ind_nol(int[] arr0)
        {
            int c = 0;
            for (int i = 0; i < arr0.Length; i++)
            {
                if (arr0[i] == 0)
                    c++;
            }
            int[] inds = new int[c];
            int ind = 0;
            for (int i = 0; i < arr0.Length; i++)
            {
                if (arr0[i] == 0)
                {
                    inds[ind++] = i;
                }
            }
    
            return inds;
        }
        
        // ЗАДАНИЕ 2: Перевернуть все нечетные строки матрицы
        static void Task2_TwoDimensionalarr0()
        {
            Console.Clear();
            Console.WriteLine("=== ЗАДАНИЕ 2: Переворот нечетных строк матрицы ===");
            
            // Ввод размеров матрицы
            Console.Write("Введите количество строк: ");
            int rows = int.Parse(Console.ReadLine());
            
            Console.Write("Введите количество столбцов: ");
            int cols = int.Parse(Console.ReadLine());
            
            if (rows <= 0 || cols <= 0)
            {
                Console.WriteLine("Размеры матрицы должны быть положительными числами!");
                Console.WriteLine("Нажмите любую клавишу для возврата в меню...");
                Console.ReadLine();
                return;
            }
            
            // Создание и заполнение матрицы
            int[,] matrix = new int[rows, cols];
            Console.WriteLine("Введите элементы матрицы (целые числа):");
            
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    Console.Write($"Элемент [{i},{j}]: ");
                    matrix[i, j] = int.Parse(Console.ReadLine());
                }
            }
            
            Console.WriteLine("\nИсходная матрица (строки нумеруются с 0):");
            PrintMatrix(matrix);
            
            // Переворачиваем нечетные строки
            ReverseOddRows(matrix);
            
            Console.WriteLine("\nМатрица после переворота нечетных строк (1, 3, 5...):");
            PrintMatrix(matrix);
            
            // Показываем, какие строки были перевернуты
            Console.Write("\nПеревернутые строки: ");
            bool hasOddRows = false;
            for (int i = 0; i < rows; i++)
            {
                if (i % 2 != 0)
                {
                    Console.Write($"{i} ");
                    hasOddRows = true;
                }
            }
            
            if (!hasOddRows)
            {
                Console.Write("нет нечетных строк");
            }
            Console.WriteLine();
            
            Console.WriteLine("\nНажмите любую клавишу для возврата в меню...");
            Console.ReadLine();
        }
        
        // Метод для переворота нечетных строк матрицы
        static void ReverseOddRows(int[,] matrix)
        {
            int rows = matrix.GetLength(0);
            int cols = matrix.GetLength(1);
            
            for (int i = 0; i < rows; i++)
            {
                // Проверяем, является ли индекс строки нечетным
                if (i % 2 != 0)
                {
                    // Переворачиваем строку
                    for (int j = 0; j < cols / 2; j++)
                    {
                        int temp = matrix[i, j];
                        matrix[i, j] = matrix[i, cols - 1 - j];
                        matrix[i, cols - 1 - j] = temp;
                    }
                }
            }
        }
        
        // ЗАДАНИЕ 3: Подсчитать количество слов в строке
        static void Task3_Strings()
        {
            Console.Clear();
            Console.WriteLine("=== ЗАДАНИЕ 3: Подсчет слов в строке ===");
            
            Console.WriteLine("Введите строку для подсчета слов (можно несколько вариантов):");
            Console.WriteLine("Для завершения введите пустую строку");
            
            int lineNumber = 1;
            while (true)
            {
                Console.Write($"\nСтрока {lineNumber} (или Enter для завершения): ");
                string userInput = Console.ReadLine();
                
                // Проверка на выход (пустая строка)
                if (string.IsNullOrEmpty(userInput))
                {
                    if (lineNumber == 1)
                    {
                        Console.WriteLine("Вы не ввели ни одной строки.");
                    }
                    break;
                }
                
                int wordc = cWords(userInput);
                Console.WriteLine($"Количество слов: {wordc}");
                
                // Показываем разбивку по словам
                string[] words = userInput.Split(new char[] { ' ' }, 
                                                 StringSplitOptions.RemoveEmptyEntries);
                if (words.Length > 0)
                {
                    Console.WriteLine("Слова:");
                    for (int i = 0; i < words.Length; i++)
                    {
                        Console.WriteLine($"  {i + 1}. \"{words[i]}\"");
                    }
                }
                
                lineNumber++;
            }
            
            Console.WriteLine("\nНажмите любую клавишу для возврата в меню...");
            Console.ReadLine();
        }
        
        // Метод для подсчета количества слов в строке
        static int cWords(string text)
        {
            if (string.IsNullOrWhiteSpace(text))
                return 0;
            
            // Разбиваем строку по пробелам и удаляем пустые элементы
            string[] words = text.Split(new char[] { ' ' }, 
                                         StringSplitOptions.RemoveEmptyEntries);
            return words.Length;
        }
        
        // Вспомогательные методы
        static void Printarr0Withinds(int[] arr0)
        {
            
            Console.Write("Массив:  ");
            for (int i = 0; i < arr0.Length; i++)
            {
                Console.Write($"{arr0[i]}\t");
            }
            Console.WriteLine();
        }
        
        static void Printarr0(int[] arr0)
        {
            if (arr0.Length == 0)
            {
                Console.WriteLine("Массив пуст");
                return;
            }
            
            for (int i = 0; i < arr0.Length; i++)
            {
                Console.Write($"{arr0[i]} ");
            }
            Console.WriteLine();
        }
        
        static void PrintMatrix(int[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                Console.Write($"Строка {i}: ");
                for (int j = 0; j < matrix.GetLength(1); j++)
                {
                    Console.Write($"{matrix[i, j],6}");
                }
                Console.WriteLine();
            }
        }
    }
}