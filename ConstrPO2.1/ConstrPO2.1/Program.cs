using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConstrPO2._1
{
    class Programm
    {
        static int MaxSize = 100;
        static int top = 0;
        static string[] st = new string[MaxSize];

        static void push(string c)
        {
            if (top < MaxSize)
            {
                st[top] = c;
                top++;
            }
            else
            {
                Console.WriteLine("Стек переполнен");
            }
        }

        static string? pop()
        {
            if (top > 0)
            {
                top--;
                return st[top];
            }
            else
            {
                Console.WriteLine("Стек пуст");
                return null;
            }
        }

        static void Main()
        {
            string? s;
            string r;
            do
            {
                Console.WriteLine("Что сдлеать?");
                s = Console.ReadLine();
                if (s == "заложить")
                {
                    Console.WriteLine("Что?");
                    r = Console.ReadLine() ?? "";
                    push(r);
                }
                if (s == "достать")
                {
                    Console.WriteLine(pop());
                }
            } while (s != "выйти");
        }
    }
}
