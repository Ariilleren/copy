using System;
namespace Variant23_FunctionsAndArrays
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
                Console.Write("\n(0-3): ");
                    
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
                            t2();
                            break;
                        case "3":
                            Task3_Strings();
                            break;
                        default:
                            Console.WriteLine("Неверный выбор");
                            Console.ReadKey();
                            break;
                }
            }
        }
        static void t1()
        {
            Console.Clear();
            Console.Write("Размер: ");
            int size = int.Parse(Console.ReadLine());
            
            int[] array = new int[size];
            Console.WriteLine("Элементы:");
            for (int i = 0; i < size; i++)
            {
                array[i] = int.Parse(Console.ReadLine());
            }
            
            Console.Write("\nИндексы нулевых элементов: ");

            for (int i = 0; i < array.Length; i++)
            {
                if (array[i] == 0)
                {
                    Console.Write(i /*+ " "*/);
                }
            }
            
            Console.WriteLine("\n\nНажмите любую клавишу для возврата в меню...");
            Console.ReadKey();
        }
        
        // ЗАДАНИЕ 2: Перевернуть все нечетные строки матрицы
        static void t2()
        {
            Console.Clear();
            Console.WriteLine("=== ЗАДАНИЕ 2: Переворот нечетных строк матрицы ===");
            
            Console.Write("Введите количество строк: ");
            int rows = int.Parse(Console.ReadLine());
            
            Console.Write("Введите количество столбцов: ");
            int cols = int.Parse(Console.ReadLine());
            
            if (rows <= 0 || cols <= 0)
            {
                Console.WriteLine("Размеры матрицы должны быть положительными числами!");
                Console.WriteLine("Нажмите любую клавишу для возврата в меню...");
                Console.ReadKey();
                return;
            }
            
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
            
            Console.WriteLine("\nИсходная матрица:");
            PrintMatrix(matrix);
            
            ReverseOddRows(matrix);
            
            Console.WriteLine("\nМатрица после переворота нечетных строк:");
            PrintMatrix(matrix);
            
            Console.WriteLine("\nНажмите любую клавишу для возврата в меню...");
            Console.ReadKey();
        }
        
        static void ReverseOddRows(int[,] matrix)
        {
            int cols = matrix.GetLength(1);
            
            for (int i = 1; i < matrix.GetLength(0); i += 2)
            {
                for (int j = 0; j < cols / 2; j++)
                {
                    int temp = matrix[i, j];
                    matrix[i, j] = matrix[i, cols - 1 - j];
                    matrix[i, cols - 1 - j] = temp;
                }
            }
        }
        
        // ЗАДАНИЕ 3: Подсчитать количество слов в строке (только одна строка)
        static void t3()
        {
            Console.Clear();
            Console.WriteLine("=== ЗАДАНИЕ 3: Подсчет слов в строке ===");
            
            Console.Write("Введите строку: ");
            string input = Console.ReadLine();
            
            int wordCount = CountWords(input);
            Console.WriteLine($"Количество слов: {wordCount}");
            
            Console.WriteLine("\nНажмите любую клавишу для возврата в меню...");
            Console.ReadKey();
        }
        
        static int CountWords(string text)
        {
            if (string.IsNullOrWhiteSpace(text))
                return 0;
            
            string[] words = text.Split(new char[] { ' ' }, 
                                       StringSplitOptions.RemoveEmptyEntries);
            return words.Length;
        }
        
        static void PrintMatrix(int[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                for (int j = 0; j < matrix.GetLength(1); j++)
                {
                    Console.Write($"{matrix[i, j],6}");
                }
                Console.WriteLine();
            }
        }
    }
}